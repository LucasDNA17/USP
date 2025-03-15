/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: setembro/outubro de 2024
Descrição: Isto é a interface do TAD GRAFO, utlizado para representar
um grafo, isto é, um conjunto finito de nós e um conjunto de pares desses
nós. Geometricamente, os nós são entendidos como pontos e os pares como 
arestas entre esses pontos.
*/    



#ifndef GRAFO_H
	#define GRAFO_H

	#include "item.h"
	#include "lista_encadeada.h"

	/*
	A struct GRAFO é composta por um inteiro que representa a quantidade de nós,
	e um vetor de listas encadeadas que representam as arestas. Os elementos da lista
	encadeada associada ao i-ésimo elemento do vetor são os nós que compartilham uma
	aresta com o i-ésimo nó.
	*/ 
	typedef struct grafo_ {
	int quantidade_nos;
	LISTA_ENCADEADA **arestas;
	} GRAFO;
	
	typedef struct no NO;

	/*
	A função grafo_criar() recebe como parâmetro a quantidade de nós do grafo. Ela
	aloca memória para o grafo e para o vetor de listas (de acordo com a quantidade de
	nós),cria as listas e atribui o valor da quantidade de nós ao campo da struct. Se 
	não for possível alocar espaço para o grafo ou para o vetor de listas, retorna-se NULL;
	caso contrário, é retornado o grafo criado.
	*/
	GRAFO *grafo_criar(int quantidade_nos);


	/*
	A função grafo_inserir_aresta() recebe como parâmetros um ponteiro para a struct GRAFO; dois
	inteiros que representam dois nós diferentes; e outro inteiro que representa o valor da
	aresta entre os dois nós.
	A função insere o valor da aresta nas duas listas associadas aos nós, de modo a armazenar
	também, em cada lista, o valor do outro nó a que a aresta está conectada. 
	*/
	void grafo_inserir_aresta(GRAFO *grafo, int no1, int no2, int valor);


	/*
	A função grafo_get_aresta() recebe como parâmetros um ponteiro para a struct GRAFO e dois
	inteiros que representam dois nós.
	A função realiza uma busca pelo segundo nó na lista associada ao primerio nó e retorna o
	valor da aresta entre eles caso ela exista. Se ela não existir, retorna-se -1 (assume-se que
	cada aresta tenha um valor positivo). 
	Vale ressaltar que a complexidade desse processo resume-se à complexidade da operação de busca
	na lista encadeada. Essa complexidade é descrita no header "lista_encadeada.h"
	*/
	int grafo_get_aresta(GRAFO *grafo, int no1, int no2);


	/*
	A função grafo_apagar() recebe como parâmetro um ponteiro para ponteiro da struct GRAFO. 
	Ela apaga todas as listas do vetor de listas, o vetor de listas em si, e, por fim, o grafo
	inteiro.	
	*/
	bool grafo_apagar(GRAFO **grafo);

	LISTA_ENCADEADA *grafo_get_adjacentes(GRAFO *grafo, int no);


#endif