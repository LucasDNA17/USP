/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: setembro/outubro de 2024
Objetivo: Este programa busca resolver o problema
do Carteiro Viajante de uma forma mais eficiente que a Força Bruta.
Ele recebe como entrada (inseridas no teclado) a quantidade de cidades,
a cidade de origem, a quantidade de estradas e as distâncias entre as
cidades. Ele imprime a cidade de origem, a distância
mínima a ser percorrida e o caminho ótimo.
*/    

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include "grafo.h"
#include "item.h"
#include "lista_encadeada.h"


//Função para ler os dados iniciais: quantidade de cidades, cidade inicial e quantidade de arestas.
void leitura_dados_iniciais(int *quantidade_cidades, int *cidade_inicial, int *quantidade_arestas) {
    scanf("%d", quantidade_cidades);
    scanf("%d", cidade_inicial);
    scanf("%d", quantidade_arestas);
}

//Função para ler os dados das arestas do grafo e preencher as listas de adjacência.
void leitura_dados_grafo(GRAFO *grafo, int quantidade_arestas) {
    for (int i = 0; i < quantidade_arestas; i++) {
        int origem, destino, peso;
        scanf("%d %d %d", &origem, &destino, &peso);
        grafo_inserir_aresta(grafo, origem, destino, peso);  // Insere a aresta no grafo.
    }
}

/*
Função que calcula uma estimativa do custo restante para completar o circuito.
Utiliza a soma das menores arestas de saída de cada cidade não visitada.
 */
int estimativa_custo(int *visitados, int quantidade_cidades, int *menor_aresta_saida) {
    int estimativa = 0;
    for (int i = 1; i <= quantidade_cidades; i++) {
        if (!visitados[i - 1]) {
            estimativa += menor_aresta_saida[i];  // Soma a menor aresta de saída das cidades não visitadas.
        }
    }
    return estimativa;
}

// Função recursiva que implementa o algoritmo Branch and Bound para resolver o Problema do Caixeiro Viajante.
void bb_recursivo(GRAFO *grafo, int cidade_atual, int *visitados, int nivel, int custo_atual,
                  int *caminho_atual, int *custo_minimo, int *melhor_caminho,
                  int quantidade_cidades, int *menor_aresta_saida) {
    // Caso base: todas as cidades foram visitadas.
    if (nivel == quantidade_cidades) {
        // Verifica se existe uma aresta de retorno para a cidade inicial.
        int custo_retorno = grafo_get_aresta(grafo, cidade_atual, caminho_atual[0]);
        if (custo_retorno != -1) {
            int custo_total = custo_atual + custo_retorno;
            // Se o custo total for menor que o custo mínimo atual, atualiza o melhor caminho.
            if (custo_total < *custo_minimo) {
                *custo_minimo = custo_total;
                for (int i = 0; i < quantidade_cidades; i++) {
                    melhor_caminho[i] = caminho_atual[i];
                }
                melhor_caminho[quantidade_cidades] = caminho_atual[0];  // Retorna à cidade inicial.
            }
        }
        return;
    }

    // Explora todas as cidades não visitadas.
    for (int proxima_cidade = 1; proxima_cidade <= quantidade_cidades; proxima_cidade++) {
        if (!visitados[proxima_cidade - 1]) {
            // Verifica se existe uma aresta entre a cidade atual e a próxima cidade.
            int peso = grafo_get_aresta(grafo, cidade_atual, proxima_cidade);
            if (peso != -1) {
                // Calcula uma estimativa do custo total.
                int estimativa = custo_atual + peso + estimativa_custo(visitados, quantidade_cidades, menor_aresta_saida);
                // Se a estimativa for menor que o custo mínimo atual, continua a busca.
                if (estimativa < *custo_minimo) {
                    visitados[proxima_cidade - 1] = 1;             // Marca a próxima cidade como visitada.
                    caminho_atual[nivel] = proxima_cidade;         // Adiciona a cidade ao caminho atual.
                    bb_recursivo(grafo, proxima_cidade, visitados, nivel + 1, custo_atual + peso,
                                 caminho_atual, custo_minimo, melhor_caminho, quantidade_cidades, menor_aresta_saida);
                    visitados[proxima_cidade - 1] = 0;             // Desmarca a cidade.
                }
            }
        }
    }
}


// Função para imprimir o resultado final: cidade de origem, distância mínima e caminho mínimo.
void printa_resultado(int melhor_caminho[], int custo_minimo, int quantidade_cidades) {
    printf("Cidade de origem: %d\n", melhor_caminho[0]); 
    printf("Distância mínima: %d\n", custo_minimo);  
    printf("Caminho mínimo:\n");
    for (int i = 0; i <= quantidade_cidades; i++) {
        if (i > 0) printf(" - ");
        printf("%d", melhor_caminho[i]);               
    }
    printf("\n");
}


// Função principal que implementa o algoritmo Branch and Bound para resolver o TSP.
void branch_and_bound(GRAFO *grafo, int quantidade_cidades, int cidade_inicial) {
    // Aloca memória para os vetores de controle e resultados.
    int *visitados = (int *)calloc(quantidade_cidades, sizeof(int));                 // Vetor para marcar as cidades visitadas.
    int *caminho_atual = (int *)malloc((quantidade_cidades + 1) * sizeof(int));      // Vetor para armazenar o caminho atual.
    int *melhor_caminho = (int *)malloc((quantidade_cidades + 1) * sizeof(int));     // Vetor para armazenar o melhor caminho encontrado.
    int custo_minimo = INT_MAX;                                                      // Inicializa o custo mínimo com o valor máximo.

    // Calcula a menor aresta de saída para cada cidade.
    int *menor_aresta_saida = (int *)malloc((quantidade_cidades + 1) * sizeof(int));
    for (int cidade = 1; cidade <= quantidade_cidades; cidade++) {
        menor_aresta_saida[cidade] = INT_MAX;
        LISTA_ENCADEADA *adjacentes = grafo_get_adjacentes(grafo, cidade);  // Obtém as cidades adjacentes.
        ITEM *item = lista_encadeada_primeiro(adjacentes);
        while (item != NULL) {
            int peso = *((int *)item_get_dados(item));  // Obtém o peso da aresta.
            if (peso < menor_aresta_saida[cidade]) {
                menor_aresta_saida[cidade] = peso;      // Atualiza com o menor peso encontrado.
            }
            item = lista_encadeada_proximo(adjacentes, item);
        }
        if (menor_aresta_saida[cidade] == INT_MAX) {
            menor_aresta_saida[cidade] = 0;  // Se não houver aresta de saída, define como 0.
        }
    }

    visitados[cidade_inicial - 1] = 1;        // Marca a cidade inicial como visitada.
    caminho_atual[0] = cidade_inicial;        // Inicia o caminho atual com a cidade inicial.

    // Inicia a chamada recursiva do algoritmo Branch and Bound.
    bb_recursivo(grafo, cidade_inicial, visitados, 1, 0, caminho_atual, &custo_minimo,
                 melhor_caminho, quantidade_cidades, menor_aresta_saida);

    // Verifica se foi encontrado um circuito que visita todas as cidades.
    if (custo_minimo == INT_MAX) {
        printf("Não é possível encontrar um circuito que visita todas as cidades.\n");
    } else {
        printa_resultado(melhor_caminho, custo_minimo, quantidade_cidades);  // Imprime o resultado final.
    }

    // Libera a memória alocada.
    free(visitados);
    free(caminho_atual);
    free(melhor_caminho);
    free(menor_aresta_saida);
}

int main(void)
{
    int quantidade_cidades, cidade_inicial, quantidade_arestas;

    // Lê os dados iniciais do problema.
    leitura_dados_iniciais(&quantidade_cidades, &cidade_inicial, &quantidade_arestas);

    // Cria o grafo com a quantidade de cidades especificada.
    GRAFO *grafo = grafo_criar(quantidade_cidades);

    // Lê os dados das arestas e constrói o grafo.
    leitura_dados_grafo(grafo, quantidade_arestas);

    // Chama a função que implementa o algoritmo Branch and Bound.
    branch_and_bound(grafo, quantidade_cidades, cidade_inicial);
    
    // Libera a memória alocada para o grafo.
    grafo_apagar(&grafo);

    return 0;
}
