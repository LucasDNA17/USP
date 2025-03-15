/*
Código escrito por Lucas Dúckur Nunes Andreolli e Rafael Pérez Carmanhani
Segundo semestre de 2024

As implementações a seguir são modificações dos algoritmos de ordenação
de modo a se medir a quantidade de comparações de chaves e de movimentações
de registros que cada algoritmo exige.
*/


#include "sorting.h"
#include <math.h>


unsigned long long int BubbleSort(int *vet, int tamanho, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	for(int i = 0; i < tamanho; i++) {
		bool houve_troca = false;
		for(int j = 0; j < tamanho - i - 1; j++) {
			contador_comparacoes++;
			if(vet[j] > vet[j + 1]) {
				int aux = vet[j];

				contador_trocas++;
				vet[j] = vet[j + 1];
				contador_trocas++;
				vet[j + 1] = aux;
				houve_troca = true;
			}
		}

		if(!houve_troca)
			break;
	}


	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);

}


unsigned long long int SelectionSort(int *vet, int tamanho, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	for(int i = 0; i < tamanho - 1; i++) {
		int indice_menor = i;
		for(int j = i + 1; j < tamanho; j++) {
			contador_comparacoes++;
			if(vet[j] < vet[indice_menor]) 
				indice_menor = j; 
		}

		if(indice_menor != i) {
			int aux = vet[indice_menor];
			contador_trocas++;
			vet[indice_menor] = vet[i];
			contador_trocas++;
			vet[i] = aux;
		}
	}

	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);
}


unsigned long long int InsertionSort(int *vet, int tamanho, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	for(int i = 1; i < tamanho; i++) {
		int j;
		int elemento = vet[i];
		for(j = i - 1; j >= 0; j--) {
			contador_comparacoes++;
			if(elemento >= vet[j])
				break;
			vet[j + 1] = vet[j];
			contador_trocas++;
		}

		contador_trocas++;
		vet[j + 1] = elemento;
	}

	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);

}


unsigned long long int ShellSort(int *vet, int tamanho, int *incrementos, int quantidade_incrementos, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	for(int i = 0; i < quantidade_incrementos; i++) {
		int incremento = incrementos[i];

		for(int j = incremento; j < tamanho; j++) {
			int elemento =  vet[j];

			int k;
			for(k = j - incremento; k >= 0; k -= incremento) {
				contador_comparacoes++;
				if(elemento >= vet[k])
					break;

				vet[k + incremento] = vet[k];
				contador_trocas++;
			}

			contador_trocas++;
			vet[k + incremento] = elemento;

		}
	}
	
	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);
}



int mediana_de_tres(int *vet, int fim, int inicio,  long long unsigned int *qtd_comparacoes) {
	int meio = inicio + (fim - inicio)/2;
	*qtd_comparacoes += 4;
	if ((vet[inicio] >= vet[meio] && vet[inicio] <= vet[fim]) || (vet[inicio] <= vet[meio] && vet[inicio] >= vet[fim])) {
        return (vet[inicio]); 
    } else if ((vet[meio] >= vet[inicio] && vet[meio] <= vet[fim]) || (vet[meio] <= vet[inicio] && vet[meio] >= vet[fim])) {
    	*qtd_comparacoes += 4;
        return (vet[meio]); 
    } else {
        return (vet[fim]); 
    }
}


unsigned long long int QuickSort(int *vet, int fim, int inicio, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	int pivot = mediana_de_tres(vet, fim, inicio, &contador_comparacoes);

	int i = inicio;
	int j = fim;


	do {
		contador_comparacoes++; 
		while(vet[j] > pivot) {
		 contador_comparacoes++;
		 j--;
		}

		contador_comparacoes++; 
		while(vet[i] < pivot) {
			i++;
			contador_comparacoes++;
		}

		if(i <= j) {
			int aux = vet[i];
			contador_trocas++;
			vet[i] = vet[j];
			contador_trocas++;
			vet[j] = aux;
			j--;
			i++;
		}

	
	}while(i < j);


    
	if(j > inicio) {
		int a = QuickSort(vet, j, inicio, valor_retorno);
		contador_comparacoes += a;
		contador_trocas += a;
	}

	if(i < fim) {
		int a = QuickSort(vet, fim, i, valor_retorno);
		contador_comparacoes += a;
		contador_trocas += a;
	}
	

	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);
}



unsigned long long int rearranjar_heap(int *vet, int pai, int tamanho_da_heap, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	int filho_esquerdo, filho_direito;

	filho_esquerdo = 2*pai + 1;
	filho_direito = 2*pai + 2;

	int maior = pai;
	if(filho_esquerdo < tamanho_da_heap) {
		contador_comparacoes++;
		if(vet[filho_esquerdo] > vet[pai])
			maior = filho_esquerdo;
	}

	if(filho_direito < tamanho_da_heap) {
		contador_comparacoes++;		
		if(vet[filho_direito] > vet[maior])
			maior = filho_direito;
	}

	if(maior != pai) {
		int aux = vet[maior];
		contador_trocas++;
		vet[maior] = vet[pai];
		contador_trocas++;
		vet[pai] = aux;
		int a = rearranjar_heap(vet, maior, tamanho_da_heap, valor_retorno);
		contador_trocas += a;
		contador_comparacoes += a; 
	} 

	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);
}


unsigned long long int construir_heap(int *vet, int tamanho, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	for(int i = tamanho/2 - 1; i >= 0; i--) {
		int a = rearranjar_heap(vet, i, tamanho, valor_retorno);
		contador_comparacoes += a;
		contador_trocas += a;
	}

	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);
}


unsigned long long int HeapSort(int *vet, int tamanho, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	int a = construir_heap(vet, tamanho, valor_retorno);
	contador_comparacoes += a;
	contador_trocas += a;
	int tamanho_da_heap = tamanho;
	for(int i = tamanho - 1; i > 0; i--) {
		int aux = vet[0];
		contador_trocas++;
		vet[0] = vet[i];
		contador_trocas++;
		vet[i] = aux;
		tamanho_da_heap--;
		int b = rearranjar_heap(vet, 0, tamanho_da_heap, valor_retorno);
		contador_comparacoes += b;
		contador_trocas += b;
	}

	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);
}



unsigned long long int intercala(int *vet, int fim, int meio, int inicio, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	int tamanho1 = meio - inicio + 1;
	int tamanho2 = fim - meio;


	int *vet1 = (int *) malloc((tamanho1 + 1)*sizeof(int));
	for(int i = 0; i < tamanho1; i++)
		vet1[i] = vet[inicio + i];

	vet1[tamanho1] = INT_MAX;


	int *vet2 = (int *) malloc((tamanho2 + 1)*sizeof(int));
	for(int i = 0; i < tamanho2; i++)
		vet2[i] = vet[meio + 1 + i];

	vet2[tamanho2] = INT_MAX;

	
	int i = 0, j = 0;
	for(int k = inicio; k <= fim; k++) {
		contador_comparacoes++;
		if(vet1[i] < vet2[j]) {
			vet[k] = vet1[i];
			i++;
			contador_trocas++;
		}

		else {
			vet[k] = vet2[j];
			j++;
			contador_trocas++;
		}
	}

	free(vet1); free(vet2);

	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);
}


unsigned long long int MergeSort(int *vet, int fim, int inicio, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	if(fim > inicio) {
		int meio = (fim + inicio)/2;
		unsigned long long int a = MergeSort(vet, fim, meio + 1, valor_retorno);
		unsigned long long int b = MergeSort(vet, meio, inicio, valor_retorno);
		unsigned long long int c = intercala(vet, fim, meio, inicio, valor_retorno);

		contador_trocas += a; contador_trocas += b; contador_trocas += c;
		contador_comparacoes += a; contador_comparacoes += b; contador_comparacoes += c;
	}
	
	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);
}


typedef struct no_ no;

struct no_ {
	int dado;
	no*proximo;
};


typedef struct fila_ {
	no *inicio;
	no *fim;
	int tamanho;
}fila;


fila *fila_criar(void) {
	fila *Fila = (fila *) malloc(sizeof(fila));

	if(Fila != NULL) {
		Fila->inicio = NULL;
		Fila->fim = NULL;
		Fila->tamanho = 0;
	}
	return(Fila);
}

void fila_inserir(fila *Fila, int dado) {
	no *No = (no *) malloc(sizeof(no));
	No->dado = dado;
	No->proximo = NULL;

	if(Fila->inicio == NULL) 
		Fila->inicio = No;
	else
		Fila->fim->proximo = No;

	Fila->fim = No;
	Fila->tamanho++;
}


int fila_remover(fila *Fila) {
	if(Fila->inicio == NULL)
		return(-1);

	no *No = Fila->inicio;
	int dado = Fila->inicio->dado;
	Fila->inicio = Fila->inicio->proximo;

	No->proximo = NULL;
	Fila->tamanho--;
	free(No);
	return(dado);
}


void fila_esvaziar(fila *Fila, int *vet, int tamanho) {
	int contador = 0;
	while(Fila->inicio != NULL && contador < tamanho) {
		vet[contador] = fila_remover(Fila);
		contador++;
	}
}


void fila_apagar(fila *Fila) {
	while(Fila->inicio != NULL) {
		fila_remover(Fila);
	}

	free(Fila);
}



unsigned long long int RadixSort(int *vet, int tamanho, int quantidade_digitos, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	fila **vetor = (fila **) malloc(10*sizeof(fila *));
	for(int i = 0; i < 10; i++) 
		vetor[i] = fila_criar();

	
	for(int i = 0; i  < quantidade_digitos; i++) {
		for(int j = 0; j < tamanho; j++) {
			if(vet[i] < pow(10,i))
				fila_inserir(vetor[0], vet[j]);
			else 
				fila_inserir(vetor[(vet[j] / (int)pow(10, i)) % 10], vet[j]);
		}

		int contador = 0;	
		for(int i = 0; i  < 10; i++) {
			while(vetor[i]->inicio != NULL) {
				contador_trocas++;
				vet[contador] = fila_remover(vetor[i]);
				contador++;
			}

		}

	}
	
	for(int i = 0; i < 10; i++)
		fila_apagar(vetor[i]);

	free(vetor);
	
	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);
}


unsigned long long int Contagem_dos_menores(int *vet, int tamanho, int valor_retorno) {
	unsigned long long int contador_trocas = 0, contador_comparacoes = 0;
	int *auxiliar = (int *) calloc(tamanho, sizeof(int));
	int *final = (int *) malloc(tamanho*sizeof(int));


	for(int i = 1; i < tamanho; i++) {
		for(int j = i - 1; j >= 0; j--) {
			contador_comparacoes++;
			if(vet[j] < vet[i])
				auxiliar[i]++;
			else
				auxiliar[j]++;
		}
	}

	for(int i = 0; i < tamanho; i++) {
		final[auxiliar[i]] = vet[i];
	}

	for(int i = 0; i  < tamanho; i++) {
		contador_trocas++;
		vet[i] = final[i];
	}

	free(auxiliar); free(final);
	
	if(valor_retorno == 0)
		return(contador_comparacoes);
	else if(valor_retorno == 1)
		return(contador_trocas);
	else
		return(-1);

}

