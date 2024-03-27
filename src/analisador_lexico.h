#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum{
    ERRO,
    IDENTIFICADOR,
    NUMERO,
    OP_SOMA,
    OP_MULT,
    EOS
}TAtomo;



typedef struct{
    TAtomo atomo;
    int linha;
    float atributo_numero;
    char atributo_ID[16];
}TInfoAtomo;

void ignora_delimitadores();
TInfoAtomo obter_atomo();
TInfoAtomo reconhece_id();
TAtomo reconhece_num();