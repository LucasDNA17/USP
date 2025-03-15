#include "Pilha.h"


struct no {
	ITEM *item;
	NO *anterior;
};


struct pilha {
	int tamanho;
	NO *topo;
};

  PILHA* pilha_criar(void) {
  	PILHA *p = (PILHA *) malloc(sizeof(PILHA));
  	return(p);
  }

  void pilha_apagar(PILHA** pilha) {
  	while(!pilha_vazia(*pilha)) {
  		item_apagar(&(*pilha)->topo->item);
  		NO* aux = (*pilha)->topo;
  		(*pilha)->topo = aux->anterior;
  		free(aux); aux = NULL;
  	}
  	free(*pilha);
  	*pilha = NULL;
  }
  
  bool pilha_vazia(PILHA* pilha) {
  	if(!pilha_tamanho(pilha))
  		return(true);
  	return(false);
  }

  bool pilha_cheia(PILHA* pilha) {
  	if(pilha != NULL) {
  		NO* temp;
  		if(pilha_empilhar(pilha, temp->item))
  			return(true);
  	}
  	return(false);
  }

  int pilha_tamanho(PILHA* pilha) {
  	if(pilha == NULL)
  		return(0);
  	return(pilha->tamanho);
  }

  ITEM* pilha_topo(PILHA* pilha) {
  	if(pilha == NULL)
  		return(NULL);

  	return(pilha->topo->item);
  }

  bool pilha_empilhar(PILHA* pilha, ITEM* item) {
  	if(pilha != NULL && item != NULL) {
	  	NO* aux = (NO *) malloc(sizeof(NO));
	  	if(aux != NULL) {
		  	aux->item = item;
		  	aux->anterior = pilha->topo;
		  	pilha->topo = aux;
		  	pilha->tamanho++;
		  	return(true);
		}
  	}
  	return(false);
  }

  ITEM* pilha_desempilhar(PILHA* pilha) {
  	if(pilha_vazia(pilha))
  		return(NULL);

  	ITEM* it = pilha->topo->item;
  	NO* aux = pilha->topo;
  	pilha->topo = aux->anterior;
  	pilha->tamanho--;
  	free(aux); aux->anterior = NULL; aux = NULL;
  	return(it);
  }

  int verifica_tamanho(PILHA *pilha1, PILHA *pilha2) {
    NO *aux1 = pilha1->topo;
    NO *aux2 = pilha2->topo; 

    while(aux1 != NULL && aux2 != NULL) {
      aux1 = aux1->anterior;
      aux2 = aux2->anterior;
    }

    if(aux1 != NULL)
      return(1); //pilha1 > pilha2

    else if(aux2 != NULL)
      return(-1)

    else
      return(0);
  }