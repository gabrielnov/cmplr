#ifndef _ANALISADOR_H_
#define _ANALISADOR_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> 

#include "tokens.h"

void ignora_delimitadores();
TInfoAtomo obter_atomo();
TInfoAtomo reconhece_id();
TInfoAtomo reconhece_palavra_reservada();
TInfoAtomo reconhece_numero();

#endif