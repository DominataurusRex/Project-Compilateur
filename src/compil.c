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


static type_v evalExpr(Node* expr, Identifier* funct_id);



static type_v evalIdent(Node* expr, Identifier* funct_id) {
    Identifier* var = verifHashFunct(table_ception->global_var, funct_id, expr->ident);
    if (!var) {
        errorUndeclared(expr);
        return None_v;
    }
    if (!var->data.var.is_init) warningUninitialized(expr);
    return !strcmp(var->data.var.type, "int")? Int_v: Char_v;
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





/**
 * Fonction aiguillage des expressions
 * @param expr La racine de l'expression
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 * @return type_v de l'expression
 */
static type_v evalExpr(Node* expr, Identifier* funct_id) {
    switch (expr->label)
    {
    case Num: {
        return Int_v;
    }
    case Char: {
        return Char_v;
    }
    case Ident: {
        return evalIdent(expr, funct_id);
    }
    case Funct: {
        printf("Todo funct\n");
        return None_v;
    }
    case Negate: {
        return evalNegate(expr, funct_id);
    }
    case UnOperator: {
        return evalUnOperator(expr, funct_id);
    }
    case BiOperator: {
        return evalBiOperator(expr, funct_id);
    }
    case Equal: {
        return evalEqual(expr, funct_id);
    }
    case Order: {
        return evalOrder(expr, funct_id);
    }
    case And: {
        return evalAnd(expr, funct_id);
    }
    case Or: {
        return evalOr(expr, funct_id);
    }
    default: {
        fprintf(stderr, "Expr: %d WIP\n", expr->label);
        return None_v;
    }
    }
}


static void evalAffect(Node* instr, Identifier* funct_id) {
    Identifier* left = verifHashFunct(table_ception->global_var, funct_id, instr->ident);
    if (!left) errorUndeclared(instr);
    type_v right = evalExpr(instr->firstChild, funct_id);
    if (left) {
        if (right == Int_v && !strcmp(left->data.var.type, "char")) warningImpliciteConvert(instr);
        left->data.var.is_init = 1;
    }
}


/**
 * Fonction aiguillage des instructions
 * @param instr La racine de l'instruction
 * @param funct_id L'identifier lie a la fonction en cours d'evaluation
 */
static void evalInstr(Node* instr, Identifier* funct_id) {
    switch (instr->label)
    {
    case Affect:
        evalAffect(instr, funct_id);
        break;
    
    default:
        fprintf(stdout, "Instr: %d WIP\n", instr->label);
    }
}


static void evalDeclFonct(Node* decl_funct) {
    Identifier* funct_id = verifHashTable(table_ception->global_funct, decl_funct->firstChild->firstChild->nextSibling->ident);
    printf("\n- %s\n", funct_id->data.func.id);
    // TODO ecriture en-tete + alloc var local
    Node* instr = decl_funct->firstChild->nextSibling->nextSibling->firstChild;
    for (; instr; instr = instr->nextSibling) evalInstr(instr, funct_id);
    // TODO ecriture nettoyage pile + 'ret'
}


void evalTpc() {
    // TODO ecriture en-tete fichier
    Node* decl_funct = root->firstChild->nextSibling;
    for (; decl_funct; decl_funct = decl_funct->nextSibling) evalDeclFonct(decl_funct);
    // TODO ecriture _start si main present
}
