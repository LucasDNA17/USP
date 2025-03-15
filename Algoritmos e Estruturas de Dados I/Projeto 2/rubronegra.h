/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: Novembro/Dezembro de 2024

Descrição: Isto é a interface do TAD rubronegra, utlizado para representar
a estrutura de dados "Árvore Rubro Negra", um tipo de árvore balanceada. 
Os detalhes de implementação encontram-se no arquivo "rubronegra.c".
*/



#ifndef _RUBRO_NEGRA_H
#define _RUBRO_NEGRA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct rubronegra_ RN;

RN *rn_criar(void); 
void rn_apagar (RN **T);
bool rn_inserir(RN *T, int chave); 
bool rn_remover(RN *T, int chave);
void rn_imprimir (RN *T);
void rn_imprimir_2D (RN *T);
int rn_qtd_nos (RN *T);
void rn_unir(RN *A, RN *B, RN *U);
void rn_intersectar(RN *A, RN *B, RN *i);
bool rn_busca(RN *T, int chave);


#endif
