#include "hash_index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// debug
#define DEBUG 1

int main() {

    // Abrir o arquivo de entrada
    FILE *infile = fopen("data/in.txt", "r");
    if (infile == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return EXIT_FAILURE;
    }

    // Abrir o arquivo de saída
    FILE *outfile = fopen("data/out.txt", "w");
    if (outfile == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(infile); 
        return EXIT_FAILURE;
    }

    // Ler a profundidade global inicial do diretório de hash
    int initial_depth = 0;
    fscanf(infile, "PG/%d\n", &initial_depth);
    if(initial_depth == 0) {
        fprintf(stderr, "Erro: Profundidade global inválida\n");
        fclose(infile);
        fclose(outfile);
        return EXIT_FAILURE;
    }

    if(DEBUG) printf("\n> main: Profundidade global inicial: %d\n", initial_depth);

    
    // Criar o diretório hash com a profundidade inicial
    HashDirectory *dir = create_hash_directory(initial_depth);
    
    //exit(0);

    // Carregar dados iniciais do arquivo CSV
    load_data_from_csv("data/compras.csv", dir);

    // Processar as operações no arquivo de entrada
    char operation[10], data[20];
    int key;

    //fflush(stdout);

    if(DEBUG) printf("\n\033[0;36m> main: Processando operações...\033[0m\n");


    //WHILE MEXIDO PELO ESTAGIARIO
    /*
    while (fscanf(infile, "\n%[^:]:%d,%*s", operation, &key) == 2){

        if (operation[0] == '\n') { continue; } // skip empty lines
        if (operation[0] == '#') { continue; }  // pula os comentários
        if(DEBUG) printf(">>\tmain: op:[%s], key:[%d], data[%s]\n", operation, key, data);
        
        //SE A OPERAÇÃO FOR UMA INCLUSAO
        if (strcmp(operation, "INC") == 0) {
            fscanf(infile, "%*[^:]:%*d,%s", data);
            insert_entry(dir, key, data); // Suponha que a entrada de dados seja uma string genérica
            fprintf(outfile, "INC:%d/Operação concluída\n", key);
        } 
        //SE A OPERAÇÃO FOR UMA BUSCA
        else if (strcmp(operation, "BUS") == 0){
            search_entry(dir, key);
            //insert_entry(dir, key, data); // Suponha que a entrada de dados seja uma string genérica
            fprintf(outfile, "BUS:%d/Operação concluída\n", key);
        } 
    }
    */




















    //WHILE ORIGINAL COM A LEITURA DO DATA PADRÃO ---------------------------------------------------------------

    while (fscanf(infile, "\n%[^:]:%d,%s", operation, &key, data) == 3) {
        //operation[strcspn(operation,"\n")] = '\0';

        // TODO: verificar o porque o fscanf não está lendo corretamente a string de operação
        
        if (operation[0] == '\n') { continue; } // skip empty lines
        if (operation[0] == '#') { continue; }  // pula os comentários
        if(DEBUG) printf(">>\tmain: op:[%s], key:[%d], data[%s]\n", operation, key, data);
        
        //SE A OPERAÇÃO FOR UMA INCLUSAO
        if (strcmp(operation, "INC") == 0) {
            insert_entry(dir, key, data); // Suponha que a entrada de dados seja uma string genérica
            fprintf(outfile, "INC:%d/Operação concluída\n", key);
        } 
        //SE A OPERAÇÃO FOR UMA BUSCA
        else if (strcmp(operation, "S RC") == 0){
            search_entry(dir, key);
            //insert_entry(dir, key, data); // Suponha que a entrada de dados seja uma string genérica
            fprintf(outfile, "SRC:%d/Operação concluída\n", key);
        } 
        /*
        else if (strcmp(operation, "REM") == 0) {
            delete_entry(dir, key);
            fprintf(outfile, "REM:%d/Operação concluída\n", key);
        } else if (strcmp(operation, "BUS") == 0) {
            char *result = search_entry(dir, key);
            if (result != NULL) {
                fprintf(outfile, "BUS:%d/Encontrado\n", key);
            } else {
                fprintf(outfile, "BUS:%d/Não encontrado\n", key);
            }
        }
        */
    }

    // Liberar recursos e fechar arquivos
    free_hash_directory(dir);
    fclose(infile);
    fclose(outfile);

    return EXIT_SUCCESS;
}

