#include "analisador_lexico.h"

int linha = 1;
char *buffer = "0x785FA\n ";

void ignora_delimitadores(){
    while(*buffer == ' ' || *buffer == '\n' || *buffer == '\t' || *buffer == '\r'){
        if(*buffer=='\n')
            linha++;

        buffer++;
    }
}

TInfoAtomo obter_atomo(){
    TInfoAtomo infoAtomo;
    infoAtomo.atomo=ERRO;
    
    ignora_delimitadores();

    if(*buffer == '+' || *buffer == '-'){
        buffer++;
        infoAtomo.atomo = OP_SOMA;
    }
    else if(*buffer == '*' || *buffer == '/'){
        buffer++;
        infoAtomo.atomo = OP_MULT;
    }
    else if(*buffer == '_'){
        buffer++; // opcional?
        infoAtomo = reconhece_id();
    }
    else if(*buffer == '0'){
        buffer++; // opcional?
        infoAtomo.atomo = reconhece_num();        
    }
    else if(*buffer == '\0')
        infoAtomo.atomo = EOS;
    
    infoAtomo.linha = linha;
    return infoAtomo;
}

TInfoAtomo reconhece_id(){
    TInfoAtomo infoAtomo;
    char *iniLexema;
    iniLexema = buffer;

q0:
    if(isalpha(*buffer)){
        buffer++;
        goto q1;
    } else
        infoAtomo.atomo = ERRO;
q1:
    if(isalpha(*buffer) || isdigit(*buffer)){
        buffer++;    
        goto q1;
    } else
        infoAtomo.atomo = ERRO;
    

    if( buffer - iniLexema <= 15 ){ // maximo de quinze characteres, incluindo o underline que foi removido anteriormente
        // referencia:https://cplusplus.com/reference/cstring/strncpy/
        strncpy(infoAtomo.atributo_ID,iniLexema, buffer - iniLexema);
        infoAtomo.atributo_ID[buffer-iniLexema] = '\0'; // finaliza string
        infoAtomo.atomo = IDENTIFICADOR;
    }else
        infoAtomo.atomo = ERRO;

    return infoAtomo;
}

TAtomo reconhece_num(){

q0:
    if(*buffer == 'x'){
        buffer++;
        goto q1;
    }else
        return ERRO; // [outro]
q1:
    if(
        (*buffer >= 65 && * buffer <= 70 ) ||
        (*buffer >= 48 && * buffer <= 57 ) 
    ){
        buffer++;
        goto q1;
    }
    
    if (*buffer != '\0' && *buffer != ' ' && *buffer != '\n' && *buffer != '\r'){
        return ERRO;
    }      
        
    
    return NUMERO;
}


TAtomo lookahead;
TInfoAtomo infoAtomo;

int main(void){
    printf("Analisando:\n%s\n",buffer);
    infoAtomo = obter_atomo();

    char *strAtomo[]={"Erro Lexico","IDENTIFICADOR","NUMERO","+","*","Fim de buffer(EOS)"};

    printf("%s\n", strAtomo[infoAtomo.atomo]);


}