#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "compil.h"
#include "parcour_tree.h"
#include "table_sym.h"
#include "tree.h"

int yyparse(void);
extern Node* root;
extern FILE* yyin;
extern TableCeption* table_ception;
char* file_name;
int error_flag = 0;
int show_tree;
int show_symtabs;

static struct option long_options[] = {
    {"tree", no_argument, 0, 't'},
    {"help", no_argument, 0, 'h'},
    {"symtabs", no_argument, 0, 's'},
    {0, 0, 0, 0}
};

const char *mess_help = 
    "UTILISATION:\n" 
    "\t./tpcc [OPTIONS] < redirection entrée fichier .tpc\n"
    "\t./tpcc [OPTIONS] FILE.tpc\n"
    "\n"
    "OPTION:\n"
    "\t-t, --tree: Affiche l'arbre abstrait sur la sortie standard\n"
    "\t-h, --help: Affiche cette description de l'interface utilisateur et termine l'exécution\n"
    "\t-s, --symtabs affiche toutes les tables des symboles sur la sortie standard\n"
    "\n"
    "RETOUR:\n"
    "\t- 0: Aucune erreur lexicale ou syntaxique\n"
    "\t- 1: Si il contient une erreur lexicale ou syntaxique\n"
    "\t- 2: s’il contient une erreur sémantique\n"
    "\t- 3 ou plus: pour les autres sortes d’erreurs :\n"
    "\t\tligne de commande\n"
    "\t\tfonctionnalité non implémentée\n"
    "\t\tmémoire insuffisante...\n";


    /**
     * Permet de gerer les option avec getopt
     */
int getOption(int argc, char** argv) {
    int opt;
    int option_index;
    show_symtabs = 0;
    show_tree = 0;
    while ((opt = getopt_long(argc, argv, "ths", long_options, &option_index)) != -1) {
        switch(opt) {
        case 't':
            show_tree = 1;
            break;
        case 'h':
            fprintf(stdout, "%s", mess_help);
            return 1;
        case 's':
            show_symtabs = 1;
            break;
        case '?':
            printf("Option invalide. Utilisez -h ou --help pour plus d'informations.\n");
            break;
        default:
            abort();
        }
    }
    return 0;
}


/**
 * Permet de recuperer un fichier donnee en argument de l'appel
 */
int getFile(int argc, char** argv) {
    if (optind < argc) {
        yyin = fopen(argv[optind], "r");
        if (!yyin) {
            fprintf(stderr, "\033[31;1merror\033[0m file not found \033[1m‘%s’\033[0m\n", argv[optind]);
            return 1;
        }
        file_name = argv[optind];
    } else {
        file_name = "_anonymous.tpc";
    }
    return 0;
}

int main(int argc, char **argv) {
    if (getOption(argc, argv)) return 0;
    if (getFile(argc, argv)) return 1;
    int value = yyparse();
    fprintf(stdout, "%d\n", value);
    if (!value) {
        if (show_tree) printTree(root);
        fillTableCeption();
        calcType();
        if (error_flag) return 2;
        if (show_symtabs) showCeption(table_ception);
        /*
        createNasm();
        */
        deleteTree(root);
        deleteTableCeption(table_ception);
        fclose(yyin);
    }
    return 0;
}
