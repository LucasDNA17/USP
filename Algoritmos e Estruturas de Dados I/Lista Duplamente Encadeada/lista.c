#include "lista.h"

typedef struct no_ NO;

struct no_ {
	ITEM *item;
	NO* anterior;
	NO* proximo;
};


struct lista_ {
	NO *inicio;
	NO *fim;
	int tamanho;
	bool ordenada;
};


LISTA *lista_criar(bool ordenada){
	LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
	if(lista != NULL) {
		lista->inicio = NULL;
		lista->fim = NULL;
		lista->tamanho = 0;
		lista->ordenada = ordenada;
	}
	return(lista);
}



void lista_esvazia (NO *ptr){
	if (ptr != NULL){
		if(ptr->proximo != NULL)
			lista_esvazia(ptr->proximo);

		item_apagar(&ptr->item);
		ptr->anterior = NULL;
		free(ptr); /* apaga o nó*/
		ptr = NULL;
	}
}

void lista_apagar(LISTA **ptr){
	if (*ptr == NULL)
		return;
	lista_esvazia((*ptr)->inicio);
	free(*ptr);
	*ptr = NULL;
}


bool lista_inserir_inicio(LISTA *lista, ITEM *i){
	if ((lista != NULL) && (!lista_cheia(lista)) ) {
		NO *pnovo = (NO *) malloc(sizeof (NO));
		pnovo->item = i;
		if (lista->inicio == NULL){
			//lista->inicio = pnovo;
			lista->fim = pnovo;
			pnovo->proximo = NULL;
		}
		else {
			lista->inicio->anterior = pnovo;
			pnovo->proximo = lista->inicio;
		}
		pnovo->anterior = NULL;
		lista->inicio = pnovo;
		lista->tamanho++;
		return (true);
	} 
	else
		return (false);
}


int lista_busca_ordenada(LISTA *l, int x) {
	if(inicio == fim)
		return(inicio);







	}













bool lista_inserir(LISTA *l, ITEM *it) {
	if(!l->ordenada)
		lista_inserir_fim(l, it);
	else {
		int pos = lista_busca_ordenada()

	}



}