#include <stdio.h>
#include "error.h"

extern char* file_path;     // Le nom du fichier
extern int nb_error;        // Le nombre d'erreur
extern int nb_warning;      // Le nombre de warning



void errorCalledNotFunction(Node* node) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[31;1m error:\033[0m called object \033[0;1m‘%s’\033[0m is not a function\n\n",
        file_path,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}


void errorIgnoredVoid(Node* node) {
    fprintf(
        stderr,
        "\033[1m%s:%d:%d:\033[31;1m error:\033[0m void value not ignored as it ought to be\n\n",
        file_path,
        node->line,
        node->column
    );
    nb_error++;
}


void errorImpliciteDecl(Node* node) {
    fprintf(
        stderr,
        "\033[1m%s:%d:%d:\033[31;1m error:\033[0m implicit declaration of function \033[1m‘%s’\033[0m\n\n",
        file_path,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}

void errorNotMain(){
    fprintf(
        stderr,
        "\033[1m%s:\033[31;1m error:\033[0m no declaration of function \033[1m‘main’\033[0m\n\n",
        file_path
    );
    nb_error++;
}


void errorRedefinition(Node* node) {
    fprintf(
        stderr,
        "\033[1m%s:%d:%d:\033[31;1m error:\033[0m redefinition of \033[1m‘%s’\033[0m\n\n",
        file_path,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}


void errorRedefinitionBan(Node* node) {
    fprintf(
        stderr,
        "\033[1m%s:%d:%d:\033[31;1m error:\033[0m redefinition of the already integrated \033[1m‘%s’\033[0m function\n\n",
        file_path,
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
        file_path,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}


void errorRetNoValNoVoid(Node* node) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[31;1m error:\033[0;1m ‘return’\033[0m with no value, in function returning non-void\n\n",
        file_path,
        node->line,
        node->column
    );
    nb_error++;
}


void errorRetValVoid(Node* node) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[31;1m error:\033[0;1m ‘return’\033[0m with a value, in function returning void\n\n",
        file_path,
        node->line,
        node->column
    );
    nb_error++;
}


void errorTooFewArgs(Node* node) {
    fprintf(
        stderr,
        "\033[1m%s:%d:%d:\033[31;1m error:\033[0m too few arguments to function ‘%s’\033[0m\n\n",
        file_path,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}


void errorTooManyArgs(Node* node) {
    fprintf(
        stderr,
        "\033[1m%s:%d:%d:\033[31;1m error:\033[0m too many arguments to function ‘%s’\033[0m\n\n",
        file_path,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}


void errorUndeclared(Node* node) {
    fprintf(
        stderr, "%s:%d:%d: \033[31;1merror:\033[0;1m ‘%s’\033[0m undeclared (first use in this function)\n\n",
        file_path,
        node->line,
        node->column,
        node->ident
    );
    nb_error++;
}


void warningControlReaches(Node* node) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[35;1m warning:\033[0m control reaches end of non-void function\n\n",
        file_path,
        node->line,
        node->column
    );
    nb_warning++;
}


void warningDivisionZero(Node* node) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[35;1m warning:\033[0m division by zero\n\n",
        file_path,
        node->line,
        node->column
    );
    nb_warning++;
}


void warningImpliciteConvert(Node* node, char* param) {
    if (!param) fprintf(
        stderr, "\033[1m%s:%d:%d:\033[35;1m warning:\033[0m implicite convertion \033[1m‘%s’\033[0m (char <- int)\n\n",
        file_path,
        node->line,
        node->column,
        node->ident
    );
    else fprintf(
        stderr, "\033[1m%s:%d:%d:\033[35;1m warning:\033[0m implicite convertion of arguments \033[1m‘%s’\033[0m (char <- int) in function \033[1m‘%s’\033[0m\n\n",
        file_path,
        node->line,
        node->column,
        param,
        node->ident
    );
    nb_warning++;
}


void warningMain() {
    fprintf(
        stderr,
        "\033[1m%s:\033[35;1mwarning:\033[0m \033[1m‘main’\033[0m function not signature like \033[1m‘int main(void)’\033[0m\n\n",
        file_path
    );
    nb_warning++;
}


void warningUninitialized(Node* node) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[35;1m warning:\033[0;1m ‘%s’\033[0m is used uninitialized\n\n",
        file_path,
        node->line,
        node->column,
        node->ident
    );
    nb_warning++;
}


void warningUnusedFunct(char* name, int line, int column) {
    fprintf(
        stderr, 
        "\033[1m%s:%d:%d:\033[35;1m warning:\033[0;1m ‘%s’\033[0m defined but not used\n\n",
        file_path,
        line,
        column,
        name
    );
    nb_warning++;
}


void warningUnusedSetVar(char* var, int line, int column) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[35;1m warning:\033[0m variable \033[1m‘%s’\033[0m set but not used\n",
        file_path,
        line,
        column,
        var
    );
    nb_warning++;
}


void warningUnusedVar(char* var, int line, int column) {
    fprintf(
        stderr, "\033[1m%s:%d:%d:\033[35;1m warning:\033[0m unused variable \033[1m‘%s’\033\n",
        file_path,
        line,
        column,
        var
    );
    nb_warning++;
}
