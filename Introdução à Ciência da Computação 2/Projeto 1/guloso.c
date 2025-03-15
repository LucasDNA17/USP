/* Struct que armazena os itens. */
typedef struct {
1	int valor; //valor do item
2	int peso; //peso do item
3	double razao; //razao valor/peso do item
} elemento;


/*Funcao que implementa o algoritmo de ordenacao 
QuickSort para ordenar um vetor de itens de acordo
com a razao valor/peso */
void quick_sort(elemento v[], int inf, int sup) {
1	int meio = (inf + sup)/2;
2	double pivo = v[meio].razao;
3
4	int i = inf;
5	int j = sup;
6
7	do {
8		while(v[i].razao > pivo) i++;
9		while(v[j].razao < pivo) j--;
10
11		if(i <= j) {
12			elemento aux = v[i];
13			v[i] = v[j];
14			v[j] = aux;
15			i++;
16			j--;
17		} 
18	}while(i < j);
19	
20	if(j > inf) quick_sort(v, inf, j);
21	if(i < sup) quick_sort(v, i, sup);
22	}





/* Funcao que resolve o problema da Mochila 0/1 segundo o paradigma do Algoritmo Guloso.
A funcao recebe como parametros um vetor de inteiros "v", que armazena os valores de 
cada item; um vetor de inteiros "p", que armazena os pesos de cada item; um inteiro
"limite" que representa o peso maximo da mochila; e um inteiro "n", que representa o 
número de items.*/
int algoritmo_guloso(int v[], int limite, int p[], int n) {
1	//Criação e inicialização de um vetor que
2	//armazena cada item
3	elemento vet[n];
4	for(int i = 0; i < n; i++) {
5		vet[i].razao = (double) v[i]/p[i];
6		vet[i].valor = v[i];
7		vet[i].peso = p[i];
8	}
9
10	//Ordenação dos itens de acordo
11	//com a razão valor/peso
12	quick_sort(vet, 0, n - 1);
13
14	//escolha dos itens com melhor relacao
15	// valor/peso até que a mochila esteja
16	//cheia ou que acabem os itens 
17	int peso = 0, valor = 0;
18	for(int k = 0; k < n; k++) {
19		if(peso + vet[k].peso > limite)
20			continue;
21
22		valor += vet[k].valor;
23		peso += vet[k].peso;
24		if(peso == limite)
25			break;
26	}
27
28	return(valor);
29	}