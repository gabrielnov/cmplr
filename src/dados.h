
char *str_atomo[]={    
    "Fim de buffer(EOS)",
    "Erro Lexico",
    "identificador",
    "numero",
    "palavra_reservada",
    "menor",
    "menor_igual",
    "maior",
    "maior_igual",
    "+",
    "*",
    "abre_par",
    "fecha_par",
    "abre_chaves",
    "fecha_chaves",
    "ponto_virgula"
};

typedef enum{
    EOS, // end of string    
    ERRO,
    IDENTIFICADOR,
    NUMERO,
    PALAVRA_RESERVADA,
    // operadores
    MENOR,
    MENOR_IGUAL,
    MAIOR,
    MAIOR_IGUAL,
    OP_SOMA, 
    OP_MULT,
    ABRE_PAR,
    FECHA_PAR,
    ABRE_CHAVES,
    FECHA_CHAVES,
    PONTO_VIRGULA
}TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
    float atributo_numero;
    char atributo[15];
    char erro[100];
}TInfoAtomo;
