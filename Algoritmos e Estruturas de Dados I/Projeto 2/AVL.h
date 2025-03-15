/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: Novembro/Dezembro de 2024

Descrição: Isto é a interface do TAD AVL, utlizado para representar
a estrutura de dados "Árvore AVL", um tipo de árvore balanceada. 
Os detalhes de implementação encontram-se no arquivo "AVL.c".
*/


#ifndef _ARVORE_AVL_H
#define _ARVORE_AVL_H
 
  #include <stdbool.h>

  #define ERRO -32000
  #define FILHO_ESQ 0
  #define FILHO_DIR 1

 typedef struct arv_avl AVL;
 
 AVL *avl_criar(void);
 bool avl_inserir (AVL *T, int chave);
 void avl_imprimir (AVL *T);
 void avl_imprimir_2D (AVL *T);
 int avl_qtd_nos (AVL *T);
 void avl_apagar (AVL **T);
 bool avl_remover(AVL *T, int chave);
 bool avl_busca(AVL *T, int chave);
 bool avl_vazia(AVL *T);
 void avl_unir(AVL *A, AVL *B, AVL *U);
 void avl_intersectar(AVL *A, AVL *B, AVL *i);


 //int *avl_lista_nos(AVL *T);
 
 
#endif
