#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> 
#include "dados.h"

void ignora_delimitadores();
TInfoAtomo obter_atomo();
TInfoAtomo reconhece_id();
TInfoAtomo reconhece_palavra_reservada();
TInfoAtomo reconhece_numero();