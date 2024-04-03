#include "analisador_sintatico.h"

int main(int argc, char *argv[]){
    if( argc != 2 ) {
      printf("uso: %s <arquivo_fonte>\n", argv[0]);
      exit(0);
   }

    inicia(argv[1]);
}