#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "Pilha.h"


struct pilha {
	int tamanho;
	ITEM *item[TAM];
};

PILHA* pilha_criar(void) {
	PILHA* pilha = (PILHA *) malloc(sizeof (PILHA));
	if (pilha != NULL)
		pilha->tamanho = 0;
	return (pilha);
 }

void pilha_apagar(PILHA** pilha) {
	for(int i = 0; i < (*pilha)->tamanho; i++) 
		item_apagar(&((*pilha)->item[i]));
	free(*pilha);
	*pilha = NULL;
}

bool pilha_vazia(PILHA* pilha) {
	if (pilha != NULL)
		return ((pilha->tamanho == 0));
	return(false);
}

bool pilha_cheia(PILHA *pilha) {
	if (pilha != NULL)
		return ((pilha->tamanho == TAM));
	return(false);
}

int pilha_tamanho(PILHA *pilha) {
	if(pilha != NULL)
		return(pilha->tamanho);
	exit(1);
}

bool pilha_empilhar(PILHA *pilha, ITEM *it) {
	if(pilha != NULL) {
		if(!pilha_cheia(pilha)) {
			pilha->item[pilha->tamanho] = it;
			pilha->tamanho++;
			return(true);
		}
	}
	return(false);
}

ITEM *pilha_desempilhar(PILHA *pilha) {
	if(!pilha_vazia(pilha)) {
		ITEM *aux = pilha->item[pilha->tamanho - 1];
		pilha->tamanho--;
		pilha->item[pilha->tamanho] = NULL;
		return(aux);
	}
	return(NULL);
}

ITEM* pilha_topo(PILHA* pilha) {
	if((pilha != NULL) && (pilha->tamanho != 0))
		return(pilha->item[pilha->tamanho - 1]);
	return(NULL);
}



bool balanceada(char *sequencia) {
	PILHA *pilha = pilha_criar();
	
	int i = 0;
	char *leitura;
	while(sequencia[i] != '\0') {
		if(sequencia[i] == '(' || sequencia[i] == '[' || sequencia[i] == '{') 
			pilha_empilhar(pilha, item_criar(i, &sequencia[i]));
		else{
			if(pilha_vazia(pilha))
				return(false);

			char *aux = (char *) item_get_dados(pilha_desempilhar(pilha));
			if((sequencia[i] == ')' && *aux != '(') || (sequencia[i] == ']' && *aux != '[') || (sequencia[i] == '}' && *aux != '{') )
				return(false);
		}
		i++;
	}
	return(pilha_vazia(pilha));
}

