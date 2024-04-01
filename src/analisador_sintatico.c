#include "analisador_sintatico.h"
#include "tokens.h"

TAtomo lookahead;
TInfoAtomo info_atomo;

char * lista_tokens_2[]={    
        "Fim de buffer(EOS)",
        "Erro Lexico",
        "identificador",
        "numero",
        "menor",
        "menor_igual",
        "maior",
        "maior_igual",
        "+",
        "*",
        "abre_parenteses",
        "fecha_parenteses",
        "abre_chaves",
        "fecha_chaves",
        " ; ",
        "int",
        "bool",
        "main",
        "funcao",
        "if",
        "else",
        "while",
        "void",
        "true",
        "false",
    };

void inicia(){
    info_atomo = obter_atomo();
    lookahead = info_atomo.atomo;

    programa();
}

void programa(){
    //  int main “(” void “)” “{“ <declaracoes> <comandos> “}”
    consome(PR_INT);
    consome(PR_MAIN);
    consome(ABRE_PAR);
    consome(PR_VOID);
    consome(FECHA_PAR);
    consome(ABRE_CHAVES);

    declaracoes();
    comandos();

    consome(FECHA_CHAVES);
}

void declaracoes(){}

void comandos(){}

void consome( TAtomo atomo){
    if( lookahead == atomo ){
        info_atomo = obter_atomo();
        lookahead = info_atomo.atomo;
    }
    else{
        printf("linha %d | erro sintatico: esperado [ %s ] encontrado [ %s ]\n", 
                info_atomo.linha, lista_tokens_2[atomo], lista_tokens_2[lookahead]);

        exit(1);
    }

}
