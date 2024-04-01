#include "analisador_sintatico.h"
#include "tokens.h"

TAtomo lookahead;
TInfoAtomo info_atomo;

char * lista_tokens_2[]={    
        "Fim de buffer(EOS)",
        "Erro Lexico",
        "identificador",
        "numero",
        "==",
        "!="
        "<",
        "<=",
        ">",
        ">=",
        "+",
        "*",
        "||",
        "&&",
        "(",
        ")",
        "{",
        "}",
        ";",
        "int | bool",
        "main",
        "scanf",
        "printf",
        "if",
        "else",
        "while",
        "void",
        "true",
        "false",
        ","
    };

void inicia(){
    info_atomo = obter_atomo();
    lookahead = info_atomo.atomo;

    programa();
}

void programa(){
    //  int main “(” void “)” “{“ <declaracoes> <comandos> “}”
    consome(PR_TIPO);
    consome(PR_MAIN);
    consome(ABRE_PAR);
    consome(PR_VOID);
    consome(FECHA_PAR);
    consome(ABRE_CHAVES);

    declaracoes();
    comandos();

    consome(FECHA_CHAVES);
}

void declaracoes(){
    // while(1){ TODO implementar repetição
        declaracao();
    // }
}

void declaracao(){
    consome(PR_TIPO);
    consome(IDENTIFICADOR);

    // while(1){ TODO implementar repetição
        // consome(VIRGULA);
        // consome(IDENTIFICADOR);
    // }

    consome(PONTO_VIRGULA);
}

void bloco_comandos(){
    consome(ABRE_CHAVES);
    comandos();
    consome(FECHA_CHAVES);
}

void comandos(){

}

void comando(){

}

void atribuicao(){
    consome(IDENTIFICADOR);
    consome(OP_IGUAL);
    expressao();
    consome(PONTO_VIRGULA);
}

void comando_if(){
    consome(PR_IF);
    consome(ABRE_PAR);
    expressao();
    consome(FECHA_PAR);
    comando();
    // consome(PR_ELSE); // TODO implementar condicional
    // comando();
}

void comando_while(){
    consome(PR_WHILE);
    consome(ABRE_PAR);
    expressao();
    consome(FECHA_PAR);
    comando();
}

void comando_entrada(){
    consome(PR_SCANF);
    consome(ABRE_PAR);
    // lista_variavel(); // TODO ver o que é isso
    consome(FECHA_PAR);
    consome(PONTO_VIRGULA);
}

void comando_saida(){
    consome(PR_PRINTF);
    consome(ABRE_PAR);
    expressao();
    
    // while(1){ // TODO implementar repetição
    //  consome(VIRGULA);
    //  expressao();    
    // }

    consome(FECHA_PAR);
    consome(PONTO_VIRGULA);
}

void expressao(){
    expressao_logica();

    // while(1){ TODO implementar repetição
        // consome(OP_OR);
        // expressao_logica();
    // }   
}

void expressao_logica(){
    expressao_relacional();

    // while(1){ TODO implementar repetição
        // consome(OP_AND);
        // expressao_logica();
    // }   
}

void expressao_relacional(){
    expressao_adicao();

    // TODO implementar condicional 
    // op_relacional();
    // expressao_adicao();
}

void op_relacional(){
    //TODO implementar condicionais

    consome(OP_MENOR);

    consome(OP_MENOR_IGUAL);

    consome(OP_IGUAL);

    consome(OP_DIFERENTE);

    consome(OP_MAIOR);

    consome(OP_MAIOR_IGUAL);
}

void expressao_adicao(){
    expressao_multi();

    // TODO implementar repetição
    // consome(OP_SOMA); consome(OP_SUBTR); // TODO implementar condicional
    // expressao_multi()
}

void expressao_multi(){
    operando();

    // TODO implementar repetição
    // consome(OP_MULT); consome(OP_DIV); // TODO implementar condicional
    // operando();
}

void operando(){
    // TODO implementar condicional
    consome(IDENTIFICADOR);
    consome(NUMERO);
    consome(PR_TRUE);
    consome(PR_FALSE);
    expressao();
    //
}
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
