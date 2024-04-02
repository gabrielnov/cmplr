#include "gerencia_arquivos.h"

char * abrir_arquivo(char const* caminho_arquivo){
    FILE* arquivo;
    long num_bytes;
    
    arquivo = fopen(caminho_arquivo, "r"); 

    if(arquivo == NULL) {
        printf( "erro ao tentar abrir %s: arquivo nao encontrado", caminho_arquivo);
        exit(1);
    }

    fseek(arquivo, 0L, SEEK_END);
    num_bytes = ftell(arquivo);

    if(num_bytes == 0) {
        printf( "erro ao tentar abrir %s: arquivo vazio", caminho_arquivo);
        exit(1);
    }
     if(num_bytes >= 1000) {
        printf( "erro ao tentar abrir %s: tamanho de arquivo nao permitido", caminho_arquivo);
        exit(1);
    }

    fseek(arquivo, 0L, SEEK_SET);	

    char *buffer = malloc (sizeof (char) * 1000);
    fread(buffer, sizeof(char), num_bytes, arquivo);

    fclose(arquivo);
    
    return buffer;
}