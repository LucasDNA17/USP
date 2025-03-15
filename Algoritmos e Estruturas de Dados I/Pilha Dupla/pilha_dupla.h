#ifndef PILHA_DUPLA_H
	#define PILHA_DUPLA_H

	#include <stdbool.h>
	#include <stdlib.h>
	#include "item.h"

	#define TAM_MAX 100

	typedef struct pilha_dupla_ PILHA_DUPLA;


	PILHA_DUPLA* pilha_criar(void);
  	void pilha_apagar(PILHA_DUPLA** pilha);
  	bool pilha1_vazia(PILHA_DUPLA* pilha);
  	bool pilha2_vazia(PILHA_DUPLA* pilha);
 	bool pilha_cheia(PILHA_DUPLA* pilha);
  	int pilha1_tamanho(PILHA_DUPLA* pilha);
  	int pilha2_tamanho(PILHA_DUPLA* pilha);
  	ITEM* pilha1_topo(PILHA_DUPLA* pilha);
  	ITEM* pilha2_topo(PILHA_DUPLA* pilha);
  	bool pilha1_empilhar(PILHA_DUPLA* pilha, ITEM* item);
  	bool pilha2_empilhar(PILHA_DUPLA* pilha, ITEM* item);
  	ITEM* pilha1_desempilhar(PILHA_DUPLA* pilha);
  	ITEM* pilha2_desempilhar(PILHA_DUPLA* pilha);
 	//bool balanceada(char *sequencia);


#endif 




