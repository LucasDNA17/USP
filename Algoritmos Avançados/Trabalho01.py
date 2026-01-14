#Lucas Dúckur Nunes Andreolli ---- N°USP: 15471518


####  ESTRUTURA DE DADOS TRIE  #### 

#Cada nó possui um indicativo se é palavra ou não e,
#se for, armazena a palavra
#Os nós filhos são acessados por meio de um dicionário que
#possui como chaves os códigos asci dos caracteres
class TrieNode:

    def __init__(self):
        self.filhos = {}
        for i in range(26):
            self.filhos[i] = None

        self.ehPalavra = False
        self.palavra = []

class Trie:

    def __init__(self):
        self.raiz = TrieNode()
        self.no_atual = self.raiz

    def adicionar_palavra(self, palavra):
        no_atual = self.raiz

        #Percorre os caracteres da string, criando novos nós
        #caso nenhum dos já existentes represente o caracter atual
        for caracter in palavra:
            codigo_ascii = ord(caracter) - ord('A')
            if no_atual.filhos[codigo_ascii] == None:
                novo_no = TrieNode()
                no_atual.filhos[codigo_ascii] = novo_no
            
            no_atual = no_atual.filhos[codigo_ascii]

        #Último nó armazena que é palavra a a palavra também
        no_atual.ehPalavra = True
        no_atual.palavra = palavra
        
    #Avança o no_atual da árvore de acordo com o caracter de entrada
    def percorrer_arvore(self, caracter):
        codigo_ascii = ord(caracter) - ord('A')

        #Prefixo inválido, volta à raíz da árvore e retorna falso
        if self.no_atual.filhos[codigo_ascii] == None:
            self.no_atual = self.raiz
            return False
        else:
            self.no_atual = self.no_atual.filhos[codigo_ascii]

        if(self.no_atual.ehPalavra):
            #Se for palavra, retorne-a
            return self.no_atual.palavra
        else:
            #Se não for, retorne que o prefixo é verdadeiro
            return True



####  CLASSE CAÇA-PALAVRAS  #### 


class caça_palavras():

    def __init__(self):
        self.dicionario = None
        self.grid = None
        self.n_colunas = -1
        self.n_linhas = -1

    #Cria o grid
    def set_grid(self, linhas, colunas):
        self.grid = []
        self.n_colunas = colunas
        self.n_linhas = linhas
        for i in range(linhas):
            linha_letras = input()
            coluna = []

            if(len(linha_letras) != colunas):
                return []
            for j in range(colunas):
                coluna.append(linha_letras[j])

            self.grid.append(coluna)

    #Cria o dicionário
    def set_dictionary(self, qtd_palavras):
        self.dicionario = Trie()
        for i in range(qtd_palavras):
            palavra = input()
            self.dicionario.adicionar_palavra(palavra)


    #Verifica se uma posição do grid é válida
    def __posicao_eh_valida(self, posicao):
        return posicao[0] < self.n_linhas and posicao[0] >= 0 and posicao[1] < self.n_colunas and posicao[1] >= 0
    
    #Retorna o no_atual da árvore à raíz
    def __reset_dicionario(self):
        self.dicionario.no_atual = self.dicionario.raiz

    #Encontra todas as soluções cujo início está em "posição_atual"
    #A função realiza a busca nas oito direções, retornando sempre
    #à posição original quando a busca em uma direção se encerra
    def __solucao_parcial(self, posicao_atual):
        direcoes = [(1, 0), (0, 1), (1, 1), (-1, 0), (0, -1), (-1, -1), (1, -1), (-1, 1)]
        palavras_encontradas = []
        for direcao in direcoes:
            posicao = posicao_atual
            while(self.__posicao_eh_valida(posicao)):
                i,j = posicao[0], posicao[1]

                buscar_caça_palavras = self.dicionario.percorrer_arvore(self.grid[i][j])
            
                #Palavra encontrada
                if(buscar_caça_palavras and buscar_caça_palavras != True):
                    palavras_encontradas.append(buscar_caça_palavras)
                
                #Prefixo não é válido, encerra a busca nessa direção
                if(not buscar_caça_palavras):
                    break
                
                #Palavra encontrada ou prefixo ainda é válido, continua a busca nessa direção
                posicao = (posicao[0] + direcao[0], posicao[1] + direcao[1])
            
            #Precisa reiniciar a busca na árvore sempre que a busca em uma direção se encerra
            self.__reset_dicionario()

        return palavras_encontradas

    #Percorre o grid todo, pegando as soluções que se iniciam em cada posição do grid
    def solucao(self):
        palavras_encontradas = []
        for i in range(self.n_linhas):
            for j in range(self.n_colunas):
                palavras_encontradas_posicao = self.__solucao_parcial((i, j))
                for palavra in palavras_encontradas_posicao:
                    if palavra not in palavras_encontradas:
                        palavras_encontradas.append(palavra)

        return palavras_encontradas




def main():
    
    linhas,colunas = map(int, input().split())
    
    #Lê o grid
    jogo = caça_palavras()
    jogo.set_grid(linhas, colunas)
    
    #Lê o dicionário
    qtd_palavras = int(input())
    jogo.set_dictionary(qtd_palavras)
    
    #Soluciona o caça-palavras
    palavras_encontradas = jogo.solucao()
    palavras_encontradas.sort()
    
    #Imprime as palavras encontradas
    print(f"{len(palavras_encontradas)}")
    for palavra in palavras_encontradas:
        print(palavra)

    
if __name__ == "__main__":
    main()
