#include "item.h"
#include "Deque.h"
#include <stdlib.h>

struct deque_ {
	int inicio;
	int fim;
	int tamanho;
	ITEM* itens[MAX_TAMANHO];
};


DEQUE* deque_criar() {
	DEQUE* d = (DEQUE *) malloc(sizeof(DEQUE));
	if(d != NULL) {
		d->inicio = 0;
		d->fim = 0;
		d->tamanho = 0;
	}
	return(d);
}

void deque_apagar(DEQUE** deque) {
	while(!deque_vazia(*deque)) {
		ITEM* item = deque_remover_inicio(*deque);
		item_apagar(&item);
	}
	free(*deque);
	*deque = NULL;
}

bool deque_inserir_inicio(DEQUE* deque, ITEM* item) {
	if(!deque_cheia(deque)) {
		deque->inicio = (deque->inicio - 1 + MAX_TAMANHO) % MAX_TAMANHO;
		deque->itens[deque->inicio] = item;
		deque->tamanho++;
		return(true);
	}
	return(false);
}


bool deque_inserir_fim(DEQUE* deque, ITEM* item) {
	if(!deque_cheia(deque)) {
		deque->itens[deque->fim] = item;
		deque->fim = (deque->fim + 1) % MAX_TAMANHO;
		deque->tamanho++;
		return(true); 
	}
	return(false);
}


ITEM* deque_remover_inicio(DEQUE* deque) {
	if(!deque_vazia(deque)) {
		ITEM* item = deque->itens[deque->inicio];
		deque->itens[deque->inicio] = NULL;
		deque->inicio = (deque->inicio + 1) % MAX_TAMANHO;
		deque->tamanho--;
		return(item);
	}
	return(NULL);
}

ITEM* deque_remover_fim(DEQUE* deque) {
	if(!deque_vazia(deque)) {
		deque->fim = (deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO;
		ITEM* item = deque->itens[deque->fim];
		deque->itens[deque->fim] = NULL;
		deque->tamanho--;
		return(item);
	}
	return(NULL);
}

ITEM* deque_primeiro(DEQUE* deque) {
	if(!deque_vazia(deque)) 
		return(deque->itens[deque->inicio]);

	return(NULL);
}

ITEM* deque_ultimo(DEQUE* deque) {
	if(!deque_vazia) 
		return(deque->itens[(deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO]);

	return(NULL);
}

int deque_contar(DEQUE* deque) {
	if(deque == NULL)
		return(ERRO);

	return(deque->tamanho);
}

bool deque_vazia(DEQUE* deque) {
	if(deque != NULL)
		return(deque->tamanho == 0);

	return(true);
}

bool deque_cheia(DEQUE* deque) {
	if(deque != NULL)
		return(deque->tamanho == MAX_TAMANHO);

	return(true);
}
