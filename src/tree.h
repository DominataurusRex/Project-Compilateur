/* tree.h */

typedef enum {
    Prog,           // 0
    DeclVars,
    DeclFonct,      // 2
    EnTeteFonct,
    Instr,          // 4
    Type,
    StaticType,     // 6
    Ident,
    Void,           // 8
    Var,
    Funct,          // 10
    Char,
    Num,            // 12
    Return,
    Affect,         // 14
    UnOperator,
    BiOperator,     // 16
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
    int line;
    int column;
} Node;

Node *makeNode(label_t label);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node*node);
void printTree(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling
