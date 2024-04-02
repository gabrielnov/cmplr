#ifndef GERENCIA_ARQUIVOS_H
#define GERENCIA_ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

extern char *buffer; // TODO nao usar variavel global
void abrir_arquivo(char const*);

#endif