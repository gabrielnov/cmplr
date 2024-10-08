#include "analisador_lexico.h"

int linha = 1;
extern char * buffer; // compartilhamos o buffer entre os analisadores

// exclui caracteres irrelevantes do buffer
void ignora_delimitadores(){
    while(*buffer == ' ' || *buffer == '\n' || *buffer == '\t' || *buffer == '\r'){
        if(*buffer=='\n')
            linha++;
        buffer++;
    }
}

TInfoAtomo obter_atomo(){
    TInfoAtomo info_atomo;
    
    info_atomo.atomo = ERRO; // sobrescrevemos o atomo apenas em caso de sucesso
    strcpy(info_atomo.atributo, "");
    
    ignora_delimitadores(buffer);

    if(*buffer == '_')
        info_atomo = reconhece_id(buffer);
    else if(*buffer == '0')
        info_atomo = reconhece_numero(buffer);        
    else if ((*buffer >= 'a' && *buffer <= 'z') || (*buffer >= 'A' && *buffer <= 'Z'))
        info_atomo = reconhece_palavra_reservada(buffer);
    else if(*buffer == '\0')
        info_atomo.atomo = EOS;
    else if(*buffer == ';'){
        buffer++;
        info_atomo.atomo = PONTO_VIRGULA;
    }
    else if(*buffer == '&'){
        buffer++;
        if (*buffer == '&'){
            info_atomo.atomo = OP_AND;
            buffer++;
        } // caso contrario, ja está settado como ERRO 
    }
    else if(*buffer == '|'){
        buffer++;
        if (*buffer == '|'){
            info_atomo.atomo = OP_OR;
            buffer++;
        } // caso contrario, ja está settado como ERRO 
    }
    else if(*buffer == ','){
        buffer++;
        info_atomo.atomo = VIRGULA;
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
    else if(*buffer == '+'){
        buffer++;
        info_atomo.atomo = OP_SOMA;
    }
    else if(*buffer == '-'){
        buffer++;
        info_atomo.atomo = OP_SUBTR;
    }
    else if(*buffer == '*'){
        buffer++;
        info_atomo.atomo = OP_MULT;
    }
    else if(*buffer == '/'){
        info_atomo.atomo = OP_DIV; 
        buffer++;
        if (*buffer == '/')
            info_atomo = reconhece_comentario();
        else if (*buffer == '*')
            info_atomo = reconhece_comentario_mult();
    }
    else if(*buffer == '='){
        info_atomo.atomo = OP_ATRIBUICAO;
        buffer++;
        if (*buffer == '='){
            buffer++;
            info_atomo.atomo = OP_IGUAL;
        }
    }
    else if(*buffer == '!'){
        buffer++;
        if (*buffer == '='){
            info_atomo.atomo = OP_DIFERENTE;
            buffer++;
        } // caso contrario, ja está settado como ERRO 
    }
   
    // caso nao seja ID ou NUM, copiamos o atomo para facilitar no print nas proximas linhas
    if (strlen(info_atomo.atributo) == 0 ) 
        strcpy(info_atomo.atributo, lista_tokens[info_atomo.atomo]);
    
    info_atomo.linha = linha;

    imprime_atomo(info_atomo);

    return info_atomo;
}

// comentário de apenas uma linha, igual a este que está escrito
TInfoAtomo reconhece_comentario(){
    TInfoAtomo info_atomo;
    buffer++;
    strcpy(info_atomo.atributo, lista_tokens[COMENTARIO]);

    while(*buffer != '\n')
        buffer++;
    
    info_atomo.atomo = COMENTARIO; 
    return info_atomo;
}

/*  comentário de multiplas linhas
    igual a este que está escrito */
TInfoAtomo reconhece_comentario_mult(){
    TInfoAtomo info_atomo;
    buffer++;
    info_atomo.atomo = COMENTARIO;
    strcpy(info_atomo.atributo, lista_tokens[COMENTARIO]);

    while(*buffer != '\0'){
        if (*buffer == '*'){
            buffer++;

            if (*buffer == '/'){
                buffer++;
                return info_atomo;
            } 
        }
        else if (*buffer == '\n')
            linha++;
        
        buffer++;
    }

    info_atomo.atomo = ERRO;
    return info_atomo;
}

TInfoAtomo reconhece_id(){
    TInfoAtomo info_atomo;
    char * lexema;
    lexema = buffer;    
    info_atomo.atomo = ERRO;

    if (*buffer == '_')
        buffer++;
    else
        return info_atomo;

    if((*buffer >= 'a' && *buffer <= 'z') || (*buffer >= 'A' && *buffer <= 'Z'))
        buffer++;
    else
        return info_atomo;
        
q0:
    if(*buffer == ' ' || *buffer == ',' || *buffer == ')' || *buffer == ';' || *buffer == '}'){
        info_atomo.atomo = IDENTIFICADOR;
    }
    else if((*buffer >= 'a' && *buffer <= 'z') || (*buffer >= 'A' && *buffer <= 'Z') || isdigit(*buffer)){
        buffer++;    
        goto q0;
    } 
  
    if(buffer - lexema > 15){ // maximo de quinze characteres por identificador
       info_atomo.atomo = ERRO;
       return info_atomo;
    } 

    strncpy(info_atomo.atributo, lexema, buffer - lexema);
    info_atomo.atributo[ buffer - lexema ] = '\0'; // finaliza string
   
    return info_atomo;
}

TInfoAtomo reconhece_numero(){
    char * lexema;
    lexema = buffer;
    TInfoAtomo info_atomo;
    info_atomo.atomo = NUMERO;

    buffer++;
  
    if(*buffer == 'x')
        buffer++; 
    else
        info_atomo.atomo = ERRO; 
   

q0:
    if(
        (*buffer >= 65 && *buffer <= 70 ) ||
        (*buffer >= 48 && *buffer <= 57 ) 
    ){
        buffer++;
        goto q0;
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
    { 
        info_atomo.atomo = ERRO; 
    }

    // convertendo hex para dec
    info_atomo.atributo_numero = strtol(lexema, (char**)NULL, 16);

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
            return info_atomo;
        
        lexema[i] = *buffer;
        buffer++;
        i++;
    }
    
    if (strcmp(lexema, "bool") == 0) info_atomo.atomo = PR_BOOL;
    else if (strcmp(lexema, "int") == 0) info_atomo.atomo = PR_INT;
    else if (strcmp(lexema, "main") == 0) info_atomo.atomo = PR_MAIN;
    else if (strcmp(lexema, "scanf") == 0) info_atomo.atomo = PR_SCANF;
    else if (strcmp(lexema, "printf") == 0) info_atomo.atomo = PR_PRINTF;
    else if (strcmp(lexema, "if") == 0) info_atomo.atomo = PR_IF;
    else if (strcmp(lexema, "else") == 0) info_atomo.atomo = PR_ELSE;
    else if (strcmp(lexema, "while") == 0) info_atomo.atomo = PR_WHILE;
    else if (strcmp(lexema, "void") == 0) info_atomo.atomo = PR_VOID;
    else if (strcmp(lexema, "true") == 0) info_atomo.atomo = PR_TRUE;
    else if (strcmp(lexema, "false") == 0) info_atomo.atomo = PR_FALSE;

    strcpy(info_atomo.atributo, lista_tokens[info_atomo.atomo]);

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
        printf("erro lexico\n");
        return;
    }
   printf("%s\n", info_atomo.atributo);    
}