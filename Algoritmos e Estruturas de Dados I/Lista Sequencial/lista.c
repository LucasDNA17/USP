#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


struct lista_ {
	ITEM *lista[TAM_MAX];
	int inicio; //inicio da lista
	int fim; //fim da lista -1a posicao livre para insercao
	int tamanho;
	bool ordenada;
};

/*Cria logicamente uma lista, inicialmente vazia*/
LISTA *lista_criar(bool ordenada){
	LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
	if (lista != NULL){
		lista->inicio = 0;
		lista->fim = lista->inicio; /*lista vazia*/
		lista->tamanho = 0;
		lista->ordenada = ordenada;
	}
	return (lista);
}



bool lista_cheia(LISTA *l) {
	if(l == NULL)
		return(true);
	else
		return(l->tamanho == TAM_MAX);
}

bool lista_vazia(LISTA *l) {
	if(l == NULL)
		return(true);
	else
		return(l->tamanho == 0);
}



int lista_tamanho(LISTA *l) {
	if(l == NULL)
		return(-1);
	else
		return(l->tamanho);
} 


bool lista_apagar(LISTA **l) {
	if((*l) != NULL) {
		for(int i = 0; i < (*l)->fim; i++) {
			free((*l)->lista[i]);
			(*l)->lista[i] = NULL;
		}
	
		free(*l);
		*l = NULL;
		return(true);
	}

	return(false);
}


void lista_imprimir(LISTA *l) {
	if(l != NULL) {
		for(int i = 0; i < l->fim; i++) {
			int c = item_get_chave(l->lista[i]);
			printf("%d ", c);
		}
		printf("\n");
	}
}

int lista_busca_normal(LISTA *l, int x) {
	int i;

	for (i = 0; i < l->fim; i++) /*não usar ’i < TAM_MAX’ !!!*/
		if (item_get_chave(l->lista[i]) == x)
		return (i);
	

	return(-1);
}


int lista_busca_ordenada(LISTA *l, int x, int inicio, int fim) {
	if(inicio <= fim) {
		if(inicio == fim)
			return(inicio);

		int meio = inicio + (fim- inicio)/2;

		if(x == item_get_chave(l->lista[meio])) {
			return(meio);
		}

		else if(x > item_get_chave(l->lista[meio]))
			lista_busca_ordenada(l, x, meio + 1, fim);

		else  
			lista_busca_ordenada(l, x, inicio, meio - 1);	

	}
}

bool lista_inserir_fim(LISTA *l, ITEM *item){

	if ((l != NULL) && !lista_cheia(l)){
		(l->lista[l->fim]) = item;
		l->fim++; l->tamanho++;
		return(true);
	}
	return(false);
}

bool lista_inserir_posicao(LISTA *l, int pos, ITEM *item) {
	int i;

	//verifica se existe espaço e se a posição está na lista
	if (!lista_cheia(l) && (pos <= l->fim)) {
		for (i = (l->fim-1); i >= pos; i--) { //move os itens
			l->lista[i + 1] = l->lista[i];
		}

		l->lista[pos] = item; //insere novo item
		l->fim++; //ajusta o fim da fila
		l->tamanho++;
		return (true);
		} 
	else {
		return (false);
	}
}

bool lista_inserir(LISTA *l, ITEM *item) {
	if (!l->ordenada)
		return (lista_inserir_fim(l, item));
	else {
		int x = lista_busca_ordenada(l, item_get_chave(item), l->inicio, l->fim - 1);
		return(lista_inserir_posicao(l, x, item));
	}
}



ITEM *lista_remover_pos(LISTA *l, int pos) {
	if(l != NULL && pos <= l->fim - 1) {
		ITEM *it = l->lista[pos];
		for(int i = pos; i < l->fim - 1; i++)
			l->lista[i] = l->lista[i + 1];


		l->tamanho--;
		l->fim--;
		return(it);
	}

	return(NULL);
}



ITEM *lista_remover(LISTA *l, int chave) {
	int x;
	if (!l->ordenada)
		x = lista_busca_normal(l, chave); 
	else 
		x = lista_busca_ordenada(l, chave, l->inicio, l->fim - 1);

	if(x >= 0) 
		return(lista_remover_pos(l, x));

	else
		return(NULL);
}

