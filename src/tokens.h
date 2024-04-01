#ifndef _TOKENS_H_
#define _TOKENS_H_

typedef enum{
    EOS, // end of string    
    ERRO,
    IDENTIFICADOR,
    NUMERO,
    // operadores
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
    ABRE_PAR,
    FECHA_PAR,
    ABRE_CHAVES,
    FECHA_CHAVES,
    PONTO_VIRGULA,
    // palavras reservadas
    PR_TIPO,
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
    VIRGULA
} TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
    float atributo_numero;
    char atributo[15];
    char erro[100];
} TInfoAtomo;

#endif