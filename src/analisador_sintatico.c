#include "analisador_sintatico.h"

TAtomo lookahead;
TInfoAtomo info_atomo;

char * buffer;

void inicia(){
    abrir_arquivo("teste.txt");
    info_atomo = obter_atomo();
    lookahead = info_atomo.atomo;
    programa();
}

void consome( TAtomo atomo){
    if( lookahead == atomo ){
        info_atomo = obter_atomo();
        lookahead = info_atomo.atomo;
    }
    else{
        printf("linha %d | erro sintatico: esperado [ %s ] encontrado [ %s ]\n", 
                info_atomo.linha, lista_tokens[atomo], lista_tokens[lookahead]);

        exit(1);
    }
}

//  <programa> ::= int main “(” void “)” “{“ <declaracoes> <comandos> “}”
void programa(){
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

// <declaracoes> ::= { <declaracao> } 
void declaracoes(){
    declaracao();
    while(lookahead == PR_INT || lookahead == PR_BOOL){ 
        declaracao();
    }
}

// <declaracao> ::= <tipo> identificador { “,” identificador } “;” 
void declaracao(){
    if (lookahead == PR_INT || lookahead == PR_BOOL)
        consome(lookahead);

    consome(IDENTIFICADOR);

    while(lookahead == VIRGULA){ 
        consome(VIRGULA);
        consome(IDENTIFICADOR);
    }

    consome(PONTO_VIRGULA);
}

// <tipo> ::= [ int | bool ]
void tipo(){
    if(lookahead == PR_INT|| lookahead == PR_BOOL)
        consome(lookahead);
}

// <bloco_comandos> ::= “{“ <comandos> “}” 
void bloco_comandos(){
    consome(ABRE_CHAVES);
    comandos();
    consome(FECHA_CHAVES);
}

// <comandos> ::= { <comando> } 
void comandos(){
    while(lookahead != '}') // TODO
        comando();
}

// <comando> ::= “;” |
//      <bloco_comandos> |
//      <atribuicao> |
//      <comando_if> |
//      <comando_while> |
//      <comando_entrada> |
//      <comando_saida> 
void comando(){
    if (lookahead == ABRE_CHAVES)
        bloco_comandos();
    else if (lookahead == PONTO_VIRGULA)  
        consome(lookahead);
    else if (lookahead == IDENTIFICADOR)  
        atribuicao();
    else if (lookahead == PR_IF)  
        comando_if();
    else if (lookahead == PR_WHILE)  
        comando_while();
    else if (lookahead == PR_SCANF)  
        comando_entrada();
    else if (lookahead == PR_PRINTF)  
        comando_saida();
}

// <atribuicao> ::= identificador “=” <expressao> “;” 
void atribuicao(){
    consome(IDENTIFICADOR);
    consome(OP_ATRIBUICAO);
    expressao();
    consome(PONTO_VIRGULA);
}

// <comando_if> ::= if “(” <expressao> “)” <comando>
//      [else <comando>] 
void comando_if(){
    consome(PR_IF);
    consome(ABRE_PAR);
    expressao();
    consome(FECHA_PAR);
    comando();
    
    if (lookahead == PR_ELSE){
        consome(lookahead); // TODO implementar condicional
        comando();
    }
}

// <comando_while> ::= while “(” <expressao> “)” <comando> 
void comando_while(){
    consome(PR_WHILE);
    consome(ABRE_PAR);
    expressao();
    consome(FECHA_PAR);
    comando();
}

// <comando_entrada> ::= scanf “(“ <lista_variavel> “)” “;”
void comando_entrada(){
    consome(PR_SCANF);
    consome(ABRE_PAR);
    // lista_variavel(); // TODO ver o que é isso
    consome(IDENTIFICADOR);
    consome(FECHA_PAR);
    consome(PONTO_VIRGULA);
}

// <comando_saida> ::= printf “(“ <expressao> { “,” <expressao> } “)” “;” 
void comando_saida(){
    consome(PR_PRINTF);
    consome(ABRE_PAR);
    expressao();
    
    while(lookahead == VIRGULA){
        consome(lookahead);
        expressao();    
    }

    consome(FECHA_PAR);
    consome(PONTO_VIRGULA);
}

// <expressao> ::= <expressao_logica> { “||” <expressao_logica> } 
void expressao(){
    expressao_logica();

    while(lookahead == OP_OR){ 
        consome(lookahead);
        expressao_logica();
    }   
}

// <expressao_logica>::= <expressao_relacional> { “&&” <expressao_relacional> }
void expressao_logica(){
    expressao_relacional();

    while(lookahead == OP_AND){
        consome(lookahead);
        expressao_logica();
    }   
}

// <expressao_relacional> ::= <expressao_adicao>
//      [ <op_relacional> <expressao_adicao> ]
void expressao_relacional(){
    expressao_adicao();

    if (
        lookahead == OP_MENOR ||
        lookahead == OP_MENOR_IGUAL ||
        lookahead == OP_IGUAL ||
        lookahead == OP_DIFERENTE ||
        lookahead == OP_MAIOR ||
        lookahead == OP_MAIOR_IGUAL
    ){
        op_relacional();
        expressao_adicao();
    }
}

// <op_relacional> ::= “<” | “<=” | “==” | “!=” | “>” | “>=” 
void op_relacional(){
     if (
        lookahead == OP_MENOR ||
        lookahead == OP_MENOR_IGUAL ||
        lookahead == OP_IGUAL ||
        lookahead == OP_DIFERENTE ||
        lookahead == OP_MAIOR ||
        lookahead == OP_MAIOR_IGUAL
    ){
        consome(lookahead);
    }
}

// <expressao_adicao> ::= <expressao_multi> { (“+” | “−” ) <expressao_multi> }
void expressao_adicao(){
    expressao_multi();

    while(lookahead == OP_SOMA || lookahead == OP_SUBTR){
        consome(lookahead);
        expressao_multi();
    }
}

// <expressao_multi>::= <operando> { ( “*” | “/” ) <operando> }
void expressao_multi(){
    operando();

     while(lookahead == OP_MULT || lookahead == OP_DIV){
        consome(lookahead);
        operando();
    }
}

// <operando> ::= identificador |
//      numero |
//      true |
//      false |
//      <expressao> 
void operando(){
     if (
        lookahead == IDENTIFICADOR ||
        lookahead == NUMERO ||
        lookahead == PR_TRUE ||
        lookahead == PR_FALSE
        // TODO <expressao>
    ){
        consome(lookahead);
    }
}