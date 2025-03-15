/* 
Autoria: Lucas Dúckur Nunes Andreolli / Rafael Perez Carmanhani
Data: Novembro/Dezembro de 2024

Descrição: Isto é a interface do TAD SET, utlizado para representar
a estrutura matemática de um conjunto. Os detalhes de implementação encontram-se
no arquivo "set.c".
*/  


#ifndef _SET_H
#define _SET_H

  #include "AVL.h" 
  #include "rubronegra.h" 
                    
                   

 typedef struct set SET;

  SET *set_criar(int tipo);
  bool set_pertence(SET *A, int elemento);
  bool set_inserir (SET *s, int elemento);
  bool set_remover(SET *s, int elemento);
  void set_apagar(SET **s);
  void set_imprimir(SET *s);
  SET *set_uniao(SET *A, SET *B);
  SET *set_interseccao(SET *A, SET *B);
  
#endif
