#ifndef LISTA_H
	#define LISTA_H

	#define TAM_MAX 100 /*estimativa do tamanho máximo da lista*/
	#define inicial 0
	#define ERRO -32000
	#define ORDENADA 0 /*0 = lista não ordenada; 1 = lista ordenada*/
	#include "item.h"
	#include <stdbool.h>

	typedef struct lista_ LISTA;


	LISTA *lista_criar(bool ordenada);
	bool lista_inserir_fim(LISTA *lista, ITEM *item);
	bool lista_apagar(LISTA **lista);
	ITEM *lista_remover(LISTA *lista, int chave);
	//ITEM *lista_busca(LISTA *lista, int chave);
	int lista_tamanho(LISTA *lista);
	bool lista_vazia(LISTA *lista);
	bool lista_cheia(LISTA *lista);
	void lista_imprimir(LISTA *lista);
	bool lista_inserir(LISTA *lista, ITEM *item);

#endif