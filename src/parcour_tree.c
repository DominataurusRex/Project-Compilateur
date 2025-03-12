#include <stdio.h>
#include <stdlib.h>
#include "parcour_tree.h"


void parcourFunction(Table* table, Node* node) {
    Node* temp = node->firstChild->firstChild;
    Node* tempChild;
    for (; temp != NULL; temp = temp->nextSibling) {
        tempChild = temp->firstChild;
        for (; tempChild != NULL; tempChild = tempChild->nextSibling) {
            printf("-- %-5s %3s --\n", temp->ident, tempChild->ident);
            if (!verifHash(table, tempChild->ident, temp->ident)) {
                printf("Ajout\n");
                addHash(table, tempChild->ident, temp->ident);
            } else {
                printf("Error\n");
                exit(1);
            }
        }
    }
}