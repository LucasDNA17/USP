/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: setembro/outubro de 2024
Descrição: Isto é a implementação do TAD GRAFO. Encontram-se aqui
comentários pontuais a respeito do TAD. Os principais aspectos do
TAD são descritos no header "grafo.h".
*/  


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista_encadeada.h"
#include "item.h"
#include "grafo.h"


struct no {
	int vertice;
	int peso;
	struct no *proximo;
};

GRAFO *grafo_criar(int quantidade_nos) {
	GRAFO *grafo = (GRAFO *) malloc(sizeof(GRAFO));
	if(grafo != NULL) {
		grafo->quantidade_nos = quantidade_nos;
		grafo->arestas = (LISTA_ENCADEADA **) malloc(quantidade_nos*sizeof(LISTA_ENCADEADA *));
		if(grafo->arestas == NULL)
			return(NULL);

		for(int i = 0; i < quantidade_nos; i++)
			grafo->arestas[i] = lista_encadeada_criar();
	}

	return(grafo);
}


void grafo_inserir_aresta(GRAFO *grafo, int no1, int no2, int valor) {
	if(grafo != NULL) {
		int *val1 = (int *) malloc(sizeof(int));
		int *val2 = (int *) malloc(sizeof(int));
		*val1 = valor; *val2 = valor;
 		ITEM *item1 = (ITEM *) item_criar(no2, val1);
		ITEM *item2 = (ITEM *) item_criar(no1, val2);

		lista_encadeada_inserir_fim(grafo->arestas[no1 - 1], item1);
		lista_encadeada_inserir_fim(grafo->arestas[no2 - 1], item2);
	}

}


int grafo_get_aresta(GRAFO *grafo, int no1, int no2) {
	if(grafo != NULL) {
		ITEM *item = lista_encadeada_busca(grafo->arestas[no1 - 1], no2);
		if(item == NULL)
			return(-1);
		else
			return(*((int *)item_get_dados(item)));
	}
	return(-1);
}


bool grafo_apagar(GRAFO **grafo) {
	if(*grafo != NULL) {
		if((*grafo)->arestas != NULL) {
			for(int i = 0; i < (*grafo)->quantidade_nos; i++)
				lista_encadeada_apagar(&((*grafo)->arestas[i]));
				
				free((*grafo)->arestas);
				(*grafo)->arestas = NULL;
		}

		free(*grafo);
		*grafo = NULL;
		return(true);
	}

	return(false);
}

LISTA_ENCADEADA *grafo_get_adjacentes(GRAFO *grafo, int no) {
	if(grafo != NULL && no > 0 && no <= grafo->quantidade_nos) {
		return grafo->arestas[no - 1];  // Retorna a lista de adjacência
	}
	return NULL;  // Retorna NULL se o nó for inválido
}
