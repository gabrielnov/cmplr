#include "analisador_lexico.h"

int linha = 1;
char *buffer = "if\n else\n _var1 0xF ";

void ignora_delimitadores(){
    while(
        *buffer == ' ' || *buffer == '\n' || *buffer == '\t' || *buffer == '\r'){
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
    else if(isalpha(*buffer))
        infoAtomo = reconhece_palavra_reservada();

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
        strncpy(infoAtomo.atributo_ID, iniLexema, buffer - iniLexema);
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
    
    if (
        *buffer != ' '  && 
        *buffer != '\n' && 
        *buffer != '\r' &&
        *buffer != '\t' &&
        *buffer != '\0' 
        )
        return ERRO;        
        
    return NUMERO;
}

TInfoAtomo reconhece_palavra_reservada(){
    const int MAX_LENGTH = 6;
    char lexema[MAX_LENGTH];
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = ERRO;

    int i = 0;

    while (
        *buffer != ' '  && 
        *buffer != '\n' && 
        *buffer != '\r' &&  
        *buffer != '\t' && 
        *buffer != '\0'
        )
    {
        if (i > MAX_LENGTH)
            return infoAtomo;
        
        lexema[i] = *buffer;
        buffer++;
        i++;
    }
    
    if (
        strcmp(lexema, "while") == 0 ||
        strcmp(lexema, "if") == 0 ||
        strcmp(lexema, "else") == 0 ||
        strcmp(lexema, "void") == 0 ||
        strcmp(lexema, "int") == 0 ||
        strcmp(lexema, "bool") == 0 ||
        strcmp(lexema, "true") == 0 ||
        strcmp(lexema, "false") == 0 ||
        strcmp(lexema, "main") == 0 ||
        strcmp(lexema, "printf") == 0 ||
        strcmp(lexema, "scanf") == 0
    ) infoAtomo.atomo = PALAVRA_RESERVADA; 

    strcpy(infoAtomo.palavra_reservada, lexema);
    
    return infoAtomo;
}

TAtomo lookahead;
TInfoAtomo infoAtomo;

int main(void){
    printf("Analisando:\n%s\n",buffer);

    infoAtomo = obter_atomo();
    printf("%s \n", strAtomo[infoAtomo.atomo]);
        
}