#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compil.h"
#include "error.h"

extern Node* root;                      // La racine de l'arbre tpc
extern TableCeption* table_ception;     // Table des symboles
extern char* file_name;                 // Nom du fichier tpc
extern int nb_error;                    // Nombre d'erreur
extern int start_flag;                  // Presence d'un main
FILE* f_nasm;                           // Fichier sortie nasm


/**
 * Fonction aiguillage des expressions
 * @param expr La racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return type_v de l'expression
 */
static type_v evalExpr(Node* expr, Identifier* funct_id, Precalc* pre_calc);


static int evalSuiteInstr(Node* instr, Identifier* funct_id);



static Precalc* initPrecalc() {
    Precalc* new = (Precalc*) malloc(sizeof(Precalc));
    if (!new) exit(5);
    new->abort = 0;
    return new;
}


static type_v evalIdent(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    if (pre_calc) pre_calc->abort = 1;
    Identifier* var = verifHashFunct(table_ception->global_var, funct_id, expr->ident);
    if (!var) {
        errorUndeclared(expr);
        return None_v;
    }
    if (!var->data.var.is_init) warningUninitialized(expr);
    var->data.var.is_used = 1;
    return var->data.var.type;
}


static type_v evalFunct(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    if (pre_calc) pre_calc->abort = 1;
    Identifier* funct = verifHashTable(table_ception->global_funct, expr->ident);
    if (!funct) {
        errorImpliciteDecl(expr);
        return None_v;
    }
    Node* arg = expr->firstChild;
    for (int i = funct->data.func.nb_param - 1; i >= 0; i--) {
        if (!arg || arg->label == Void) {
            errorTooFewArgs(expr);
            return None_v;
        }
        type_v right = evalExpr(arg, funct_id, NULL);
        if (funct->data.func.param[i].data.var.type == Char_v && right == Int_v) warningImpliciteConvert(expr, funct->data.func.param[i].data.var.id);
        arg = arg->nextSibling;
    }
    if (arg && arg->label != Void) {
        errorTooManyArgs(expr);
        return None_v;
    }
    funct->data.func.is_used = 1;
    return funct->data.func.type;
}


static type_v evalNegate(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    evalExpr(expr->firstChild, funct_id, pre_calc);
    if (!pre_calc->abort) pre_calc->val = !pre_calc->val;
    return Int_v;
}


static type_v evalUnOperator(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    evalExpr(expr->firstChild, funct_id, pre_calc);
    if (!pre_calc->abort && expr->byte == '-') pre_calc->val *= -1; 
    return Int_v;
}


static type_v evalBiOperator(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    int is_div = expr->byte == '/' || expr->byte == '%';
    Precalc* pre_left = pre_calc? initPrecalc(): NULL;
    Precalc* pre_right = pre_calc || is_div? initPrecalc(): NULL;
    evalExpr(expr->firstChild, funct_id, pre_left);
    evalExpr(expr->firstChild->nextSibling, funct_id, pre_right);
    if (is_div && !pre_right->abort && !pre_right->val) {
        warningDivisionZero(expr);
        pre_calc->abort = 1;
    }
    if (pre_calc && !pre_calc->abort) {
        if (!pre_left->abort && !pre_right->abort) {
            switch (expr->byte) {
                case '+': pre_calc->val = pre_left->val + pre_right->val; break;
                case '-': pre_calc->val = pre_left->val - pre_right->val; break;
                case '*': pre_calc->val = pre_left->val * pre_right->val; break;
                case '/': pre_calc->val = pre_left->val / pre_right->val; break;
                case '%': pre_calc->val = pre_left->val % pre_right->val;
            }
        } else {
            pre_calc->abort = 1;
        }
    }
    free(pre_left);
    free(pre_right);
    return Int_v;
}


static type_v evalOrder(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    Precalc* pre_left = pre_calc? initPrecalc(): NULL;
    Precalc* pre_right = pre_calc? initPrecalc(): NULL;
    evalExpr(expr->firstChild, funct_id, pre_left);
    evalExpr(expr->firstChild->nextSibling, funct_id, pre_right);
    if (pre_calc) {
        if (!pre_left->abort && !pre_right->abort) {
            if (!strcmp(expr->ident, "<")) pre_calc->val = pre_left->val < pre_right->val;
            else if (!strcmp(expr->ident, "<=")) pre_calc->val = pre_left->val <= pre_right->val;
            else if (!strcmp(expr->ident, ">")) pre_calc->val = pre_left->val > pre_right->val;
            else pre_calc->val = pre_left->val >= pre_right->val;
        } else {
            pre_calc->abort = 1;
        }
    }
    free(pre_left);
    free(pre_right);
    return Int_v;
}


static type_v evalEqual(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    Precalc* pre_left = pre_calc? initPrecalc(): NULL;
    Precalc* pre_right = pre_calc? initPrecalc(): NULL;
    evalExpr(expr->firstChild, funct_id, pre_left);
    evalExpr(expr->firstChild->nextSibling, funct_id, pre_right);
    if (pre_calc) {
        if (!pre_left->abort && !pre_right->abort) {
            if (!strcmp(expr->ident, "==")) pre_calc->val = pre_left->val == pre_right->val;
            else pre_calc->val = pre_left->val != pre_right->val;
        } else {
            pre_calc->abort = 1;
        }
    }
    free(pre_left);
    free(pre_right);
    return Int_v;
}


static type_v evalAnd(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    Precalc* pre_left = pre_calc? initPrecalc(): NULL;
    Precalc* pre_right = pre_calc? initPrecalc(): NULL;
    evalExpr(expr->firstChild, funct_id, pre_left);
    evalExpr(expr->firstChild->nextSibling, funct_id, pre_right);
    if (pre_calc) {
        if (!pre_left->abort && !pre_right->abort) {
            pre_calc->val = pre_left->val && pre_right->val;
        } else {
            pre_calc->abort = 1;
        }
    }
    free(pre_left);
    free(pre_right);
    return Int_v;
}


static type_v evalOr(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    Precalc* pre_left = pre_calc? initPrecalc(): NULL;
    Precalc* pre_right = pre_calc? initPrecalc(): NULL;
    evalExpr(expr->firstChild, funct_id, pre_left);
    evalExpr(expr->firstChild->nextSibling, funct_id, pre_right);
    if (pre_calc) {
        if (!pre_left->abort && !pre_right->abort) {
            pre_calc->val = pre_left->val || pre_right->val;
        } else {
            pre_calc->abort = 1;
        }
    }
    free(pre_left);
    free(pre_right);
    return Int_v;
}


static type_v evalExpr(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    switch (expr->label) {
    case Num: if (pre_calc) pre_calc->val = expr->num; return Int_v;
    case Char: if (pre_calc) pre_calc->val = expr->byte; return Char_v;
    case Ident: return evalIdent(expr, funct_id, pre_calc);
    case Funct: return evalFunct(expr, funct_id, pre_calc);
    case Negate: return evalNegate(expr, funct_id, pre_calc);
    case UnOperator: return evalUnOperator(expr, funct_id, pre_calc);
    case BiOperator: return evalBiOperator(expr, funct_id, pre_calc);
    case Equal: return evalEqual(expr, funct_id, pre_calc);
    case Order: return evalOrder(expr, funct_id, pre_calc);
    case And: return evalAnd(expr, funct_id, pre_calc);
    case Or: return evalOr(expr, funct_id, pre_calc);
    default: fprintf(stderr, "Expr: %d WIP\n", expr->label); return None_v;
    }
}








static int evalAffect(Node* instr, Identifier* funct_id) {
    Identifier* left = verifHashFunct(table_ception->global_var, funct_id, instr->ident);
    if (!left) errorUndeclared(instr);
    type_v right = evalExpr(instr->firstChild, funct_id, NULL);
    if (left) {
        left->data.var.is_init = 1;
        if (right == Void_v) {
            errorIgnoredVoid(instr->firstChild);
        }
        if (left->data.var.type == Char_v && right == Int_v) warningImpliciteConvert(instr, NULL);
    }
    return 0;
}


static int evalReturn(Node* instr, Identifier* funct_id) {
    type_v right = instr->firstChild? evalExpr(instr->firstChild, funct_id, NULL): Void_v;
    if (funct_id->data.func.type == Void_v && (right == Int_v || right == Char_v)) warningRetValVoid(instr);
    if (funct_id->data.func.type != Void_v && right == Void_v) warningRetNoValNoVoid(instr);
    if (funct_id->data.func.type == Char_v && right == Int_v) warningImpliciteConvert(instr, NULL);
    return 1;
}


static int evalWhile(Node* instr, Identifier* funct_id) {
    evalExpr(instr->firstChild->firstChild, funct_id, NULL); //condition while
    int nb_ret = evalSuiteInstr(instr->firstChild->nextSibling->firstChild, funct_id); //intérieur boucle while
    return nb_ret;
}


static int evalIf(Node* instr, Identifier* funct_id) {
    Precalc* pre_calc = initPrecalc();
    int tmp;
    evalExpr(instr->firstChild->firstChild, funct_id, pre_calc);
    int nb_ret_if = evalSuiteInstr(instr->firstChild->nextSibling->firstChild, funct_id);

    //else existant ou non 
    if (instr->firstChild->nextSibling->nextSibling){
        int nb_ret_else = evalSuiteInstr(instr->firstChild->nextSibling->nextSibling->firstChild, funct_id); 
        if (!(pre_calc->abort)) tmp = (nb_ret_if || !(pre_calc->val)) && (nb_ret_else || pre_calc->val);
        else tmp = nb_ret_if && nb_ret_else; //regarde si il y a bien un return dans les deux blocs
    } else {
        tmp = !(pre_calc->abort) && pre_calc->val && nb_ret_if;
    }
    free(pre_calc);
    return tmp;
}


/**
 * Fonction aiguillage des instructions
 * @param instr La racine de l'instruction
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return Presence ou non d'un return
 */
static int evalInstr(Node* instr, Identifier* funct_id) {
    printf("N %d\n", instr->label);
    switch (instr->label)
    {
    case Affect: return evalAffect(instr, funct_id);
    case Return: return evalReturn(instr, funct_id);
    case Funct: evalFunct(instr, funct_id, NULL); return 0;
    case While: return evalWhile(instr, funct_id);
    case If: return evalIf(instr, funct_id);
    default: fprintf(stdout, "Instr: %d WIP\n", instr->label); return 0;
    }
}


static int evalSuiteInstr(Node* instr, Identifier* funct_id) {
    Node* cursor = instr;
    int return_block = 0;
    for (; cursor; cursor = cursor->nextSibling) return_block += evalInstr(cursor, funct_id);
    return return_block;
}


static void evalDeclFonct(Node* decl_funct) {
    Identifier* funct_id = verifHashTable(table_ception->global_funct, decl_funct->firstChild->firstChild->nextSibling->ident);
    printf("\n- %s\n", funct_id->data.func.id);
    // TODO ecriture en-tete + alloc var local
    Node* instr = decl_funct->firstChild->nextSibling->nextSibling->firstChild;
    int return_block = evalSuiteInstr(instr, funct_id);
    if (funct_id->data.func.type != Void_v && funct_id->data.func.type != None_v && !return_block)
        warningControlReaches(decl_funct->firstChild->firstChild->nextSibling);
    // TODO ecriture nettoyage pile + 'ret'
}


void evalTpc() {
    // TODO ecriture en-tete fichier
    Node* decl_funct = root->firstChild->nextSibling;
    for (; decl_funct; decl_funct = decl_funct->nextSibling) evalDeclFonct(decl_funct);
    // TODO ecriture _start si main present
}
