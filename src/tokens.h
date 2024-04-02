#ifndef TOKENS_H
#define TOKENS_H

typedef enum{
    EOS, // end of string    
    ERRO,
    IDENTIFICADOR,
    NUMERO,
    // operador
    OP_IGUAL,
    OP_DIFERENTE,
    OP_MENOR,
    OP_MENOR_IGUAL,
    OP_MAIOR,
    OP_MAIOR_IGUAL,
    OP_SOMA, 
    OP_SUBTR,
    OP_MULT,
    OP_DIV,
    OP_OR,
    OP_AND,
    // palavra reservada
    PR_INT,
    PR_BOOL,
    PR_MAIN,
    PR_SCANF,
    PR_PRINTF,
    PR_IF,
    PR_ELSE,
    PR_WHILE,
    PR_VOID,
    PR_TRUE,
    PR_FALSE,
    // outros
    VIRGULA,
    ABRE_PAR,
    FECHA_PAR,
    ABRE_CHAVES,
    FECHA_CHAVES,
    PONTO_VIRGULA,
} TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
    float atributo_numero;
    char atributo[15];
    char erro[100];
} TInfoAtomo;

#endif