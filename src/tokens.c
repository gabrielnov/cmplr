#include "tokens.h"

const char * const lista_tokens[]={    
        "Fim de buffer(EOS)",
        "Erro Lexico",
        "identificador",
        "numero",
        // operador
        "operador_igual",
        "operador_diferente",
        "operador_menor",
        "operador_menor_igual",
        "operador_maior",
        "operador_maior_igual",
        "operador_soma",
        "operador_subtracao",
        "operador_multiplicacap",
        "operador_divisao",
        "operador_or",
        "operador_and",
        // palavra reservada
        "pr_int",
        "pr_bool", 
        "pr_main",
        "pr_scanf",
        "pr_printf",
        "pr_if",
        "pr_else",
        "pr_while",
        "pr_void",
        "pr_true",
        "pr_false",
        // outros
        "virgula",
        "abre_par",
        "fecha_par",
        "abre_chaves",
        "fecha_chaves",
        "ponto_virgula",
};