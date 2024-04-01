#ifndef _TOKENS_H_
#define _TOKENS_H_

typedef enum{
    EOS, // end of string    
    ERRO,
    IDENTIFICADOR,
    NUMERO,
    // operadores
    MENOR,
    MENOR_IGUAL,
    MAIOR,
    MAIOR_IGUAL,
    OP_SOMA, 
    OP_MULT,
    ABRE_PAR,
    FECHA_PAR,
    ABRE_CHAVES,
    FECHA_CHAVES,
    PONTO_VIRGULA,
    // palavras reservadas
    PR_INT,
    PR_BOOL,
    PR_MAIN,
    PR_FUNCTION,
    PR_IF,
    PR_ELSE,
    PR_WHILE,
    PR_VOID,
    PR_TRUE,
    PR_FALSE

} TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
    float atributo_numero;
    char atributo[15];
    char erro[100];
} TInfoAtomo;

#endif