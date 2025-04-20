#ifndef __ERROR_H__
#define __ERROR_H__

#include "tree.h"


/**
 * Message d'erreur pour une redefinition var/var funct/funct.
 * Incremente nb_error
 * @param node La node problematique
 */
void errorRedefinition(Node* node);


/**
 * Message d'erreur pour une redefinition var/funct.
 * Incremente nb_error
 * @param node La node problematique
 */
void errorRedefinitionType(Node* node);


/**
 * Message d'erreur pour une variable ou une fonction indefinie.
 * incremente nb_error
 * @param node La node problematique
 */
void errorUndeclared(Node* node);


/**
 * Message d'avertissement d'une conversion implicite `char` <- `int`.
 * Incremente nb_warning
 * @param node La node problematique
 */
void warningImpliciteConvert(Node* node);


/**
 * Message d'avertissement de l'utilisation d'une variable non initialisee.
 * Incremente nb_warning
 * @param node La node problematique
 */
void warningUninitialized(Node* node);


/**
 * Message d'avertissement de la definition de main comme variable.
 * Incremente nb_warning
 * @param node La node problematique
 */
void warningVarMain(Node* node);

#endif
