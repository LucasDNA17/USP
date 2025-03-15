/* Funcao que resolve o problema da Mochila 0/1 segundo o paradigma da Programacao
Dinamica.A funcao recebe como parametros um vetor de inteiros "v", que armazena os
valores de cada item; um vetor de inteiros "p", que armazena os pesos de cada item;
um inteiro "limite" que representa o peso maximo da mochila; e um inteiro "n", que
representa o número de items.*/
int programacao_dinamica(int v[], int limite, int p[], int n) {
	int tabela[n + 1][limite + 1];

	//Preenchimento da tabela que
	//armazena os resultados de cada
	// subproblema i/w
	for(int i = 0; i <= n; i++) {
		for(int w = 0; w <= limite; w++) {
			//Se nao for possivel incluir nenhum
			//item ou o peso maximo for zero,
			//o valor maximo eh zero
			if(i == 0 || w == 0)
				tabela[i][w] = 0;
			else{

			if(p[i - 1] > w)
				//Se o peso do ultimo item que pode ser incluso for
				//maior que o peso maximo, o valor maximo eh igual ao
				//valor maximo dos i - 1 itens com o mesmo limite w 
				tabela[i][w] = tabela[i - 1][w];
			else 

				//Se o item puder ser incluso, o valor maximo eh o maximo entre o valor 
				//de quando ele eh incluso e de quando ele nao o eh 
				tabela[i][w] = max(tabela[i - 1][w], tabela[i - 1][w - p[i - 1]] + v[i - 1]);
			}
		}
	}

	return(tabela[n][limite]);
	}
