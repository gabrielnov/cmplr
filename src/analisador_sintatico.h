#ifndef _ANALISADOR_SINTATICO_H_
#define _ANALISADOR_SINTATICO_H_

#include "analisador_lexico.h"

void inicia();

void consome( TAtomo atomo);

void programa();

void declaracoes();
void declaracao();

void tipo();

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

void op_racional();
void operando();

#endif