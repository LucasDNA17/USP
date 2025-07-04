import math

class Tabuleiro:

    def __init__(self, comprimento, largura):
        self.comprimento = comprimento
        self.largura = largura
        self.tabuleiro = []
        self.pos_vazia_i = -1
        self.pos_vazia_j = -1

    def preenche_tabuleiro(self, valores):
        self.largura =  int(math.sqrt(len(valores)))
        self.comprimento =  int(math.sqrt(len(valores)))
        self.tabuleiro = [[0 for i in range(self.largura)] for x in range(self.comprimento)]
       
        for i in range(self.comprimento):
            for j in range(self.largura):
                numero = valores[self.largura*i + j]
                self.tabuleiro[i][j] = numero
                if(numero == 0):
                    self.pos_vazia_i = i
                    self.pos_vazia_j = j

    def swap(self, i1, j1, i2, j2):
        tmp = self.tabuleiro[i1][j1]
        self.tabuleiro[i1][j1] = self.tabuleiro[i2][j2]
        self.tabuleiro[i2][j2] = tmp

    
    def up(self):
        if(self.pos_vazia_i < self.comprimento - 1 and self.pos_vazia_i != -1):
            self.swap(self.pos_vazia_i + 1, self.pos_vazia_j, self.pos_vazia_i, self.pos_vazia_j)
            self.pos_vazia_i += 1

    def down(self):
        if(self.pos_vazia_i > 0):
            self.swap(self.pos_vazia_i - 1, self.pos_vazia_j, self.pos_vazia_i, self.pos_vazia_j)
            self.pos_vazia_i -= 1

    def left(self):
        if(self.pos_vazia_j < self.largura - 1  and  self.pos_vazia_j != -1):
            self.swap(self.pos_vazia_i, self.pos_vazia_j + 1, self.pos_vazia_i, self.pos_vazia_j)
            self.pos_vazia_j += 1

    def right(self):
        if(self.pos_vazia_j > 0):
            self.swap(self.pos_vazia_i, self.pos_vazia_j - 1, self.pos_vazia_i, self.pos_vazia_j)
            self.pos_vazia_j -= 1


    def movements(self):
        movements = input()
        self.printa_tabuleiro()
        for i in range(len(movements)):
            match movements[i]:
                case 'u':
                    self.up()
                case 'd':
                    self.down()
                case 'l':
                    self.left()
                case 'r':
                    self.right()

            self.printa_tabuleiro()


    def print_line(self, tamanho):
        for i in range(tamanho):
            print("+------", end = "")

        print("+")

    def printa_tabuleiro(self):
        self.print_line(self.largura)

        for i in range(self.comprimento):
            print("|", end = "")
            for j in range(self.largura):
                if(self.tabuleiro[i][j] >= 10):
                    print(" ", self.tabuleiro[i][j], end = "")
                    print("  |", end = "")
                else:
                    print("   ", end = "")
                    if(self.tabuleiro[i][j] != 0):
                        print(self.tabuleiro[i][j], end = "")
                    else:
                        print(" ", end = "")          
                    print("  |", end = "")

            print()
            self.print_line(self.largura)

        print()


    def EhSolucao(self):
        for i in range(self.comprimento):
            for j in range(self.largura):
                if(self.tabuleiro[i][j] != self.largura*i + j):
                    return False 

        return True




def leitura():
    entrada = input()
    inteiros = entrada.split()
    for i in range(len(inteiros)):
        inteiros[i] = int(inteiros[i])
    return inteiros


def main():
    valores = leitura()
    tabuleiro = Tabuleiro(0, 0) 

    tabuleiro.preenche_tabuleiro(valores)
    tabuleiro.movements()
    if(tabuleiro.EhSolucao()):
        print("Posicao final: True")
    else:
        print("Posicao final: False")


main()