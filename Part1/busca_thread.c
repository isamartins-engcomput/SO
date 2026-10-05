// Parte 1: Exercício prático - Busca em vetor usando Thread

/* Considere um vetor global de 1000 posições preenchido com números aleatórios (preencham com rand()). O objetivo é encontrar o MAIOR valor dentro desse vetor
utilizando 4 threads. Cada thread deve percorrer 1/4 do vetor. Cada thread fica responsável por sua respectiva parte no vetor. Crie um vetor global secundário
chamado maiores_parciais[4]. Cada thread deve vasculhar apenas a sua fatia do vetor principal, encontrar o maior número da sua fatia, e salvar exclusivamente
na sua posição correspondente do vetor maiores_parciais (ex: a thread 2 salva em maiores_parciais[2]).
Ao final, após os pthread_join, a própria função main varre esse pequeno vetor de 4 posições e imprime o maior número de todo o vetor. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAM_VETOR 1000
#define NUM_THREADS 4

// Vetores Globais
int vetor[TAM_VETOR];
int maiores_parciais[NUM_THREADS];

// Função que cada thread vai executar individualmente
void* buscar_maior(void* arg)
{
    // 1. Quem é a thread atual? (0, 1, 2 ou 3)
    int meu_id = *(int*)arg;
    
    // 2. Qual pedaço do vetor essa thread vai ler?
    int tamanho_fatia = TAM_VETOR / NUM_THREADS; // 1000 / 4 = 250
    int inicio = meu_id * tamanho_fatia;
    int fim = inicio + tamanho_fatia;
    
    // 3. Procura-se o maior número somente nessa fatia
    int maior_da_minha_fatia = vetor[inicio];
    
    for (int i = inicio + 1; i < fim; i++) {
        if (vetor[i] > maior_da_minha_fatia) {
            maior_da_minha_fatia = vetor[i];
        }
    }
    
    // 4. Anota o resultado num vetor secundário
    maiores_parciais[meu_id] = maior_da_minha_fatia;
    
    pthread_exit(NULL);
}

int main()
{
    // Geração de números aleatórios diferentes a cada execução
    srand(time(NULL));
    
    // Preenchendo o vetor principal com 1000 números aleatórios
    for(int i = 0; i < TAM_VETOR; i++) {
        vetor[i] = rand() % 10000;
    }

    // Criando as 4 threads e suas identidades
    pthread_t threads[NUM_THREADS];
    int ids_das_threads[NUM_THREADS];

    // Iniciando as threads
    for(int i = 0; i < NUM_THREADS; i++) {
        ids_das_threads[i] = i;
        // Executa buscar_maior levando o ID
        pthread_create(&threads[i], NULL, buscar_maior, (void*)&ids_das_threads[i]);
    }

    // Main aguardando todo mundo terminar (JOIN)
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Após todas terminaram, a main olha o vetor de resultados parciais
    int maior_absoluto = maiores_parciais[0];
    
    for(int i = 1; i < NUM_THREADS; i++) {
        if(maiores_parciais[i] > maior_absoluto) {
            maior_absoluto = maiores_parciais[i];
        }
    }

    // Resultado final!
    printf("O maior valor encontrado no vetor inteiro foi: %d\n", maior_absoluto);

    return 0;
}