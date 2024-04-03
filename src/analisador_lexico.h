#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> 

#include "tokens.h"

extern const char * const lista_tokens[];

void ignora_delimitadores();
TInfoAtomo reconhece_comentario();
TInfoAtomo reconhece_comentario_mult();
TInfoAtomo obter_atomo();
TInfoAtomo reconhece_id();
TInfoAtomo reconhece_palavra_reservada();
TInfoAtomo reconhece_numero();
void imprime_atomo(TInfoAtomo info_atomo);

#endif