/* tree.c */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

static const char *StringFromLabel[] = {
    "Prog",
    "DeclVars",
    "DeclFonct",
    "EnTeteFonct",
    "Instr",
    "Type",
    "StaticType",
    "Ident",
    "Void",
    "Var",
    "Funct",
    "Char",
    "Num",
    "Return",
    "Affect",
    "UnOperator",
    "BiOperator",
    "Negate",
    "Order",
    "Compar",
    "Or",
    "And",
    "Equal",
    "While",
    "If",
    "Else",
    "Cond",
    "Do"
    /* list all other node labels, if any */
    /* The list must coincide with the label_t enum in tree.h */
    /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
};

Node *makeNode(label_t label) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        printf("Run out of memory\n");
        exit(1);
    }
    node->label = label;
    node-> firstChild = node->nextSibling = NULL;
    node->num = 0;
    node->byte = 0;
    node->ident = NULL;
    return node;
}

void addSibling(Node *node, Node *sibling) {
    Node *curr = node;
    while (curr->nextSibling != NULL) {
        curr = curr->nextSibling;
    }
    curr->nextSibling = sibling;
}

void addChild(Node *parent, Node *child) {
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    }
    else {
        addSibling(parent->firstChild, child);
    }
}

void deleteTree(Node *node) {
    if (node->firstChild) {
        deleteTree(node->firstChild);
    }
    if (node->nextSibling) {
        deleteTree(node->nextSibling);
    }
    free(node);
}

void printTree(Node *node) {
    static bool rightmost[128]; // tells if node is rightmost sibling
    static int depth = 0;       // depth of current node
    for (int i = 1; i < depth; i++) { // 2502 = vertical line
        printf(rightmost[i] ? "    " : "\u2502   ");
    }
    if (depth > 0) { // 2514 = L form; 2500 = horizontal line; 251c = vertical line and right horiz 
        printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
    }
    printf("%s", StringFromLabel[node->label]);

    if (node->ident != NULL) {
        printf(": %s", node->ident);
    }

    if (node->label == Num) {
        printf(": %d", node->num);
    }

    if (node->label == Char || node->label == UnOperator || node->label == BiOperator) {
        printf(": %c", node->byte);
    }

    printf("\n");
    depth++;
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
        rightmost[depth] = (child->nextSibling) ? false : true;
        printTree(child);
    }
    depth--;
}
