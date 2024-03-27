#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> 

char *strAtomo[]={    
    "Fim de buffer(EOS)",
    "Erro Lexico",
    "IDENTIFICADOR",
    "NUMERO",
    "PALAVRA_RESERVADA",
    "+",
    "*"
};

typedef enum{
    EOS, // end of string    
    ERRO,
    IDENTIFICADOR,
    NUMERO,
    PALAVRA_RESERVADA,
    // operadores
    OP_SOMA, 
    OP_MULT
}TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
    float atributo_numero;
    char atributo_ID[16];
    char palavra_reservada[6];
}TInfoAtomo;

void ignora_delimitadores();
TInfoAtomo obter_atomo();
TInfoAtomo reconhece_id();
TInfoAtomo reconhece_palavra_reservada();
TInfoAtomo reconhece_numero();