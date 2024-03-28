#include "analisador_lexico.h"

int linha = 1;
char *buffer = "0x123 ;\n"
                "int _teste ;\n"
                "printaaaaaaf() ;\n"
                ">  >=\n"
                "< <= >";

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
    TInfoAtomo info_atomo;
    info_atomo.atomo=ERRO;
    
    ignora_delimitadores();

    if(*buffer == '\0')
        info_atomo.atomo = EOS;
    else if(*buffer == ';'){
        buffer++;
        info_atomo.atomo = PONTO_VIRGULA;
    }
    else if(*buffer == ')'){
        buffer++;
        info_atomo.atomo = FECHA_PAR;
    }
    else if(*buffer == '('){
        buffer++;
        info_atomo.atomo = ABRE_PAR;
    }
    else if(*buffer == ')'){
        buffer++;
        info_atomo.atomo = FECHA_PAR;
    }
    else if(*buffer == '{'){
        buffer++;
        info_atomo.atomo = ABRE_CHAVES;
    }
    else if(*buffer == '}'){
        buffer++;
        info_atomo.atomo = FECHA_CHAVES;
    }
    else if(*buffer == '<'){
        buffer++;
        info_atomo.atomo = MENOR;
        if (*buffer == '='){
            buffer++;
            info_atomo.atomo = MENOR_IGUAL;
        }
    }
    else if(*buffer == '>'){
        buffer++;
        info_atomo.atomo = MAIOR;
        if (*buffer == '='){
            buffer++;
            info_atomo.atomo = MAIOR_IGUAL;
        }
    }
    else if(*buffer == '+' || *buffer == '-'){
        buffer++;
        info_atomo.atomo = OP_SOMA;
    }
    else if(*buffer == '*' || *buffer == '/'){
        buffer++;
        info_atomo.atomo = OP_MULT;
    }
   
   strcpy(  info_atomo.atributo, str_atomo[info_atomo.atomo]);
    
    
    if(*buffer == '_')
        info_atomo = reconhece_id();
    else if(*buffer == '0')
        info_atomo = reconhece_numero();        
    else if(isalpha(*buffer))
        info_atomo = reconhece_palavra_reservada();

    info_atomo.linha = linha;
    return info_atomo;
}

TInfoAtomo reconhece_id(){
    TInfoAtomo info_atomo;
    char *iniLexema;
    iniLexema = buffer;

q0:
    if (*buffer == '_'){
        buffer++;
        goto q1;
    } else info_atomo.atomo = ERRO;
q1:
    if(isalpha(*buffer)){
        buffer++;
        goto q2;
    } else info_atomo.atomo = ERRO;
q2:
    if(isalpha(*buffer) || isdigit(*buffer)){
        buffer++;    
        goto q1;
    } else info_atomo.atomo = ERRO;
    
    if( buffer - iniLexema <= 15 ){ // maximo de quinze characteres por identificador
        strncpy(info_atomo.atributo, iniLexema, buffer - iniLexema);
        info_atomo.atributo[buffer-iniLexema] = '\0'; // finaliza string
        info_atomo.atomo = IDENTIFICADOR;
    } else info_atomo.atomo = ERRO;

    if (info_atomo.atomo == ERRO) 
        strcpy(info_atomo.erro, iniLexema);

    return info_atomo;
}

TInfoAtomo reconhece_numero(){
    char *iniLexema;
    iniLexema = buffer;
    TInfoAtomo info_atomo;
    info_atomo.atomo = NUMERO;

q0:
    if(*buffer == '0'){
        buffer++;
        goto q1;
    } else info_atomo.atomo = ERRO; 
q1:
    if(*buffer == 'x'){
        buffer++;
        goto q2;
    } else info_atomo.atomo = ERRO; 
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
    { info_atomo.atomo = ERRO; }

    if (info_atomo.atomo == ERRO) 
        strcpy(info_atomo.erro, iniLexema);

    // convertendo hex para dec
    info_atomo.atributo_numero = strtol(iniLexema, (char**)NULL, 16);

    return info_atomo;
}

TInfoAtomo reconhece_palavra_reservada(){
    const int MAX_LENGTH = 7;
    char lexema[MAX_LENGTH];
    memset(lexema, 0, MAX_LENGTH);

    TInfoAtomo info_atomo;
    info_atomo.atomo = ERRO;

    int i = 0;

    while (
        *buffer != ' '  && 
        *buffer != '\n' && 
        *buffer != '\r' &&  
        *buffer != '\t' &&
        *buffer != '('  && 
        *buffer != '\0'
        )
    {
        if (i > MAX_LENGTH)
            return info_atomo; // TODO copiar lexema para mensagem de erro
        
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
    ) info_atomo.atomo = PALAVRA_RESERVADA; 

    strcpy(info_atomo.atributo, lexema);
    
    if (info_atomo.atomo == ERRO)
        strcpy(info_atomo.erro, lexema);

    return info_atomo;
}

TAtomo lookahead;
TInfoAtomo info_atomo;

int main(void){
    printf("Analisando:\n\n----\n%s\n----\n\n",buffer);

    while(1){
        info_atomo = obter_atomo();
        if( info_atomo.atomo == EOS )
            break;

        printf("# %d: ", info_atomo.linha);

        if( info_atomo.atomo == IDENTIFICADOR)
            printf("identificador | ");
        else if( info_atomo.atomo == NUMERO ){
            printf("numero | %.4f\n", info_atomo.atributo_numero);
            continue;             
        }
        else if( info_atomo.atomo == ERRO ){
            printf("erro lexico: %s\n", info_atomo.erro);
            break;
        }

        printf("%s\n", info_atomo.atributo);
    }    
        
}