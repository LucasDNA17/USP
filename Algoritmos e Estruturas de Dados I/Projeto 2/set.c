/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: Novembro/Dezembro de 2024

Descrição: Isto é a implementação do TAD SET. Encontram-se aqui
detalhes de implementação das funções que manipulam os conjuntos.
Para mais detalhes relativos à manipulação das estruturas de dados
(Árvore AVL e Árvore Rubro Negra), consulte os arquivos "AVL.c" e
"rubronegra.c".
*/  


#include <stdlib.h>
#include <stdio.h>
#include "set.h"


/* Definição da struct SET: ela é composta por um inteiro 
que representa a estrutura de dados utilizada (0 - Árvore AVL;
1 - Árvore Rubro Negra) e por um ponteiro void que aponta para
a estrutura de dados utilizada. */
struct set {
	int tipo;
	void *estrutura;
};


/*A função set_criar() recebe como parâmetro o inteiro que representa
a estrutura de dados que será usada para implementar o conjunto. Ela aloca
memória para o conjunto e, se a alocação obtiver sucesso, atribui o inteiro
que representa a estrutura de dados ao campo da struct, cria a estrutura de
dados correspondente e retorna o conjunto criado. Caso a alocação falhe, 
retorna-se NULL.*/ 
SET *set_criar(int tipo) {
	SET *set = (SET *) malloc(sizeof(SET));

	if(set != NULL) {
		if(tipo == 0) {
			set->tipo = 0;
			set->estrutura = (AVL *) avl_criar();
		}

		else if(tipo == 1) {
			set->tipo = 1;
			set->estrutura = (RN *) rn_criar();
		}

		else
			return(NULL);
	}

	return(set);
}


/*A função set_pertence() recebe como parâmetros um conjunto A e um
inteiro "elemento", que é o valor a ser buscado no conjunto. Caso A
seja NULL ou caso o tipo do conjunto não corresponda a nenhuma estrutura,
retorna-se imediatamente "false". Caso contrário, retorna-se o valor de retorno
da função de busca correspondente à estrutura de dados usada.*/
bool set_pertence(SET *A, int elemento) {
	if(A == NULL)
		return(false);

	else if(A->tipo == 0)
		return(avl_busca(A->estrutura, elemento));
	else if(A->tipo == 1)
		return(rn_busca(A->estrutura, elemento));

	else
		return(false);
}


/*A função set_inserir() recebe como parâmetros um conjutno s
e um inteiro "elemento", o valor a ser inserido. Caso s seja NULL,
retorna-se "false"; caso contrário, retorna-se "true" se a inserção 
obtiver êxito e "false" se não. A inserção é realizada com chamadas às
funções de inserção das estruturas de dados utilizadas.*/
bool set_inserir (SET *s, int elemento) {
	if(s == NULL)
		return(false);

	else if(s->tipo == 0)
		return(avl_inserir(s->estrutura, elemento));
	else if(s->tipo == 1)
		return(rn_inserir(s->estrutura, elemento));

	else
		return(false);
}


/*A função set_remover() recebe como parâmetros um conjunto s e 
um inteiro "elemento", o valor a ser removido do conjunto. Se s
for NULL, retorna-se "false"; caso contrário, se a remoção obtiver
sucesso, retorna-se "true" e, se não, retorna-se "false". A remoção é
realizada com chamadas às funções de remoção das estruturas de dados
implementadas.*/ 
bool set_remover(SET *s, int elemento) {
	if(s == NULL)
		return(false);

	else if(s->tipo == 0)
		return(avl_remover(s->estrutura, elemento));
	else if(s->tipo == 1)
		return(rn_remover(s->estrutura, elemento));

	else
		return(false);
}



/*A função set_apagar() recebe como parâmetro um ponteiro para um conjunto s.
Se s for NULL, a função se encerra; caso contrário, apaga-se a estrutura de 
dados implementada no conjunto (a partir das funções próprias das estruturas)
e, em seguida, apaga-se o conjunto também.*/
void set_apagar(SET **s) {
	if(*s == NULL)
		return;

	else if((*s)->tipo == 0) {
		AVL **s_aux = (AVL **) &((*s)->estrutura);
		avl_apagar(s_aux);
	}
	else if((*s)->tipo == 1) {
		RN **s_aux = (RN **) &((*s)->estrutura);
		rn_apagar(s_aux);
	}

	free(*s);
	*s = NULL;
}



/*A função set_imprimir() recebe como parâmetro um conjunto s. Caso s seja
NULL, a função se encerra; caso contrário, o conjunto s é impresso. A impressão
é realizada de acordo com as chamadas das funções correspondentes às estruturas de
dados.*/ 
void set_imprimir(SET *s) {
	if(s == NULL)
		return;

	else if(s->tipo == 0)
		avl_imprimir(s->estrutura);
	else if(s->tipo == 1)
		rn_imprimir(s->estrutura);
}




/*A função set_uniao() recebe como parâmetros dois conjuntos
A e B. Caso um deles seja NULL, retorna-se NULL; caso contrário,
cria-se outro conjunto C, que recebe a união de A e B. A operação 
de união é feita a partir das funções específicas de cada estrutura
de dados. */
SET *set_uniao(SET *A, SET *B) {
	if(A == NULL || B == NULL)
		return(NULL);
	

	SET *C = set_criar(A->tipo);
	if(C != NULL) {
		if(A->tipo == 0)
			avl_unir(A->estrutura, B->estrutura, C->estrutura);
		else
			rn_unir(A->estrutura, B->estrutura, C->estrutura);
	}
	return(C);
}


/*A função set_interseccao() recebe como parâmetros dois conjuntos
A e B. Caso um deles seja NULL, retorna-se NULL; caso contrário,
cria-se outro conjunto C, que recebe a interseccao de A e B. A operação 
de interseccao é feita a partir das funções específicas de cada estrutura
de dados. */
SET *set_interseccao(SET *A, SET *B) {
	if(A == NULL || B == NULL)
		return(NULL);

	SET *C = set_criar(A->tipo);

	if(A->tipo == 0)
		avl_intersectar(A->estrutura, B->estrutura, C->estrutura);
	else
		rn_intersectar(A->estrutura, B->estrutura, C->estrutura);

	return(C);
}








