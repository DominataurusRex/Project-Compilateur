#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "compil.h"
#include "parcour_tree.h"
#include "table_sym.h"
#include "tree.h"


int yyparse(void);                          // Fonction du parser
extern Node* root;                          // Racine de l'arbre syntaxique
extern FILE* yyin;                          // Stream du fichier d'entre
extern TableCeption* table_ception;         // Tables des symboles
char* file_name;                            // Nom du fichier d'entre
int nb_error = 0;                           // Nombre d'erreur
int nb_warning = 0;                         // Nombre de warning
int show_tree;                              // Booleen pour afficher l'arbre
int show_symtabs;                           // Booleen pour afficher les table des symboles

static struct option long_options[] = {
    {"tree", no_argument, 0, 't'},
    {"help", no_argument, 0, 'h'},
    {"symtabs", no_argument, 0, 's'},
    {0, 0, 0, 0}
};                                          // Structure pour getopt

const char *mess_help =                     // Message d'aide
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
 * @param argc Le nombre d'argument
 * @param argv La liste des arguments
 * @return La continuation du programme ou non
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
 * @param argc Le nombre d'argument
 * @param argv La liste des arguments
 * @return L'obtention du fichier ou non
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
    if (getFile(argc, argv)) return 3;
    int value = yyparse();
    if (!value) {
        if (show_tree) printTree(root);
        fillTableCeption();
        if (!nb_error) {
            evalTpc();
        }
        if (!nb_error) {
            if (show_symtabs) showCeption(table_ception);
        }
        deleteTree(root);
        deleteTableCeption(table_ception);
        fclose(yyin);
    } else {
        return value;
    }
    if (nb_warning) fprintf(stdout, "\033[35;1mNb warning:\033[0m %d\n", nb_warning);
    if (nb_error) {
        fprintf(stdout, "\033[31;1mNb error:\033[0m %d\n", nb_error);
        return 2;
    }
    return 0;
}
