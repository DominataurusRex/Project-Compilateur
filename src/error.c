#include <stdio.h>
#include "error.h"

extern char* file_name;
extern int nb_error;
extern int nb_warning;


void errorRedefinition(Node* node) {
    fprintf(
        stderr,
        "\033[1m%s:%d:%d:\033[31;1m error:\033[0m redefinition of \033[1m‘%s’\033[0m\n\n",
        file_name,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}


void errorRedefinitionType(Node* node) {
    fprintf(
        stderr,
        "\033[1m%s:%d:%d:\033[31;1m error:\033[0;1m ‘%s’\033[0m redeclared as different kind of symbol\n\n",
        file_name,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}


void errorUndeclared(Node* node) {
    fprintf(
        stderr, "%s:%d:%d: \033[31;1merror:\033[0;1m ‘%s’\033[0m undeclared (first use in this function)\n\n",
        file_name,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}


void warningImpliciteConvert(Node* node) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[35;1m warning:\033[0m implicite convertion \033[1m‘%s’\033[0m (char <- int)\n\n",
        file_name,
        node->line,
        node->column,
        node->ident
    );
    nb_warning++;
}


void warningUninitialized(Node* node) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[35;1m warning: \033[0;1m‘%s’\033[0m is used uninitialized\n\n",
        file_name,
        node->line,
        node->column,
        node->ident
    );
    nb_warning++;
}


void warningVarMain(Node* node) {
    fprintf(
        stderr,
        "\033[1m%s:%d:%d:\033[35;1m warning:\033[0;1m ‘main’\033[0m is usually a function\n\n",
        file_name,
        node->line,
        node->column
    );
    nb_warning++;
}
