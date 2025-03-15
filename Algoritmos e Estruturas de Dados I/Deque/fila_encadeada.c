#include <stdio.h>
#include <stdlib.h>
#include "fila.h"




#ifndef _STRUCTS_
#define _STRUCTS_

typedef struct no_ {
	ITEM* item;
	struct no_* proximo;
}noObj;

typedef noObj NO;

typedef struct fila_ {
	NO* inicio;
	NO* fim;
	int tamanho;
}filaObj;

typedef filaObj FILA;

#endif


FILA *fila_criar(void) {
	FILA *fila = (FILA *) malloc(sizeof(FILA));
	if(fila != NULL) {
		fila->inicio = NULL;
		fila->fim = NULL;
		fila->tamanho = 0;
	}
	return(fila);
} 

bool fila_inserir(FILA *fila, ITEM *item) {
	if(!fila_cheia(fila)) {
		NO *no = (NO *) malloc(sizeof(NO));
		if(fila->inicio == NULL)
			fila->inicio = no;
		else
			fila->fim->proximo = no;

		no->item = item;
		no->proximo = NULL;
		fila->fim = no;
		fila->tamanho++;
		return(true);
	}
	return(false);
}


bool fila_cheia(FILA *fila) {
	if(fila == NULL)
		return(true);
	else
		return(!(fila->tamanho - TAM_MAX));
}

bool fila_vazia(FILA *fila) {
	if(fila == NULL)
		return(true);

	else
		return(!(fila->tamanho));
}



int fila_tamanho(FILA *fila) {
	if(fila_vazia(fila))
		return(0);
	else
		return(fila->tamanho);
}



void fila_apagar_topo(FILA *fila) {
	item_apagar(&((fila)->inicio->item)); (fila)->inicio->item = NULL;
	NO *inicio_ = (fila)->inicio;
	(fila)->inicio = ((fila)->inicio->proximo);
	free(inicio_); inicio_ = NULL;

}




void fila_apagar(FILA **fila) {
	if((*fila) == NULL)
		return;

	if((*fila)->inicio == NULL) {
		free(*fila); *fila = NULL;
		return;
	}

	fila_apagar_topo(*fila);
	fila_apagar(fila);
	
}


void fila_inverter_recursiva(FILA *fila) {
	if(fila_vazia(fila))
		return;

	else {
		ITEM *it = fila_remover(fila);
		fila_inverter_recursiva(fila);
		fila_inserir(fila, it);
	}
		
}


void fila_inverter_iterativa(FILA *fila) {
	for(int i = 0; i < fila->tamanho - 1; i++) {
		ITEM *it = fila_remover(fila);
		fila_inserir(fila, it);
	}

}





ITEM *fila_remover(FILA *fila) {
	if(!fila_vazia(fila)) {
		ITEM *it = fila->inicio->item;

		if(fila->tamanho == 1)
			fila->fim = NULL;

		NO *aux = fila->inicio;
		fila->inicio = fila->inicio->proximo;
		aux->proximo = NULL;
		free(aux); aux = NULL;

		fila->tamanho--;


		return(it);
	} 

	return(NULL);
}