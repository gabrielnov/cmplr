#ifndef ANALISADOR_SINTATICO_H
#define ANALISADOR_SINTATICO_H

#include "gerencia_arquivos.h"
#include "analisador_lexico.h"
#include "tokens.h"

extern const char * const lista_tokens[];

void inicia(char *);

void consome(TAtomo);

void programa();

void declaracoes();
void declaracao();

void lista_variavel();

void bloco_comandos();
void comandos();
void comando();

void atribuicao();
void comando_if();
void comando_while();
void comando_entrada();
void comando_saida();

void expressao();
void expressao_logica();
void expressao_relacional();
void expressao_adicao();
void expressao_multi();

void op_relacional();
void operando();

#endif