#include "analisador_sintatico.h"

TAtomo lookahead;
TInfoAtomo info_atomo;

void consome( TAtomo atomo ){
    if( lookahead == atomo ){
        info_atomo = obter_atomo();
        lookahead = info_atomo.atomo;
    }
    else{
        printf("erro sintatico: esperado [%s] encontrado [%s]\n", 
                str_atomo[atomo], str_atomo[lookahead]);

        exit(1);
    }

}