#include "analisador_lexico.h"

int linha = 1;
char *buffer = "0x123;\n"
                "int _teste;\n"
                "scanf();"
                ;

void ignora_delimitadores(){
    while(
        *buffer == ' ' || *buffer == '\n' || *buffer == '\t' || *buffer == '\r'
        ){
        if(*buffer=='\n')
            linha++;

        buffer++;
    }
}

TInfoAtomo obter_atomo(){
    TInfoAtomo infoAtomo;
    infoAtomo.atomo=ERRO;
    
    ignora_delimitadores();

    if(*buffer == '\0')
        infoAtomo.atomo = EOS;
    else if(*buffer == ';'){
        buffer++;
        infoAtomo.atomo = PONTO_VIRGULA;
    }
    else if(*buffer == ')'){
        buffer++;
        infoAtomo.atomo = FECHA_PAR;
    }
    else if(*buffer == '('){
        buffer++;
        infoAtomo.atomo = ABRE_PAR;
    }
    else if(*buffer == ')'){
        buffer++;
        infoAtomo.atomo = FECHA_PAR;
    }
    else if(*buffer == '{'){
        buffer++;
        infoAtomo.atomo = ABRE_CHAVES;
    }
    else if(*buffer == '}'){
        buffer++;
        infoAtomo.atomo = FECHA_CHAVES;
    }
    else if(*buffer == '*' || *buffer == '/'){
        buffer++;
        infoAtomo.atomo = OP_MULT;
    }
    else if(*buffer == '+' || *buffer == '-'){
        buffer++;
        infoAtomo.atomo = OP_SOMA;
    }
    else if(*buffer == '_')
        infoAtomo = reconhece_id();
    else if(*buffer == '0')
        infoAtomo = reconhece_numero();        
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
    if (*buffer == '_'){
        buffer++;
        goto q1;
    } else infoAtomo.atomo = ERRO;
q1:
    if(isalpha(*buffer)){
        buffer++;
        goto q2;
    } else infoAtomo.atomo = ERRO;
q2:
    if(isalpha(*buffer) || isdigit(*buffer)){
        buffer++;    
        goto q1;
    } else infoAtomo.atomo = ERRO;
    
    if( buffer - iniLexema <= 15 ){ // maximo de quinze characteres por identificador
        strncpy(infoAtomo.atributo, iniLexema, buffer - iniLexema);
        infoAtomo.atributo[buffer-iniLexema] = '\0'; // finaliza string
        infoAtomo.atomo = IDENTIFICADOR;
    } else infoAtomo.atomo = ERRO;

    if (infoAtomo.atomo == ERRO) 
        strcpy(infoAtomo.erro, iniLexema);

    return infoAtomo;
}

TInfoAtomo reconhece_numero(){
    char *iniLexema;
    iniLexema = buffer;
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = NUMERO;

q0:
    if(*buffer == '0'){
        buffer++;
        goto q1;
    } else infoAtomo.atomo = ERRO; 
q1:
    if(*buffer == 'x'){
        buffer++;
        goto q2;
    } else infoAtomo.atomo = ERRO; 
q2:
    if(
        (*buffer >= 65 && * buffer <= 70 ) ||
        (*buffer >= 48 && * buffer <= 57 ) 
    ){
        buffer++;
        goto q2;
    }
    
    if (
        *buffer != ' '  && 
        *buffer != '\n' && 
        *buffer != '\r' &&
        *buffer != '\t' &&
        *buffer != '\0' 
        )
    { infoAtomo.atomo = ERRO; }

    if (infoAtomo.atomo == ERRO) 
        strcpy(infoAtomo.erro, iniLexema);

    // convertendo hex para dec
    infoAtomo.atributo_numero = strtol(iniLexema, (char**)NULL, 16);

    return infoAtomo;
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

    strcpy(infoAtomo.atributo, lexema);
    
    return infoAtomo;
}

TAtomo lookahead;
TInfoAtomo infoAtomo;

int main(void){
    printf("Analisando:\n\n----\n%s\n----\n\n",buffer);

    while(1){
        infoAtomo = obter_atomo();
        if( infoAtomo.atomo == EOS )
            break;

        printf("# %d: ", infoAtomo.linha);

        if( infoAtomo.atomo == IDENTIFICADOR)
            printf("identificador | ");
        else if( infoAtomo.atomo == NUMERO ){
            printf("numero | %.4f\n", infoAtomo.atributo_numero);
            continue;             
        }
        else if( infoAtomo.atomo == ERRO ){
            printf("erro lexico: %s\n", infoAtomo.erro);
            break;
        }

        printf("%s\n", infoAtomo.atributo);
    }    
        
}