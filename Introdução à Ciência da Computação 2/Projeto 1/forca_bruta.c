/* Função que resolve o problema da Mochila 0/1 segundo o paradigma da Força Bruta.
A função recebe como parâmetros um vetor de inteiros "v", que armazena os valores de 
cada item; um vetor de inteiros "p", que armazena os pesos de cada item; um inteiro
"limite" que representa o peso máximo da mochila; e um inteiro "n", que representa o 
número de items.*/

int forca_bruta(int v[], int limite, int p[], int n) {
	if(n == 0 || limite == 0)	//Caso base: n = 0 ou limite = 0. Nesse caso,
		return(0);				//é impossível incluir qualquer item


	if(p[n - 1] > limite)							//Se o n-ésimo item tiver peso maior
		return(forca_bruta(v, limite, p, n - 1));	//do que o limite, não o inclua


	int res = max(v[n - 1] + forca_bruta(v, limite - p[n - 1], p, n - 1), 	//Retorna o maior valor dentre dois casos:
							 forca_bruta(v, limite, p, n - 1));				//n-ésimo termo é incluso ou não
	return(res);
}