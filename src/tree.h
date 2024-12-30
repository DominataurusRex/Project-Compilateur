/* tree.h */

typedef enum {
    Prog,
    DeclVars,
    DeclFonct,
    EnTeteFonct,
    Instr,
    Type,
    StaticType,
    Ident,
    Void,
    Var,
    Funct,
    Char,
    Num,
    Return,
    Affect,
    UnOperator,
    BiOperator,
    Negate,
    Order,
    Compar,
    Or,
    And,
    Equal,
    While,
    If,
    Else,
    Cond,
    Do
    /* list all other node labels, if any */
    /* The list must coincide with the string array in tree.c */
    /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
} label_t;

typedef struct Node {
    label_t label;
    struct Node *firstChild, *nextSibling;
    int lineno;
    char* ident;
    int num;
    char byte;
} Node;

Node *makeNode(label_t label);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node*node);
void printTree(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling
