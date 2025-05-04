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
int nb_label = 0;                       // Nombre de label actuel

// r11 -> r10 -> r9 -> r8 -> rcx -> rdx -> rsi -> rdi -> rax

/**
 * Fonction aiguillage des expressions
 * @param expr La racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return type_v de l'expression
 */
static type_v evalExpr(Node* expr, Identifier* funct_id, Precalc* pre_calc);


/**
 * Evalue le bloc d'instruction 
 * @param instr La node racine du bloc d'instruction
 * @param funct_id La structure de la fonction dans lequel se trouve le bloc
 * @return Le passage obligatoire par l'instruction `return` dans le bloc
 */
static int evalSuiteInstr(Node* instr, Identifier* funct_id);



/**
 * Initialise une structure de pre-calcul d'expression
 * @return L'adresse de la structure
 */
static Precalc* initPrecalc() {
    Precalc* new = (Precalc*) malloc(sizeof(Precalc));
    if (!new) exit(5);
    new->abort = 0;
    return new;
}


/**
 * Evalue l'expression d'appel de variable
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param expr La node racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @param pre_calc Structure pour gerer le pre-calcul de l'expression (`NULL` inutile, sinon necessaire)
 * @return Le type de l'expression
 */
static type_v evalIdent(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    if (pre_calc) pre_calc->abort = 1;
    Identifier* var = verifHashFunct(table_ception->global_var, funct_id, expr->ident);
    if (!var) {
        errorUndeclared(expr);
        return None_v;
    }
    if (!var->data.var.is_init) warningUninitialized(expr);
    var->data.var.is_used = 1;
    fprintf(                                        // Recupere la valeur dans la memoire
        f_nasm, "mov r11%c, %s\n",
        var->data.var.type == Int_v? 'd': 'b',
        var->data.var.adress
    );
    fprintf(
        f_nasm, "sub rsp, %d\nmov %s [rsp], r11%c\n",
        var->data.var.type == Char_v? 1: 4,
        var->data.var.type == Char_v? "byte": "dword",
        var->data.var.type == Char_v? 'b': 'd'
    );                  // Met dans la pile la valeur
    return var->data.var.type;
}


/**
 * Evalue l'expression d'appel de fonction
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param expr La node racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @param pre_calc Structure pour gerer le pre-calcul de l'expression (`NULL` inutile, sinon necessaire)
 * @return Le type de l'expression
 */
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


/**
 * Evalue l'expression de negation
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param expr La node racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @param pre_calc Structure pour gerer le pre-calcul de l'expression (`NULL` inutile, sinon necessaire)
 * @return Le type de l'expression
 */
static type_v evalNegate(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    type_v right = evalExpr(expr->firstChild, funct_id, pre_calc);
    if (pre_calc && !pre_calc->abort) pre_calc->val = !pre_calc->val;
    int label_if = nb_label;
    int label_else = nb_label + 1;
    nb_label += 2;
    fprintf(
        f_nasm, "mov r11%c, [rsp]\nadd rsp, %d\n"
                "cmp r11d, 0\n"
                "jne .%d_else\n"
                "mov r11d, 1\n"
                "jmp .%d_if\n"
                ".%d_else:\n"
                "xor r11d, r11d\n"
                ".%d_if:\n"
                "sub rsp, 4\nmov dword [rsp], r11d\n",
        right == Char_v? 'b': 'd',
        right == Char_v? 1: 4,
        label_else,
        label_if,
        label_else,
        label_if
    );
    return Int_v;
}


/**
 * Evalue l'expression des operateurs unaire
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param expr La node racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @param pre_calc Structure pour gerer le pre-calcul de l'expression (`NULL` inutile, sinon necessaire)
 * @return Le type de l'expression
 */
static type_v evalUnOperator(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    type_v right = evalExpr(expr->firstChild, funct_id, pre_calc);
    if (pre_calc && !pre_calc->abort && expr->byte == '-') pre_calc->val *= -1; 
    if (expr->byte == '-') fprintf(
        f_nasm, "mov r11%c, [rsp]\nadd rsp, %d\nneg r11\nsub rsp, 4\nmov dword [rsp], r11d\n",
        right == Char_v? 'b': 'd',
        right == Char_v? 1: 4
    );
    return Int_v;
}


/**
 * Evalue l'expression des operateurs binaire
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param expr La node racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @param pre_calc Structure pour gerer le pre-calcul de l'expression (`NULL` inutile, sinon necessaire)
 * @return Le type de l'expression
 */
static type_v evalBiOperator(Node* expr, Identifier* funct_id, Precalc* pre_calc) {
    int is_div = expr->byte == '/' || expr->byte == '%';
    Precalc* pre_left = pre_calc? initPrecalc(): NULL;
    Precalc* pre_right = pre_calc || is_div? initPrecalc(): NULL;
    type_v right = evalExpr(expr->firstChild->nextSibling, funct_id, pre_right);
    type_v left = evalExpr(expr->firstChild, funct_id, pre_left);
    if (is_div && !pre_right->abort && !pre_right->val) {
        warningDivisionZero(expr);
        if (pre_calc) pre_calc->abort = 1;
    }
    if (pre_calc && (pre_left->abort || pre_right->abort)) pre_calc->abort = 1;

    int fill_pre_calc = pre_calc && !(pre_calc->abort || pre_left->abort || pre_right->abort);
    switch (expr->byte) {
        case '+':
            if (fill_pre_calc) pre_calc->val = pre_left->val + pre_right->val;
            if (left == Char_v) fprintf(f_nasm, "xor r10, r10\n");
            if (right == Char_v) fprintf(f_nasm, "xor r11, r11\n");
            fprintf(
                f_nasm, "mov r10%c, [rsp]\nadd rsp, %d\n"
                        "mov r11%c, [rsp]\nadd rsp, %d\n"
                        "add r10d, r11d\n"
                        "sub rsp, 4\nmov dword [rsp], r10d\n",
                left == Char_v? 'b': 'd',
                left == Char_v? 1: 4,
                right == Char_v? 'b': 'd',
                right == Char_v? 1: 4
            );
            break;
        case '-':
            if (fill_pre_calc) pre_calc->val = pre_left->val - pre_right->val;
            if (left == Char_v) fprintf(f_nasm, "xor r10, r10\n");
            if (right == Char_v) fprintf(f_nasm, "xor r11, r11\n");
            fprintf(
                f_nasm, "mov r10%c, [rsp]\nadd rsp, %d\n"
                        "mov r11%c, [rsp]\nadd rsp, %d\n"
                        "sub r10d, r11d\n"
                        "sub rsp, 4\nmov dword [rsp], r10d\n",
                left == Char_v? 'b': 'd',
                left == Char_v? 1: 4,
                right == Char_v? 'b': 'd',
                right == Char_v? 1: 4
            );
            break;
        case '*':
            if (fill_pre_calc) pre_calc->val = pre_left->val * pre_right->val;
            if (left == Char_v) fprintf(f_nasm, "xor r10, r10\n");
            if (right == Char_v) fprintf(f_nasm, "xor r11, r11\n");
            fprintf(
                f_nasm, "mov r10%c, [rsp]\nadd rsp, %d\n"
                        "mov r11%c, [rsp]\nadd rsp, %d\n"
                        "imul r10d, r11d\n"
                        "sub rsp, 4\nmov dword [rsp], r10d\n",
                left == Char_v? 'b': 'd',
                left == Char_v? 1: 4,
                right == Char_v? 'b': 'd',
                right == Char_v? 1: 4
            );
            break;
        case '/':
            if (fill_pre_calc) pre_calc->val = pre_left->val / pre_right->val;
            if (left == Char_v) fprintf(f_nasm, "xor rax, rax\n");
            if (right == Char_v) fprintf(f_nasm, "xor rbx, rbx\n");
            fprintf(
                f_nasm, "xor rdx, rdx\n"
                        "mov %s, [rsp]\nadd rsp, %d\n"
                        "mov %s, [rsp]\nadd rsp, %d\n"
                        "idiv rbx\n"
                        "sub rsp, 4\nmov dword [rsp], eax\n",
                left == Char_v? "al": "eax",
                left == Char_v? 1: 4,
                right == Char_v? "bl": "ebx",
                right == Char_v? 1: 4
            );
            break;
        case '%':
            if (fill_pre_calc) pre_calc->val = pre_left->val % pre_right->val;
            if (left == Char_v) fprintf(f_nasm, "xor rax, rax\n");
            if (right == Char_v) fprintf(f_nasm, "xor rbx, rbx\n");
            fprintf(
                f_nasm, "xor rdx, rdx\n"
                        "mov %s, [rsp]\nadd rsp, %d\n"
                        "mov %s, [rsp]\nadd rsp, %d\n"
                        "idiv rbx\n"
                        "sub rsp, 4\nmov dword [rsp], edx\n",
                left == Char_v? "al": "eax",
                left == Char_v? 1: 4,
                right == Char_v? "bl": "ebx",
                right == Char_v? 1: 4
            );
    }
    free(pre_left);
    free(pre_right);
    return Int_v;
}


/**
 * Evalue l'expression d'ordre
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param expr La node racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @param pre_calc Structure pour gerer le pre-calcul de l'expression (`NULL` inutile, sinon necessaire)
 * @return Le type de l'expression
 */
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


/**
 * Evalue l'expression d'egalite
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param expr La node racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @param pre_calc Structure pour gerer le pre-calcul de l'expression (`NULL` inutile, sinon necessaire)
 * @return Le type de l'expression
 */
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


/**
 * Evalue l'expression `and`
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param expr La node racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @param pre_calc Structure pour gerer le pre-calcul de l'expression (`NULL` inutile, sinon necessaire)
 * @return Le type de l'expression
 */
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


/**
 * Evalue l'expression `or`
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param expr La node racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @param pre_calc Structure pour gerer le pre-calcul de l'expression (`NULL` inutile, sinon necessaire)
 * @return Le type de l'expression
 */
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
    case Num: if (pre_calc) pre_calc->val = expr->num; fprintf(f_nasm, "sub rsp, 4\nmov dword [rsp], %d\n", expr->num); return Int_v;
    case Char: if (pre_calc) pre_calc->val = expr->byte; fprintf(f_nasm, "sub rsp, 1\nmov byte [rsp], '%c'\n", expr->byte); return Char_v;
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






/**
 * Evalue l'instruction d'affectation
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param instr La node racine de l'instruction
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return Le passage obligatoire par l'instruction `return` dans l'expression
 */
static int evalAffect(Node* instr, Identifier* funct_id) {
    Identifier* left = verifHashFunct(table_ception->global_var, funct_id, instr->ident);
    if (!left) errorUndeclared(instr);
    type_v right = evalExpr(instr->firstChild, funct_id, NULL);
    if (left) {
        fprintf(
            f_nasm, "mov r11%c, [rsp]\nadd rsp, %d\n",  // Recuperer la valeur dans la pile
            right == Char_v? 'b': 'd',
            right == Char_v? 1: 4
        );
        left->data.var.is_init = 1;
        if (right == Void_v) {
            errorIgnoredVoid(instr->firstChild);
        }
        int affect_type = left->data.var.type;
        if (affect_type == Char_v && right == Int_v) warningImpliciteConvert(instr, NULL);
        fprintf(
            f_nasm, "mov %s %s, r11%c\n",               // Place la valeur recuperer dans la zone memoire
            affect_type == Char_v? "byte": "dword",
            left->data.var.adress,
            affect_type == Char_v? 'b': 'd'
        );
    }
    return 0;
}


/**
 * Evalue l'instruction de retour
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param instr La node racine de l'instruction
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return Le passage obligatoire par l'instruction `return` dans l'expression
 */
static int evalReturn(Node* instr, Identifier* funct_id) {
    type_v right = instr->firstChild? evalExpr(instr->firstChild, funct_id, NULL): Void_v;
    if (funct_id->data.func.type == Void_v && (right == Int_v || right == Char_v)) warningRetValVoid(instr);
    if (funct_id->data.func.type != Void_v && right == Void_v) warningRetNoValNoVoid(instr);
    if (funct_id->data.func.type == Char_v && right == Int_v) warningImpliciteConvert(instr, NULL);
    if (right == Char_v) fprintf(f_nasm, "xor rax, rax\nmov al, [rsp]\nadd rsp, 1\n");
    else if (right != Void_v) fprintf(f_nasm, "mov eax, [rsp]\nadd rsp, 4\n");
    fprintf(f_nasm, "mov rsp, rbp\npop rbp\nret\n");
    return 1;
}


/**
 * Evalue l'instruction de boucle
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param instr La node racine de l'instruction
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return Le passage obligatoire par l'instruction `return` dans l'expression
 */
static int evalWhile(Node* instr, Identifier* funct_id) {
    evalExpr(instr->firstChild->firstChild, funct_id, NULL); //condition while
    int nb_ret = evalSuiteInstr(instr->firstChild->nextSibling->firstChild, funct_id); //intérieur boucle while
    return nb_ret;
}


/**
 * Evalue l'instruction conditionnelle
 * Ecrit en assembleur tant qu'il n'y a pas d'erreur
 * @param instr La node racine de l'instruction
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return Le passage obligatoire par l'instruction `return` dans l'expression
 */
static int evalIf(Node* instr, Identifier* funct_id) {
    Precalc* pre_calc = initPrecalc();
    int tmp;
    evalExpr(instr->firstChild->firstChild, funct_id, pre_calc);
    int nb_ret_if = evalSuiteInstr(instr->firstChild->nextSibling->firstChild, funct_id);
    // Cas if-else
    if (instr->firstChild->nextSibling->nextSibling){
        int nb_ret_else = evalSuiteInstr(instr->firstChild->nextSibling->nextSibling->firstChild, funct_id);
        // Cas tautologie
        if (!(pre_calc->abort)) tmp = (nb_ret_if || !(pre_calc->val)) && (nb_ret_else || pre_calc->val);
        // Cas sophisme 
        else tmp = nb_ret_if && nb_ret_else; //regarde si il y a bien un return dans les deux blocs
    } else { // Cas if
        tmp = !(pre_calc->abort) && pre_calc->val && nb_ret_if;
    }
    free(pre_calc);
    return tmp;
}


/**
 * Fonction aiguillage pour l'evaluation des instructions
 * @param instr La node racine de l'instruction
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return Le passage obligatoire par l'instruction `return` dans l'expression
 */
static int evalInstr(Node* instr, Identifier* funct_id) {
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


/**
 * Evalue la declaration d'une fonction et le type de retour (type ou retour en Void)
 * Ecrit l'assembleur tant qu'il n'y a pas d'erreur
 * @param decl_fonct La node racine a la fonction
 */
static void evalDeclFonct(Node* decl_funct) {
    Identifier* funct_id = verifHashTable(table_ception->global_funct, decl_funct->firstChild->firstChild->nextSibling->ident);
    fprintf(f_nasm, "f_%s:\npush rbp\nmov rbp, rsp\n", funct_id->data.func.id);
    if (funct_id->data.func.size_alloc) fprintf(f_nasm, "sub rsp, %d\n", funct_id->data.func.size_alloc);
    Node* instr = decl_funct->firstChild->nextSibling->nextSibling->firstChild;
    int return_block = evalSuiteInstr(instr, funct_id);
    if (funct_id->data.func.type != Void_v && funct_id->data.func.type != None_v && !return_block)
        warningControlReaches(decl_funct->firstChild->firstChild->nextSibling);
    fprintf(f_nasm, "mov rsp, rbp\npop rbp\nret\n");
}

void evalTpc() {
    f_nasm = fopen("bin/_anonymous.asm", "w+");
    if (!f_nasm) exit(5);
    fprintf(f_nasm, "section .bss\n");
    if (table_ception->size_alloc_var) fprintf(f_nasm, "%s resb %d\n", GLOBAL_VAR, table_ception->size_alloc_var);
    fprintf(f_nasm, "%s resb 1\n%s resb 16\nsection .text\nglobal _start\n", CHAR_BUFF, INT_BUFF);
    Node* decl_funct = root->firstChild->nextSibling;
    for (; decl_funct; decl_funct = decl_funct->nextSibling) evalDeclFonct(decl_funct);
    fprintf(f_nasm, "_start:\ncall f_main\nmov rdi, rax\nmov rax, 60\nsyscall");        // Recuperer et renvoyer la valeur de sortie du main
    fclose(f_nasm);
    if (nb_error) remove("bin/_anonymous.asm");
}
