/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: Novembro/Dezembro de 2024

Descrição: Isto é a implementação do TAD AVL. Encontram-se aqui
detalhes de implementação das funções que manipulam as árvores AVL.
*/  


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AVL.h"



typedef struct no NO;


/* Definição da struct NO: ela é composta por um inteiro 
que representa o valor a ser armazenado ("chave"); um inteiro "FB"
que armazena o fator de balanceamento do nó; e dois nós que representam
as subárvores direita e esquerda.*/
struct no {
	int chave;
	int FB; 
	NO *esquerdo;
	NO *direito;
};


/* Definição da struct AVL: ela é composta por um nó, que é a raíz da árvore;
e um inteiro que armazena a quantidade de nós da árvore.*/
struct arv_avl {
	NO *raiz;
	int qtd_nos;
};



/*A função max() é uma função auxiliar que recebe como parâmetros dois inteiros a e b.
Ela retorna o valor máximo dentre os dois.*/
int max (int a, int b) {
	if(a > b)
		return(a);
	else
		return(b);
}


/*A função avl_criar() não recebe parâmetros. Ela aloca
memória para a AVL e, se a alocação obtiver sucesso, inicializa a raíz
como NULL e a quantidade de nós para zero, retornando a AVL criada. Caso a alocação falhe, 
retorna-se NULL.*/ 
AVL *avl_criar(void) {
	AVL *arvore = (AVL *) malloc(sizeof(AVL));
	if(arvore != NULL) {
		arvore->raiz = NULL;
		arvore->qtd_nos = 0;
	}

	return(arvore);
}


/*A função avl_cria_no() recebe como parâmetro um inteiro que é o
valor a ser armazenado no nó. Ela aloca memória para o nó e, caso 
a alocação obtenha êxito, atribui o valor de parâmetro ao campo da
struct; inicializa o fator de balanceamento do nó para zero; inicializa
as subárvores esquerda e direita para NULL e, em seguida, retorna o nó
criado. Caso a alocação falhe, retorna-se NULL.*/
NO *avl_cria_no (int chave) {
	NO *no = (NO *) malloc(sizeof(NO));
	if(no == NULL)
		return(NULL);
	else {
		no->chave = chave;
		no->FB = 0;
		no->direito = NULL;
		no->esquerdo = NULL;
		return(no);
	}
}


/*A função avl_qtd_nos recebe como parâmetro uma árvore
AVL T. Se T for NULL, retorna-se o código de erro -1; caso contrário,
retorna-se a quantidade de nós da árvore. Trata-se de uma função auxiliar 
utilizada para se otimizar a operação de intersecção.*/
int avl_qtd_nos (AVL *T) {
	if(T == NULL)
		return(-1);
	else
		return(T->qtd_nos);
}


/*A função no_altura recebe como parâmetro um nó "no". Caso o nó seja NULL,
retorna-se -1; caso contrário, retorna-se a altura do nó. A função é recursiva:
para cada nó, ele calcula, recursivamente, o máximo entre a altura da subárvore
esquerda e da subárvore direita e soma um a esse resultado.*/
int no_altura (NO *no) {
	if(no == NULL)
		return(-1);
	else
		return(max(no_altura(no->esquerdo), no_altura(no->direito)) + 1);
}


/*A função rotacao_direita() recebe como parâmetro um nó A. Ela rotaciona
o nó para a direita, ajeitando os fatores de balanceamento de acordo com 
os casos possíveis de rotação. Trata-se de uma função auxiliar necessária
para o balanceamento da AVL após inserções e remoções.*/
NO *rotacao_direita(NO *A) {
	if(A != NULL) {
		NO *B = A->esquerdo;
		A->esquerdo = B->direito;
		B->direito = A;

		if(A->FB == -2 && B->FB == -2) {
			A->FB = 1;
			B->FB  = 0;
		}

		else if(A->FB == -2 && B->FB ==-1) {
			A->FB = 0;
			B->FB  = 0;
		}

		else if(A->FB == -2 && B->FB == 0) {
			A->FB = -1;
			B->FB  = 1;
		}

		else if(A->FB == -1 && B->FB == -1) {
			A->FB = 1;
			B->FB  = 1;
		}

		else if(A->FB == -1 && B->FB == 0) {
			A->FB = 0;
			B->FB  = 1;
		}

		else if(A->FB == -1 && B->FB == 1) {
			A->FB = 0;
			B->FB  = 2;
		}


		return(B);
	}
	else
		return(NULL);
}


/*A função rotacao_esquerda() recebe como parâmetro um nó A. Ela rotaciona
o nó para a esquerda, ajeitando os fatores de balanceamento de acordo com 
os casos possíveis de rotação. Trata-se de uma função auxiliar necessária
para o balanceamento da AVL após inserções e remoções.*/
NO *rotacao_esquerda(NO *A) {
	if(A != NULL) {
		NO *B = A->direito;
		A->direito = B->esquerdo;
		B->esquerdo = A;



		if(A->FB == -2 && B->FB == -2) {
			A->FB = 1;
			B->FB  = 0;
		}

		else if(A->FB == -2 && B->FB ==-1) {
			A->FB = 0;
			B->FB  = 0;
		}

		else if(A->FB == -2 && B->FB == 0) {
			A->FB = -1;
			B->FB  = 1;
		}

		else if(A->FB == -1 && B->FB == -1) {
			A->FB = 1;
			B->FB  = 1;
		}

		else if(A->FB == -1 && B->FB == 0) {
			A->FB = 0;
			B->FB  = 1;
		}

		else if(A->FB == -1 && B->FB == 1) {
			A->FB = 0;
			B->FB  = 2;
		}

		return(B);
	
	}
	else
		return(NULL);
}


/*A função rotacao_esquerda_direita() recebe como parâmetro um nó A.
Ela realiza uma rotação esquerda no filho esquerdo de A e, em seguida,
realiza uma rotação direita em A. Trata-se de uma função auxiliar necessária
para o balanceamento da AVL após inserções e remoções.*/
NO *rotacao_esquerda_direita(NO *A) {
	if(A != NULL) {
		A->esquerdo = rotacao_esquerda(A->esquerdo);
		return  (rotacao_direita(A));
	}
	else
		return(NULL);
}


/*A função rotacao_direita_esquerda() recebe como parâmetro um nó A.
Ela realiza uma rotação direita no filho direito de A e, em seguida,
realiza uma rotação esquerda em A. Trata-se de uma função auxiliar necessária
para o balanceamento da AVL após inserções e remoções.*/
NO *rotacao_direita_esquerda(NO *A) {
	if(A != NULL) {
		A->direito = rotacao_direita(A->direito);
		return(rotacao_esquerda(A));
	}
	else
		return(NULL);
}


/* A função avl_inserir_no() recebe como parâmetros um nó que representa
a raíz da árvore, outro nó que é o nó a ser inserido, e um ponteiro para
inteiro que aponta para o campo "qtd_nos" da struct AVL. A função recursivamente
procura o local de inserção e, após encontrá-la, insere o nó e aumenta a quantidade 
de nós da árvore. Nas voltas de recursão, os fatores de balanceamento dos nós são 
atualizados e, caso necessário, as rotações são realizadas.*/
NO *avl_inserir_no(NO *raiz, NO *no, int *qtd_nos) {
	if (raiz == NULL) {
		raiz = no;
		(*qtd_nos)++;
	}
	else if(no->chave < raiz->chave)
		raiz->esquerdo = avl_inserir_no(raiz->esquerdo,no, qtd_nos);
	else if(no->chave > raiz->chave)
		raiz->direito = avl_inserir_no(raiz->direito,no, qtd_nos);
	else {
		free(no); no = NULL;
		return(raiz); //inserção de elementos iguais 
	}

	raiz->FB = no_altura(raiz->esquerdo) - no_altura(raiz->direito);

	if(raiz->FB == -2) {
		if(raiz->direito->FB <= 0)
			raiz = rotacao_esquerda(raiz);
		else
			raiz = rotacao_direita_esquerda(raiz);
	}

	if(raiz->FB == 2) {
		if(raiz->esquerdo->FB >= 0)
			raiz = rotacao_direita(raiz);
		else
			raiz = rotacao_esquerda_direita(raiz);
	}

	return(raiz);
}



/*A função avl_inserir recebe como parâmetro uma árvore AVL T e um inteiro que
corresponde ao valor a ser inserido. Se T for igual a NULL, retorna-se "false". Caso
contrário, cria-se um nó que armazena o valor (é verificado se o nó foi criado corretamente) e 
esse nó é inserido com a ajuda da função avl_inserir_no().*/
bool avl_inserir(AVL *T, int chave){
	if (T == NULL)
		return(false);
	else {
		NO *novo_no = avl_cria_no(chave);
		if(novo_no != NULL){
			T->raiz = avl_inserir_no(T->raiz, novo_no, &(T->qtd_nos));
			return(true);
		}
		return(false);
	}
}



/*A função arvore_imprimir() recebe como parâmetro um nó que
representa a raíz da árvore. Ela percorre todos os nós, seguindo um
percurso em-ordem, de modo a imprimí-los.*/
void arvore_imprimir(NO *raiz) {
	if(raiz != NULL) {
		arvore_imprimir(raiz->esquerdo);
		printf("%d, ", raiz->chave);
		arvore_imprimir(raiz->direito);
	}
}


/*A função avl_imprimir() recebe como parâmetro uma árvore AVL.
Caso ela seja nula, nada é feito; caso contrário, ela é imprimida com a
ajuda da função arvore_imprimir().*/
void avl_imprimir (AVL *T) {
	if(T->raiz != NULL) {
		arvore_imprimir(T->raiz);
		printf("\n");
	}
}



/*A função arvore_imprimir_2D recebe como parâmetro um nó
que representa a raíz da árvore e um inteiro que representa o espaço
entre os nós na representação da árvore. A função representa, de maneira 
bidimensional, uma árvore binária, possibilitando verificar o balanceamento.*/ 
void arvore_imprimir_2D (NO *raiz, int espaço) {
	if(raiz == NULL)
		return;

	espaço += 10; /*espaço arbitrário*/

	arvore_imprimir_2D(raiz->direito, espaço);

	printf("\n");
	for (int i = 10; i < espaço; i++)
        printf(" ");
    printf("%d\n", raiz->chave);

    
   arvore_imprimir_2D(raiz->esquerdo, espaço);
}



/*A função avl_imprimir_2D recebe como parâmetro uma árvore AVL. Caso ela
não seja nula, ela é impressa bidimensionalmente com a ajuda da função avl_imprimir_2D().*/
void avl_imprimir_2D (AVL *T) {
	if(T != NULL)
		arvore_imprimir_2D(T->raiz, 0);
}




/*A função arvore_apagar() recebe como parâmetro um ponteiro para um ponteiro de nó,
o qual representa a raíz da árvore. Ela realiza o percurso pós-ordem para apagar a árvore.*/
void arvore_apagar(NO **raiz) {
	if((*raiz) != NULL) {
		arvore_apagar(&((*raiz)->esquerdo));
		arvore_apagar(&((*raiz)->direito));
		free(*raiz);
		*raiz = NULL;
	}
}


/* A função avl_apagar recebe como parâmetro um ponteiro para ponteiro de uma árvore AVL T.
Caso esta não seja nula, ela é apagada com o auxílio da função arvore_apagar().*/
void avl_apagar(AVL **T) {
	if((*T) != NULL) {
		arvore_apagar(&((*T)->raiz));
		free(*T);
		*T = NULL;
	} 
}


/*A função troca_max_esq() recebe como parâmetros um NO "troca", que
representa o nó que será trocado; o nó que representa a raíz da árvore; e um 
nó que armazena o nó anterior do percurso recursivo feito para se achar o nó com o qual 
o nó "troca" será trocado. A função troca este nó com o maior elemento de sua subárvore esquerda e,
em seguida, apaga este nó. */
void troca_max_esq(NO *troca, NO *raiz, NO *ant) {
 if(troca->direito != NULL){
 	troca_max_esq(troca->direito, raiz, troca);
 	return;
 }
 if(raiz == ant)
 	ant->esquerdo = troca->esquerdo;
 else
 	ant->direito = troca->esquerdo;

 raiz->chave = troca->chave;
 free(troca); troca = NULL;
}


/*A função árvore_remover recebe como parâmetro um ponteiro duplo
para nó, o qual representa a raíz da árvore; um inteiro que representa
o valor a ser removido da árvore; e um ponteiro para inteiro que aponta
para a quantidade de nós da árvore. A função procura recursivamente o nó a ser
removido e, quando o encontra, remove-o dependendo se ele possuir dois ou menos filhos:
no primeiro caso, usa-se a função troca_max_esq(), enquanto que, no segundo, o nó é
apenas substituído pelo seu filho não-nulo. Na volta da recursão, os fatores de balanceamento
são ajeitados e rotações são feitas para corrigir desbalanceamentos.*/
NO *arvore_remover(NO **raiz, int chave, int *qtd_nos) {
	if(*raiz == NULL)
		return(NULL);

	NO *aux;
	if((*raiz)->chave == chave) {
		(*qtd_nos)--;
		if((*raiz)->esquerdo == NULL || (*raiz)->direito == NULL) {
			aux = *raiz;
			if((*raiz)->esquerdo == NULL)
				*raiz = (*raiz)->direito;
			else
				*raiz = (*raiz)->esquerdo;


			free(aux); aux = NULL;
		}
	else 
		troca_max_esq((*raiz)->esquerdo, (*raiz), (*raiz));
	}

	else
		if(chave < ((*raiz)->chave))
			(*raiz)->esquerdo = arvore_remover(&(*raiz)->esquerdo, chave, qtd_nos);
		else
			(*raiz)->direito = arvore_remover(&((*raiz)->direito), chave, qtd_nos);


	if(*raiz != NULL) {
		(*raiz)->FB = no_altura((*raiz)->esquerdo) - no_altura((*raiz)->direito);

		if((*raiz)->FB == -2) {
			if((*raiz)->direito->FB <= 0)
				*raiz = rotacao_esquerda(*raiz);
			else
				*raiz = rotacao_direita_esquerda(*raiz);
		}

		if((*raiz)->FB == 2) {
			if((*raiz)->esquerdo->FB >= 0)
				*raiz = rotacao_direita(*raiz);
			else
				*raiz = rotacao_esquerda_direita(*raiz);
		} 
	}

	return(*raiz);
}



/*A função avl_remover() recebe como parâmetro uma árvore AVL e um inteiro
que representa o valor a ser removido. Caso a árvore seja NULL, retorna-se "false"; caso
contrário, retorna-se, com a ajuda da função arvore_remover(), o êxito ou não da remoção.*/
bool avl_remover(AVL *T, int chave) {
	if(T != NULL) 
		return(arvore_remover(&(T->raiz), chave, &(T->qtd_nos)) != NULL);
	else
		return(false);
}



/*A função árvore_buscar() recebe como parâmetro um nó que representa a raíz da árvore e
um inteiro que representa o valor a ser buscado. Caso a árvore seja NULL ou o valor não é encontrado,
retorna-se "false"; caso contrário, retorna-se "true". A busca é feita de maneira recursiva, aproveitando-se
da estrutura de árvores binárias.*/
bool arvore_buscar(NO *raiz, int chave) {
	if(raiz == NULL)
		return(false);

	else if((raiz->chave) == chave)
		return(true);
	else if((raiz->chave) > chave)
		return(arvore_buscar(raiz->esquerdo, chave));
	else
		return(arvore_buscar(raiz->direito, chave));
}



/*A função avl_busca() recebe como parâmetro uma árvore AVL T e um
inteiro que representa o valor a ser buscado. Caso a árvore seja NULL, retorna-se
"false"; caso contrário, retorna-se o resultado da busca, obtido pela função 
arvore_buscar().*/
bool avl_busca(AVL *T, int chave) {
	if(T != NULL) 
		return(arvore_buscar(T->raiz, chave));

	else
		return(false);
}



/*A função avl_vazia() recebe como parâmetro uma árvore AVL T. Caso a árvore
seja NULL, ela retorna "true"; caso contrário, ela verifica se a árvore é vazia ("true")
ou não ("false").*/
bool avl_vazia(AVL *T) {
	if(T != NULL)  
		return(T->raiz == NULL ? true : false);

	return(true);

}


/*A função arvore_unir_aux() recebe como parâmetros um nó
que representa a raiz de uma árvore A e uma árvore B. A função
insere todos os valores da árvore A em B.*/
void arvore_unir_aux(NO *raizA, AVL *B) {
	if(raizA != NULL) {
		avl_inserir(B, raizA->chave);
		arvore_unir_aux(raizA->esquerdo, B);
		arvore_unir_aux(raizA->direito, B);
	}
}



/*A função avl_unir() recebe como parâmetro três árvores
AVL: A, B, U. A função, com o auxílio da função arvore_unir_aux, insere 
todos os elementos de A e B em U, de modo a obter a união entre A e B.*/
void avl_unir(AVL *A, AVL *B, AVL *U) {
	if(A == NULL || B == NULL)
		return;

	arvore_unir_aux(A->raiz, U);
	arvore_unir_aux(B->raiz, U);
}


/*A função arvore_intersectar_aux() recebe como parâmetros três
nós que representam as raízes de três árvores: A, B e I.  Para 
cada nó em A, ela procura pelo valor deste nó em B e, caso ela o 
encontre, insere-o em I. Desse modo, a função obtém a interseção 
entre A e B.*/
void arvore_intersectar_aux(NO *raizA, AVL *B, AVL *I) {
	if(raizA != NULL) {
		if(avl_busca(B, raizA->chave))
			avl_inserir(I, raizA->chave);

		arvore_intersectar_aux(raizA->esquerdo, B, I);
		arvore_intersectar_aux(raizA->direito, B, I);
	}
}


/*A função avl_intersectar recebe como parâmetros três árvores AVL:
A, B e I. Caso A ou B seja NULL, retorna-se; caso contrário, verifica-se qual
árvore possui a menor quantidade de nós e, a partir dessa informação, faz-se
a interseção entre A e B (em I) com o auxílio da função arvore_intersectar_aux().*/
void avl_intersectar(AVL *A, AVL *B, AVL *I) {
	if(A == NULL || B == NULL)
		return;

	if(avl_qtd_nos(A) < avl_qtd_nos(B))
		arvore_intersectar_aux(A->raiz, B, I);
	else
		arvore_intersectar_aux(B->raiz, A, I);
}






