#include "analisador_lexico.h"
#include "tokens.h"

int linha = 1;
char *buffer = "int main(void) \n "
                "{ int _aaa2a; \n "
                " }";

char * lista_tokens[]={    
        "Fim de buffer(EOS)",
        "Erro Lexico",
        "identificador",
        "numero",
        "igual",
        "diferente",
        "menor",
        "menor_igual",
        "maior",
        "maior_igual",
        "+",
        "-",
        "*",
        "/"
        "operador_or",
        "operador_and"
        "abre_par",
        "fecha_par",
        "abre_chaves",
        "fecha_chaves",
        "ponto_virgula",
        "pr_tipo", // pr = palavra reservada
        "pr_main",
        "pr_scanf",
        "pr_printf",
        "pr_if",
        "pr_else",
        "pr_while",
        "pr_void",
        "pr_true",
        "pr_false",
        "virgula"
    };

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
    strcpy(info_atomo.atributo, "");

    ignora_delimitadores();
    
    if(*buffer == '_')
        info_atomo = reconhece_id();
    else if(*buffer == '0')
        info_atomo = reconhece_numero();        
    else if ((*buffer >= 'a' && *buffer <= 'z') || (*buffer >= 'A' && *buffer <= 'Z'))
        info_atomo = reconhece_palavra_reservada();
    else if(*buffer == '\0')
        info_atomo.atomo = EOS;
    else if(*buffer == ';'){
        buffer++;
        info_atomo.atomo = PONTO_VIRGULA;
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
        info_atomo.atomo = OP_MENOR;
        if (*buffer == '='){
            buffer++;
            info_atomo.atomo = OP_MENOR_IGUAL;
        }
    }
    else if(*buffer == '>'){
        buffer++;
        info_atomo.atomo = OP_MAIOR;
        if (*buffer == '='){
            buffer++;
            info_atomo.atomo = OP_MAIOR_IGUAL;
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
   
    if (strlen(info_atomo.atributo) == 0 )
        strcpy(info_atomo.atributo, lista_tokens[info_atomo.atomo]);
    
    info_atomo.linha = linha;

    imprime_atomo(info_atomo);

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
    if(*buffer == ')' || *buffer == ';' || *buffer == '}')
        goto q3;
    if(isalpha(*buffer) || isdigit(*buffer)){
        buffer++;    
        goto q2;
    } else info_atomo.atomo = ERRO;
q3:    
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
        *buffer != '('  &&
        *buffer != ')'  && 
        *buffer != '{'  &&
        *buffer != '}'  &&
        *buffer != ';'  &&
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
        *buffer != ')'  && 
        *buffer != '{'  &&
        *buffer != '}'  &&
        *buffer != ';'  &&
        *buffer != '\0'
        )
    {
        if (i > MAX_LENGTH)
            return info_atomo; // TODO copiar lexema para mensagem de erro
        
        lexema[i] = *buffer;
        buffer++;
        i++;
    }
    
    if (strcmp(lexema, "while") == 0) info_atomo.atomo = PR_WHILE;
    else if (strcmp(lexema, "if") == 0) info_atomo.atomo = PR_IF;
    else if (strcmp(lexema, "else") == 0) info_atomo.atomo = PR_ELSE;
    else if (strcmp(lexema, "void") == 0) info_atomo.atomo = PR_VOID;
    else if (strcmp(lexema, "int") == 0) info_atomo.atomo = PR_TIPO;
    else if (strcmp(lexema, "bool") == 0) info_atomo.atomo = PR_TIPO;
    else if (strcmp(lexema, "true") == 0) info_atomo.atomo = PR_TRUE;
    else if (strcmp(lexema, "false") == 0) info_atomo.atomo = PR_FALSE;
    else if (strcmp(lexema, "main") == 0) info_atomo.atomo = PR_MAIN;
    else if (strcmp(lexema, "printf") == 0) info_atomo.atomo = PR_PRINTF;
    else if (strcmp(lexema, "scanf") == 0) info_atomo.atomo = PR_SCANF;

    strcpy(info_atomo.atributo, lista_tokens[info_atomo.atomo]);
    
    if (info_atomo.atomo == ERRO)
        strcpy(info_atomo.erro, lexema);

    return info_atomo;
}

void imprime_atomo(TInfoAtomo info_atomo){
    printf("# %d: ", info_atomo.linha);

    if( info_atomo.atomo == IDENTIFICADOR)
        printf("identificador | ");
    else if( info_atomo.atomo == NUMERO ){
        printf("numero | %.4f\n", info_atomo.atributo_numero);      
        return;
    }
    else if( info_atomo.atomo == ERRO ){
        printf("erro lexico: %s\n", info_atomo.erro);
        return;
    }

   printf("%s\n", info_atomo.atributo);    
}