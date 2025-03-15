#ifndef SORTING_H
	#define SORTING_H


	#include <stdio.h>
	#include <stdlib.h>
	#include <limits.h>
	#include <time.h>
	#include <stdbool.h>

	
	unsigned long long int BubbleSort(int *vet, int tamanho, int valor_retorno);
	unsigned long long int SelectionSort(int *vet, int tamanho, int valor_retorno);
	unsigned long long int InsertionSort(int *vet, int tamanho, int valor_retorno);
	unsigned long long int ShellSort(int *vet, int tamanho, int *incrementos, int quantidade_incrementos, int valor_retorno);
	unsigned long long int QuickSort(int *vet, int fim, int inicio, int valor_retorno);
	unsigned long long int HeapSort(int *vet, int tamanho, int valor_retorno);
	unsigned long long int MergeSort(int *vet, int fim, int inicio, int valor_retorno);
	unsigned long long int Contagem_dos_menores(int *vet, int tamanho, int valor_retorno);
	unsigned long long int RadixSort(int *vet, int tamanho, int quantidade_digitos, int valor_retorno);


#endif