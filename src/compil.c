#include <stdio.h>
#include <string.h>
#include "compil.h"
#include "error.h"

extern Node* root;                      // La racine de l'arbre tpc
extern TableCeption* table_ception;     // Table des symboles
extern char* file_name;                 // Nom du fichier tpc
extern int nb_error;                    // Nombre d'erreur
extern int nb_warning;                  // Nombre de warning
extern int start_flag;                  // Presence d'un main
FILE* f_nasm;                           // Fichier sortie nasm


/**
 * Fonction aiguillage des expressions
 * @param expr La racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return type_v de l'expression
 */
static type_v evalExpr(Node* expr, Identifier* funct_id);


static int evalSuiteInstr(Node* instr, Identifier* funct_id);



static type_v evalIdent(Node* expr, Identifier* funct_id) {
    Identifier* var = verifHashFunct(table_ception->global_var, funct_id, expr->ident);
    if (!var) {
        errorUndeclared(expr);
        return None_v;
    }
    if (!var->data.var.is_init) warningUninitialized(expr);
    var->data.var.is_used = 1;
    return var->data.var.type;
}


static type_v evalFunct(Node* expr, Identifier* funct_id) {
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
        type_v right = evalExpr(arg, funct_id);
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


static type_v evalNegate(Node* expr, Identifier* funct_id) {
    evalExpr(expr->firstChild, funct_id);
    return Int_v;
}


static type_v evalUnOperator(Node* expr, Identifier* funct_id) {
    evalExpr(expr->firstChild, funct_id);
    return Int_v;
}


static type_v evalBiOperator(Node* expr, Identifier* funct_id) {
    evalExpr(expr->firstChild->nextSibling, funct_id);
    evalExpr(expr->firstChild, funct_id);
    return Int_v;
}


static type_v evalOrder(Node* expr, Identifier* funct_id) {
    evalExpr(expr->firstChild->nextSibling, funct_id);
    evalExpr(expr->firstChild, funct_id);
    return Int_v;
}


static type_v evalEqual(Node* expr, Identifier* funct_id) {
    evalExpr(expr->firstChild->nextSibling, funct_id);
    evalExpr(expr->firstChild, funct_id);
    return Int_v;
}


static type_v evalAnd(Node* expr, Identifier* funct_id) {
    evalExpr(expr->firstChild->nextSibling, funct_id);
    evalExpr(expr->firstChild, funct_id);
    return Int_v;
}


static type_v evalOr(Node* expr, Identifier* funct_id) {
    evalExpr(expr->firstChild->nextSibling, funct_id);
    evalExpr(expr->firstChild, funct_id);
    return Int_v;
}


static type_v evalExpr(Node* expr, Identifier* funct_id) {
    switch (expr->label)
    {
    case Num: return Int_v;
    case Char: return Char_v;
    case Ident: return evalIdent(expr, funct_id);
    case Funct: return evalFunct(expr, funct_id);
    case Negate: return evalNegate(expr, funct_id);
    case UnOperator: return evalUnOperator(expr, funct_id);
    case BiOperator: return evalBiOperator(expr, funct_id);
    case Equal: return evalEqual(expr, funct_id);
    case Order: return evalOrder(expr, funct_id);
    case And: return evalAnd(expr, funct_id);
    case Or: return evalOr(expr, funct_id);
    default: fprintf(stderr, "Expr: %d WIP\n", expr->label); return None_v;
    }
}








static int evalAffect(Node* instr, Identifier* funct_id) {
    Identifier* left = verifHashFunct(table_ception->global_var, funct_id, instr->ident);
    if (!left) errorUndeclared(instr);
    type_v right = evalExpr(instr->firstChild, funct_id);
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
    type_v right = instr->firstChild? evalExpr(instr->firstChild, funct_id): Void_v;
    if (funct_id->data.func.type == Void_v && (right == Int_v || right == Char_v)) warningRetValVoid(instr);
    if (funct_id->data.func.type != Void_v && right == Void_v) warningRetNoValNoVoid(instr);
    if (funct_id->data.func.type == Char_v && right == Int_v) warningImpliciteConvert(instr, NULL);
    return 1;
}


static int evalWhile(Node* instr, Identifier* funct_id) {
    
}


/**
 * Fonction aiguillage des instructions
 * @param instr La racine de l'instruction
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return Presence ou non d'un return
 */
static int evalInstr(Node* instr, Identifier* funct_id) {
    switch (instr->label)
    {
    case Affect: return evalAffect(instr, funct_id);
    case Return: return evalReturn(instr, funct_id);
    case Funct: evalFunct(instr, funct_id); return 0;
    case While: return evalWhile(instr, funct_id);
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
    if (funct_id->data.func.type != Void_v && funct_id->data.func.type != None_v && !evalSuiteInstr(instr, funct_id))
        warningControlReaches(decl_funct->firstChild->firstChild->nextSibling);
    // TODO ecriture nettoyage pile + 'ret'
}


void evalTpc() {
    // TODO ecriture en-tete fichier
    Node* decl_funct = root->firstChild->nextSibling;
    for (; decl_funct; decl_funct = decl_funct->nextSibling) evalDeclFonct(decl_funct);
    // TODO ecriture _start si main present
}
