#ifndef __ERROR_H__
#define __ERROR_H__

#include "tree.h"


/**
 * Message d'erreur pour l'utilisation d'un retour de fonction Void
 * Incremente nb_error
 * @param node La node problematique
 */
void errorIgnoredVoid(Node* node);


/**
 * Message d'erreur pour la declaration implicite d'une fonction.
 * Incremente nb_error
 * @param node La node problematique
 */
void errorImpliciteDecl(Node* node);


/**
 * Message d'erreur pour l'absence de main dans le fichier
 * Incremente nb_error
 */
void errorNotMain();


/**
 * Message d'erreur pour une redefinition var/var funct/funct.
 * Incremente nb_error
 * @param node La node problematique
 */
void errorRedefinition(Node* node);


/**
 * Message d'erreur pour une redefinition d'une fonction deja implementee.
 * Incremente nb_error
 * @param node La node problematique
 */
void errorRedefinitionBan(Node* node);


/**
 * Message d'erreur pour une redefinition var/funct.
 * Incremente nb_error
 * @param node La node problematique
 */
void errorRedefinitionType(Node* node);


/**
 * Message d'erreur pour l'utilisation de trop peu d'argument.
 * Incremente nb_error
 * @param node La node problematique
 */
void errorTooFewArgs(Node* node);


/**
 * Message d'erreur pour l'utilisation de trop d'argument.
 * Incremente nb_error
 * @param node La node problematique
 */
void errorTooManyArgs(Node* node);


/**
 * Message d'erreur pour une variable ou une fonction indefinie.
 * incremente nb_error
 * @param node La node problematique
 */
void errorUndeclared(Node* node);


/**
 * Message d'avertissement d'un bloc d'instruction de fonction non-void sans `return`
 * Incremente nb_warning
 * @param node La node problematique
 */
void warningControlReaches(Node* node);


/**
 * Message d'avertissement d'une division par zero
 * Incremente nb_warning
 * @param node La node problematique
 */
void warningDivisionZero(Node* node);


/**
 * Message d'avertissement d'une conversion implicite `char` <- `int`.
 * Incremente nb_warning
 * @param node La node problematique
 * @param param Le nom du parametre dans le cas dans un appel de fonction
 */
void warningImpliciteConvert(Node* node, char* param);


/**
 * @brief 
 * 
 */
void warningMain();


/**
 * Message d'avertissement d'un `return` de fonction non-void renvoyant un void.
 * Incremente nb_warning
 * @param node La node problematique
 */
void warningRetNoValNoVoid(Node* node);


/**
 * Message d'avertissement d'un `return` de fonction void renvoyant une valeur.
 * Incremente nb_warning
 * @param node La node problematique
 */
void warningRetValVoid(Node* node);


/**
 * Message d'avertissement de l'utilisation d'une variable non initialisee.
 * Incremente nb_warning
 * @param node La node problematique
 */
void warningUninitialized(Node* node);


#endif
