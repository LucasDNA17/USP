#include <stdio.h>
#include <stdlib.h>
#include "pilha_dupla.h"


struct pilha_dupla_ {
	ITEM *vet[TAM_MAX];
	int tamanho_pilha1;
	int tamanho_pilha2;
};



PILHA_DUPLA* pilha_criar(void) {
	PILHA_DUPLA *pilha = (PILHA_DUPLA *) malloc(sizeof(PILHA_DUPLA));
	if(pilha != NULL) {
		pilha->tamanho_pilha1 = 0;
		pilha->tamanho_pilha2 = 0;
	}

	return(pilha);
}


void pilha_apagar(PILHA_DUPLA** pilha) {
	if((*pilha) != NULL) {
		//apaga a pilha1
		for(int i = 0; i < (*pilha)->tamanho_pilha1; i++) 
			item_apagar(&((*pilha)->vet[i]));

		//apaga a pilha2
		for(int i = 0; i < (*pilha)->tamanho_pilha2; i++) 
			item_apagar(&((*pilha)->vet[TAM_MAX -1 - i]));


		free(*pilha); *pilha = NULL;
	}
}


bool pilha1_vazia(PILHA_DUPLA* pilha) {
	if(pilha == NULL)
		return(true);
	else
		return(pilha->tamanho_pilha1 == 0);
}

bool pilha2_vazia(PILHA_DUPLA* pilha) {
	if(pilha == NULL)
		return(true);
	else
		return(pilha->tamanho_pilha2 == 0);
}


bool pilha_cheia(PILHA_DUPLA *pilha) {
	if(pilha == NULL)
		return(true);
	else
		return(pilha->tamanho_pilha1 + pilha->tamanho_pilha2 == TAM_MAX);
}


int pilha1_tamanho(PILHA_DUPLA *pilha) {
	if(pilha == NULL)
		return(-1);

	else
		return(pilha->tamanho_pilha1);
}

int pilha2_tamanho(PILHA_DUPLA *pilha) {
	if(pilha == NULL)
		return(-1);

	else
		return(pilha->tamanho_pilha2);
}


bool pilha1_empilhar(PILHA_DUPLA *pilha, ITEM *it) {
	if(!pilha_cheia(pilha)) {
		pilha->vet[pilha->tamanho_pilha1] = it;
		pilha->tamanho_pilha1++;
		return(true);
	}

	return(false);

}

bool pilha2_empilhar(PILHA_DUPLA *pilha, ITEM *it) {
	if(!pilha_cheia(pilha)) {
		pilha->vet[TAM_MAX - 1 - pilha->tamanho_pilha2] = it;
		pilha->tamanho_pilha2++;
		return(true);
	}

	return(false);

}


ITEM* pilha1_desempilhar(PILHA_DUPLA* pilha) {
	if(!pilha1_vazia(pilha)) {
		ITEM *it = pilha->vet[pilha->tamanho_pilha1 - 1];
		pilha->vet[pilha->tamanho_pilha1 - 1] = NULL;
		pilha->tamanho_pilha1--;
		return(it);
	}
	return(NULL);
}

ITEM* pilha2_desempilhar(PILHA_DUPLA* pilha) {
	if(!pilha2_vazia(pilha)) {
		ITEM *it = pilha->vet[TAM_MAX - pilha->tamanho_pilha2];
		pilha->vet[TAM_MAX - pilha->tamanho_pilha2] = NULL;
		pilha->tamanho_pilha2--;
		return(it);
	}
	return(NULL);
}


ITEM* pilha1_topo(PILHA_DUPLA* pilha) {
	if(pilha1_vazia(pilha))
		return(NULL);

	else
		return(pilha->vet[pilha->tamanho_pilha1 - 1]);
}

ITEM* pilha2_topo(PILHA_DUPLA* pilha) {
	if(pilha2_vazia(pilha))
		return(NULL);

	else
		return(pilha->vet[TAM_MAX - pilha->tamanho_pilha2]);
}

