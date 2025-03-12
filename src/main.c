#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "parcour_tree.h"
#include "table_sym.h"

int yyparse(void);
extern Node* root;

static struct option long_options[] = {
    {"tree", no_argument, 0, 't'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

const char *mess_help = 
    "Utilisation: ./tpcas [OPTIONS] < redirection entrée fichier TPC\n"
    "OPTION:\n"
    "-t, --tree: Affiche l'arbre abstrait sur la sortie standard\n"
    "-h, --help: Affiche cette description de l'interface utilisateur et termine l'exécution\n"
    "\n"
    "Retour:\n"
    "0: Aucune erreur lexicale ou syntaxique\n"
    "1: Si il contient une erreur lexicale ou syntaxique\n";

int main(int argc, char **argv) {
    int opt;
    int option_index = 0;
    int show_tree = 0;
    while ((opt = getopt_long(argc, argv, "th", long_options, &option_index)) != -1) {
        switch(opt) {
        case 't':
            show_tree = 1;
            break;
        case 'h':
            fprintf(stdout, "%s", mess_help);
            return 0;
        case '?':
            printf("Option invalide. Utilisez -h ou --help pour plus d'informations.\n");
            break;
        default:
            abort();
        }
    }
    int value = yyparse();
    if (show_tree) printTree(root);
    fprintf(stdout, "%d\n", value);
    Table* table = initTableHash("GlobalDecl");
    parcourFunction(table, root);
    showHash(table);
    deleteTree(root);
    return 0;
}
