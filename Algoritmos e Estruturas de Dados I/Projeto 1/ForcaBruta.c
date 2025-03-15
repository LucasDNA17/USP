
/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: setembro/outubro de 2024
Objetivo: Este programa busca resolver o problema
do Carteiro Viajante de acordo com o paradigma da
Força Bruta. Ele recebe como entrada (inseridas no
teclado) a quantidade de cidades, a cidade de origem,
a quantidade de estradas e as distâncias entre as
cidades. Ele imprime a cidade de origem, a distância
mínima a ser percorrida e o caminho ótimo.
*/    


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lista_sequencial.h"
#include "lista_encadeada.h"
#include "grafo.h"


/*Protótipos das funções*/
void leitura_dados_iniciais(int *quantidade_cidades, int *cidade_inicial, int *quantidade_arestas);
void leitura_dados_grafo(GRAFO *grafo, int quantidade_arestas);
void completa_lista(LISTA_SEQUENCIAL *lista, int cidade_ini, int quantidade_cidades);
int calcula_distancia_total(LISTA_SEQUENCIAL *lista, int quantidade_cidades, GRAFO *grafo);
void permutacoes(LISTA_SEQUENCIAL *lista, int esq, int *caminho_min, int *dist_min, int quantidade_cidades, GRAFO *grafo);
void printa_resultado(int caminho_min[], int dist_min, int quantidade_cidades, int cidade_inicial);


/*
Função principal: declara as variáveis, o GRAFO e a LISTA_SEQUENCIAL utilizados
e chama as funções para realizar a leitura das entradas, calcular o menor caminho
e imprimir esse resultado.
*/
int main(void) {
    int quantidade_cidades, cidade_inicial, quantidade_arestas, dist_min = INT_MAX;

    leitura_dados_iniciais(&quantidade_cidades, &cidade_inicial, &quantidade_arestas);

    LISTA_SEQUENCIAL *lista = lista_sequencial_criar();
    GRAFO *grafo = grafo_criar(quantidade_cidades);
    int *caminho_min = (int *) malloc(quantidade_cidades*sizeof(int));

    completa_lista(lista, cidade_inicial, quantidade_cidades);
    leitura_dados_grafo(grafo, quantidade_arestas);
    
    permutacoes(lista, 1, caminho_min, &dist_min, quantidade_cidades, grafo);
    printa_resultado(caminho_min, dist_min, quantidade_cidades, cidade_inicial);
  
    grafo_apagar(&grafo);
    lista_sequencial_apagar(&lista);
    free(caminho_min); caminho_min = NULL;
    return 0;
}




/*
A função leitura_dados_iniciais() recebe como parâmetros um ponteiro para a variável inteira
que armazenaa a quantidade_de_cidades; um ponteiro para a variável inteira que armazena a cidade
de origem e, por fim, um ponteiro para a variável inteira que armazena a quantidade de "estradas"
(arestas).
A função realiza a leitura dessas variáveis, cujos valores são introduzidos pelo usuário.
*/
void leitura_dados_iniciais(int *quantidade_cidades, int *cidade_inicial, int *quantidade_arestas) {
    scanf("%d", quantidade_cidades);
    scanf("%d", cidade_inicial);
    scanf("%d", quantidade_arestas);
}



/*
A função leitura_dados_grafo() recebe como parâmetros um ponteiro para a struct "GRAFO", presente
no header "grafo.h" e que representa as cidades e as estradas entre elas, e um inteiro que armazena
a quantidade de "estradas" (arestas).
A função realiza a leitura de dois inteiros, que representam duas cidades, e um terceiro que armazena
a distãncia entre elas. Essa relação de distância é, em seguida, salva no struct GRAFO.
*/ 
void leitura_dados_grafo(GRAFO *grafo, int quantidade_arestas) {
    
    for(int i = 0; i < quantidade_arestas; i++) {
        int r, t, dist;
        scanf("%d", &r); 
        scanf("%d", &t); 
        scanf("%d", &dist); 
        grafo_inserir_aresta(grafo, r, t, dist);  
    }
    

}


/*
A função completa_lista() recebe como parâmetros um ponteiro para a struct "LISTA_SEQUENCIAL",
presente no header "lista_sequencial.h", representando a estrutura de dados lista sequencial e
sendo usada posteriormente para gerar e avaliar os diferentes caminhos possíveis; um inteiro que armazena a
cidade de origem; e um inteiro que armazena a quantidade de cidades.
A função preenche a lista com a ordem numérica das cidades (1-2-3- ...) e, no fim, troca a primeira cidade
com a cidade de origem casos elas sejam diferentes. Essa troca é importante para que a posição da cidade de
origem não seja permutada ao se gerar todos os caminhos possíveis e, além disso, facilita a impressão do
caminho ótimo.
*/
void completa_lista(LISTA_SEQUENCIAL *lista, int cidade_ini, int quantidade_cidades) {
    for(int i = 0; i < quantidade_cidades; i++) {
        ITEM *item = item_criar(i + 1, NULL);
        lista_sequencial_inserir_fim(lista, item);
    }

    if(cidade_ini != 1)
        lista_sequencial_troca(lista, 0, cidade_ini - 1);
}


/*
A função calcula_distancia_total() recebe como parâmetros um ponteiro para a struct "LISTA_SEQUENCIAL",
presente no header "lista_sequencial.h" e representando um possível caminho a ser avaliado; um inteiro
que armazena a quantidade de cidades; e um ponteiro para a struct "GRAFO", presente no header "grafo.h" 
e que representa a configuração das cidades e as estradas entre elas. 
A função percorre todos os elementos da lista (menos o último) e, a cada elemento, consulta o valor da 
distância entre a cidade representada por ele e a cidade representada pelo elemento em seguida, armazenado
no TAD GRAFO. No fim, é consultada a distância entre a última cidade e a cidade de origem. A soma de todas 
essas distãncias parciais é armazenada na variável "distancia". Caso alguma distãncia parcial seja igual a -1, 
isso significa que não há estrada que conecta as duas cidades em questão (como especificado no header "grafo.h")
e, portanto, o caminho é desconsiderado (retornando -1).
Caso o caminho seja válido, a função retorna a distãncia percorrida total do caminho avaliado. 
*/
int calcula_distancia_total(LISTA_SEQUENCIAL *lista, int quantidade_cidades, GRAFO *grafo) {
    int distancia = 0;
    int distancia_parcial;
    for(int i = 0; i < quantidade_cidades - 1; i++) {
        int chave1 = item_get_chave(lista_sequencial_get_item(lista, i));
        int chave2 = item_get_chave(lista_sequencial_get_item(lista, i + 1));

        distancia_parcial = grafo_get_aresta(grafo, chave1, chave2);
        if(distancia_parcial == -1) //caminho invalido: não há conexão
            return(-1);



        distancia += distancia_parcial;
    }

    int chave1 = item_get_chave(lista_sequencial_get_item(lista, quantidade_cidades - 1));
    int chave2 = item_get_chave(lista_sequencial_get_item(lista, 0));
    distancia_parcial = grafo_get_aresta(grafo, chave1, chave2);
    if(distancia_parcial == -1)
        return(-1);

    distancia += distancia_parcial;
    return(distancia);
}



/*
A função permutacoes() recebe como parâmetros um ponteiro para uma struct "LISTA_SEQUENCIAL", presente no header 
"lista_sequencial.h" e sendo usada para criar os possíveis caminhos; um inteiro que "esq" que representa a 
posição à esquerda da lista a partir da qual os elementos são permutados; um vetor de inteiros que armazena
o melhor caminho encontrado até o momento; um ponteiro para a variável que armazena a distância mínima até
o momento (é preciso o uso de um ponteiro para a variável, pois deve-se alterar o valor da varíavel a cada 
chamada); um inteiro que armazena a quantidade de cidades; e um ponteiro para uma struct "GRAFO" que representa 
as cidades e as estradas entre elas.
No início, a função permutacoes() calcula a distãncia total da permutação atual e, caso ela seja válida e
represente o menor caminho até agora, ela atualiza o caminho e a distância mínima. Em seguida, ele percorre 
todos os elementos entre a posição "esq" e a última posição da lista, trocando o primeiro com o último elemento 
desse intervalo, chamando recursivamente a si mesma para avaliar as permutações fruto dessa nova configuração e,
no fim, desfazendo a troca feita. 
*/
void permutacoes(LISTA_SEQUENCIAL *lista, int esq, int *caminho_min, int *dist_min, int quantidade_cidades, GRAFO *grafo) {
    if(esq == quantidade_cidades - 1) {
        int dist_atual = calcula_distancia_total(lista, quantidade_cidades, grafo);
        if(dist_atual != -1 && dist_atual < *dist_min) {
            *dist_min = dist_atual;
            for(int i = 0; i < quantidade_cidades; i++)
                caminho_min[i] = item_get_chave(lista_sequencial_get_item(lista, i));
        }
    }

        else {

            for(int i = esq; i < quantidade_cidades; i++) {
                lista_sequencial_troca(lista, esq, i);
                permutacoes(lista, esq + 1, caminho_min, dist_min, quantidade_cidades, grafo);
                lista_sequencial_troca(lista, esq, i);
            }
        }
    

}


/*
A função printa_resultado() recebe como parâmetros um vetor de inteiros que representa o caminho
ótimo; um inteiro que representa a distãncia mínima a ser percorrida; um inteiro que representa
a quantidade de cidades; e um inteiro que armazena a cidade de origem.
A função imprime a cidade de origem, a distância mínima e o caminho ótimo, esse último na forma-
tação x - y - z ... - x, em que x é a cidade de origem (e destino) e as outras letras representam
as outras cidades.
*/
void printa_resultado(int caminho_min[], int dist_min, int quantidade_cidades, int cidade_inicial) {
    printf("Cidade de origem: %d\n", cidade_inicial);
    printf("Distância mínima: %d\n", dist_min);
    printf("Caminho mínimo: \n");
    for(int i = 0; i < quantidade_cidades; i++)
        printf("%d - ", caminho_min[i]);

    
    printf("%d\n", caminho_min[0]);
}
