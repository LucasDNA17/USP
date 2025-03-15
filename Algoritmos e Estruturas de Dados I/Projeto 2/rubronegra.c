/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: Novembro/Dezembro de 2024

Descrição: Isto é a implementação do TAD rubronegra. Encontram-se aqui
detalhes de implementação das funções que manipulam as árvores Rubro Negras.
*/  


#include "rubronegra.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct no_ NO;

/* Definição da struct NO: ela é composta por um inteiro 
que representa o valor a ser armazenado ("chave"); um inteiro "cor"
que armazena a cor da aresta incidente no nó; e dois nós que representam
as subárvores direita e esquerda.*/
struct no_ {
    NO *esq;
    NO *dir;
    int chave;
    int cor; /*Preto = 0; Vermelho = 1*/
};

/* Definição da struct RN: ela é composta por um nó, que é a raíz da árvore;
e um inteiro que armazena a profundidade da árvore.*/
struct rubronegra_ {
    NO *raiz;
    int profundidade;
};

/* A função Vermelho verifica se um nó é vermelho.
   Retorna 1 (true) se o nó for vermelho; caso contrário, retorna 0 (false). */
int Vermelho(NO *no){
    if (no == NULL)
        return 0;
    return (no->cor == 1);
}

/* A função rn_criar cria uma nova árvore rubro-negra.
   A árvore é inicializada com raiz nula e profundidade -1. */
RN *rn_criar(void){
    RN *arvore = (RN*) malloc(sizeof(RN));
    if (arvore != NULL){
        arvore->raiz = NULL;
        arvore->profundidade = -1;
    }
    return arvore;
}

/*A função rn_arvore_apagar() recebe como parâmetro um ponteiro para um ponteiro de nó,
o qual representa a raíz da árvore. Ela realiza o percurso pós-ordem para apagar a árvore.*/
void rn_arvore_apagar(NO **raiz) {
	if((*raiz) != NULL) {
		rn_arvore_apagar(&((*raiz)->esq));
		rn_arvore_apagar(&((*raiz)->dir));
		free(*raiz);
		*raiz = NULL;
	}
}


/* A função rn_apagar recebe como parâmetro um ponteiro para ponteiro de uma árvore Rubro Negra T.
Caso esta não seja nula, ela é apagada com o auxílio da função arvore_apagar().*/
void rn_apagar(RN **T) {
	if((*T) != NULL) {
		rn_arvore_apagar(&((*T)->raiz));
		free(*T);
		*T = NULL;
	} 
}

/* A função rn_cria_no cria um novo nó para a árvore rubro-negra.
   O nó é inicializado com a chave recebida e com a cor vermelha. */
NO *rn_cria_no(int chave) {
    NO *novo_no = (NO *) malloc(sizeof(NO));
    if (novo_no != NULL) {
        novo_no->chave = chave;
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        novo_no->cor = 1;
    }
    return novo_no;
}


/* A função rodar_direita realiza uma rotação à direita
   para corrigir desequilíbrios na árvore rubro-negra. */
NO* rodar_direita(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    b->cor = a->cor;
    a->cor = 1;
    return b;
}

/* A função rodar_esquerda realiza uma rotação à esquerda
   para corrigir desequilíbrios na árvore rubro-negra. */
NO* rodar_esquerda(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = 1;
    return b;
}

/* A função inverter_cores inverte as cores do nó atual
   e de seus filhos, corrigindo eventuais violação das
   regras da árvore rubro-negra. */
NO* inverter_cores(NO *a) {
    a->cor = !a->cor;
    if (a->esq != NULL) 
        a->esq->cor = !a->esq->cor;
    if (a->dir != NULL) 
        a->dir->cor = !a->dir->cor;
    
    return a;
}

/* A função rn_inserir_no insere recursivamente um nó na árvore.
   Após a inserção, a função realiza as rotações e ajustes necessários
   para manter as propriedades da árvore rubro-negra. */
NO *rn_inserir_no(NO *raiz, NO *novo_no){
    if (raiz == NULL)
        raiz = novo_no;
    else if(novo_no->chave < raiz->chave)
        raiz->esq = rn_inserir_no(raiz->esq, novo_no);
    else if(novo_no->chave > raiz->chave)
        raiz->dir = rn_inserir_no(raiz->dir, novo_no);
    else {
        free(novo_no); novo_no = NULL;
        return(raiz); //inserção de elementos iguais 
    }
    
    if (Vermelho(raiz->dir))
        raiz = rodar_esquerda(raiz);
    if (Vermelho(raiz->esq) && Vermelho(raiz->esq->esq))
        raiz = rodar_direita(raiz);
    if (Vermelho(raiz->esq) && Vermelho(raiz->dir))
        raiz = inverter_cores(raiz);
    
    return(raiz);
}

/* A função rn_inserir insere um valor na árvore rubro-negra.
   A função cria um novo nó e utiliza rn_inserir_no para realizar a inserção. */
bool rn_inserir(RN *T, int chave){
    if (T == NULL)
        return(false);

    NO *novo_no;
    novo_no = rn_cria_no(chave);
    if (novo_no != NULL){
        T->raiz = rn_inserir_no(T->raiz, novo_no);
        T->raiz->cor = 0; //garante que a raiz da arvore é preta
        return(true);
    }
    return(false);
    }



/* A função removeMin encontra e remove o menor nó em uma subárvore.
   Ela é usada para substituir nós em casos de remoção na árvore rubro-negra.
   Após encontrar o menor nó, ajusta as ligações do nó pai para manter a integridade da árvore. */
NO* removeMin(NO *troca, NO *raiz, NO *ant) {
    if(troca->esq != NULL){
        removeMin(troca->esq, raiz, troca);
        return(troca); 
 }
    if(raiz == ant)
        ant->dir = troca->dir;
    else
        ant->esq = troca->dir;

    raiz->chave = troca->chave;
    free(troca); troca = NULL;
}

/* A função propagaEsquerda ajusta a subárvore à esquerda antes de 
   uma operação, garantindo que as propriedades rubro-negra sejam respeitadas.
   É utilizada em operações de remoção. */
NO *propagaEsquerda(NO *r){
    if(r == NULL)
        return(NULL);
    if (r->esq != NULL && !Vermelho(r->esq) && !Vermelho(r->esq->esq)){
        inverter_cores(r);
        if (r->dir != NULL && Vermelho(r->dir->esq)) {
            r->dir = rodar_direita(r->dir);
            r = rodar_esquerda(r);
            inverter_cores(r);
        }
    }
    return r;
}

/* A função propagaDireita ajusta a subárvore à direita antes de 
   uma operação, garantindo que as propriedades rubro-negra sejam respeitadas.
   É utilizada em operações de remoção. */
NO *propagaDireita(NO *r){
    if(r == NULL)
        return(NULL);

    if (Vermelho(r->esq))
        r = rodar_direita(r);
    if (r->dir != NULL && !Vermelho(r->dir) && !Vermelho(r->dir->esq)){
        inverter_cores(r);
        if (r->esq != NULL && Vermelho(r->esq->esq)) {
            r = rodar_direita(r);
            inverter_cores(r);
        }
    }
    return r;
}

/* A função restaura corrige violações das propriedades da árvore rubro-negra 
   após operações de remoção ou inserção. Ela garante que a árvore mantenha 
   seu balanceamento e respeite as regras de coloração. */
NO *restaura(NO *r) {
    // Corrigir violação da regra 1: Aresta vermelha na direita
    if (Vermelho(r->dir) && !Vermelho(r->esq)) {
        r = rodar_esquerda(r);
    }
    // Corrigir violação da regra 2: Duas arestas vermelhas consecutivas
    if (Vermelho(r->esq) && Vermelho(r->esq->esq)) {
        r = rodar_direita(r);
    }
    // Corrigir violação da regra 3: Arestas esquerda e direita vermelhas
    if (Vermelho(r->esq) && Vermelho(r->dir)) {
        r = inverter_cores(r);
    }

    return r;
}

/*A função min() recebe como parâmetro um nó que representa a raíz da árvore.
Se a raíz for NULL, retorna-se NULL; caso contrário, retorna-se o nó com o menor
valor da árvore.*/
NO *min(NO *raiz) {
    if(raiz == NULL)
        return(NULL);

    if(raiz->esq != NULL)
        return(min(raiz->esq));
    else
        return(raiz);
}


/* A função rn_remover_aux realiza a remoção recursiva de um nó com a chave
   especificada. Após a remoção, ajusta as propriedades da árvore para manter
   as regras da árvore rubro-negra. */
NO *rn_remover_aux(NO *r, int chave){
    if (r == NULL)
        return NULL;

    if(r->chave == chave){
        /*caso folha ou 1 só filho*/
        if(r->esq == NULL || r->dir == NULL){
            NO *aux = r;
            if (r->esq == NULL)
                r = r->dir;
            else
                r = r->esq;
            free(aux);
            aux = NULL;
        }
        /*caso 2 filhos*/
        else{
            r = propagaDireita(r);
            NO *x = min(r->dir);
            r->chave = x->chave;
            r->dir = removeMin(r->dir, r, r);
        }
    }

    else{
        if(chave < r->chave){
            r = propagaEsquerda(r);
            r->esq = rn_remover_aux(r->esq, chave);
        }
        else{
            r = propagaDireita(r);
            r->dir = rn_remover_aux(r->dir, chave);
        }
    }
    if (r != NULL)
        r = restaura(r);

    return(r);
}


/* A função rn_remover remove um nó com a chave especificada de uma árvore
   rubro-negra. Ela chama a função auxiliar para realizar a remoção recursiva. */
bool rn_remover(RN *T, int chave) {
    if(T != NULL) 
        return(rn_remover_aux(T->raiz, chave) != NULL);
    else
        return(false);
}



/*A função rn_arvore_imprimir_2D recebe como parâmetro um nó
que representa a raíz da árvore e um inteiro que representa o espaço
entre os nós na representação da árvore. A função representa, de maneira 
bidimensional, uma árvore binária, possibilitando verificar o balanceamento.*/ 
void rn_arvore_imprimir_2D (NO *raiz, int espaço) {
	if(raiz == NULL)
		return;

	espaço += 10; /*espaço arbitrário*/

	rn_arvore_imprimir_2D(raiz->dir, espaço);

	printf("\n");
	for (int i = 10; i < espaço; i++)
        printf(" ");
    printf("%d\n", raiz->chave);

    
   rn_arvore_imprimir_2D(raiz->esq, espaço);
}



/*A função rn_imprimir_2D recebe como parâmetro uma árvore rn. Caso ela
não seja nula, ela é impressa bidimensionalmente com a ajuda da função rn_imprimir_2D().*/
void rn_imprimir_2D (RN *T) {
	if(T != NULL)
		rn_arvore_imprimir_2D(T->raiz, 0);
}

/*A funçãoo conta_nos_aux recebe como parâmetro um nó que representa a raíz
da árvore. Caso a raíz seja NULL, retorna-e 0; caso contrário, calcula-se 
recursivamente a quantidade de nós da árvore.*/
int conta_nos_aux(NO *raiz){
    if (raiz == NULL)
        return 0;
    
    return 1 + conta_nos_aux(raiz->esq) + conta_nos_aux(raiz->dir);
}


/* A função rn_qtd_nos() recebe como parâmetro uma árvore RN T. Caso T seja NULL, retorna-se 0.
Caso contrário, usa-se a função conta_nos_aux() para contar a quantidade de nós da árvore.*/
int rn_qtd_nos(RN *T) {
    if (T == NULL)
        return 0;

    return conta_nos_aux(T->raiz);
}

/*A função rn_arvore_unir_aux() recebe como parâmetros um nó
que representa a raiz de uma árvore A e uma árvore B. A função
insere todos os valores da árvore A em B.*/
void rn_arvore_unir_aux(NO *raizA, RN *B) {
	if(raizA != NULL) {
		rn_inserir(B, raizA->chave);
		rn_arvore_unir_aux(raizA->esq, B);
		rn_arvore_unir_aux(raizA->dir, B);
	}
}



/*A função rn_unir() recebe como parâmetro três árvores
rn: A, B, U. A função, com o auxílio da função arvore_unir_aux, insere 
todos os elementos de A e B em U, de modo a obter a união entre A e B.*/
void rn_unir(RN *A, RN *B, RN *U) {
	if(A == NULL || B == NULL)
		return;

	rn_arvore_unir_aux(A->raiz, U);
	rn_arvore_unir_aux(B->raiz, U);
}

/*A função rn_arvore_intersectar_aux() recebe como parâmetros três
nós que representam as raízes de três árvores: A, B e I.  Para 
cada nó em A, ela procura pelo valor deste nó em B e, caso ela o 
encontre, insere-o em I. Desse modo, a função obtém a interseção 
entre A e B.*/
void rn_arvore_intersectar_aux(NO *raizA, RN *B, RN *I) {
	if(raizA != NULL) {
		if(rn_busca(B, raizA->chave))
			rn_inserir(I, raizA->chave);

		rn_arvore_intersectar_aux(raizA->esq, B, I);
		rn_arvore_intersectar_aux(raizA->dir, B, I);
	}
}


/*A função rn_intersectar recebe como parâmetros três árvores rn:
A, B e I. Caso A ou B seja NULL, retorna-se; caso contrário, verifica-se qual
árvore possui a menor quantidade de nós e, a partir dessa informação, faz-se
a interseção entre A e B (em I) com o auxílio da função rn_arvore_intersectar_aux().*/
void rn_intersectar(RN *A, RN *B, RN *I) {
	if(A == NULL || B == NULL)
		return;

	if(rn_qtd_nos(A) < rn_qtd_nos(B))
		rn_arvore_intersectar_aux(A->raiz, B, I);
	else
		rn_arvore_intersectar_aux(B->raiz, A, I);
}

/*A função rn_arvore_buscar() recebe como parâmetro um nó que representa a raíz da árvore e
um inteiro que representa o valor a ser buscado. Caso a árvore seja NULL ou o valor não é encontrado,
retorna-se "false"; caso contrário, retorna-se "true". A busca é feita de maneira recursiva, aproveitando-se
da estrutura de árvores binárias.*/
bool rn_arvore_buscar(NO *raiz, int chave) {
	if(raiz == NULL)
		return(false);

	else if((raiz->chave) == chave)
		return(true);
	else if((raiz->chave) > chave)
		return(rn_arvore_buscar(raiz->esq, chave));
	else
		return(rn_arvore_buscar(raiz->dir, chave));
}

/*A função avl_busca() recebe como parâmetro uma árvore AVL T e um
inteiro que representa o valor a ser buscado. Caso a árvore seja NULL, retorna-se
"false"; caso contrário, retorna-se o resultado da busca, obtido pela função 
arvore_buscar().*/
bool rn_busca(RN *T, int chave) {
	if(T != NULL) 
		return(rn_arvore_buscar(T->raiz, chave));

	else
		return(false);
}


/*A função rn_arvore_imprimir() recebe como parâmetro um nó que
representa a raíz da árvore. Ela percorre todos os nós, seguindo um
percurso em-ordem, de modo a imprimí-los.*/
void rn_arvore_imprimir(NO *raiz) {
    if(raiz != NULL) {
        rn_arvore_imprimir(raiz->esq);
        printf("%d, ", raiz->chave);
        rn_arvore_imprimir(raiz->dir);
    }
}


/*A função rn_imprimir() recebe como parâmetro uma árvore AVL.
Caso ela seja nula, nada é feito; caso contrário, ela é imprimida com a
ajuda da função rn_arvore_imprimir().*/
void rn_imprimir (RN *T) {
    if(T->raiz != NULL) {
        rn_arvore_imprimir(T->raiz);
        printf("\n");
    }
}
