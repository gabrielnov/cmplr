#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> 

#include "tokens.h"

extern const char * const lista_tokens[];

void ignora_delimitadores(char *);
TInfoAtomo obter_atomo(char *);
TInfoAtomo reconhece_id(char *);
TInfoAtomo reconhece_palavra_reservada(char *);
TInfoAtomo reconhece_numero(char *);
void imprime_atomo(TInfoAtomo info_atomo);

#endif