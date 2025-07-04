import Dado
import random

class RolarDados:
        def __init__(self,n, seed):
                self.r  = random.Random(seed)
                self.dados = []
                for i in range(n):
                        if(seed == 0):
                                dado = Dado.Dado()
                        else:
                                dado = Dado.Dado(6, self.r.randint(1, 10000))

                        self.dados.append(dado)

        def rolar(self, lista = [0]):
                if (lista != [0] and lista != [] and isinstance(lista[0], bool)):
                        valor_dados = []
                        for i in range(len(self.dados)):
                                if(i >= len(lista)):
                                        break

                                if(lista[i]):
                                        self.dados[i].rolar()

                                valor_dados.append(self.dados[i].getLado())

                        return valor_dados
                
                elif(lista != [0] and (lista == [] or isinstance(lista[0], int))):
                        lista_booleanos = [False]*len(self.dados)
                        for i in range(len(lista)):
                                indice = lista[i] - 1
                                if(indice >= 0 and indice < len(self.dados)):
                                        lista_booleanos[indice] = True

                        return self.rolar(lista_booleanos)

                else:
                        valor_dados = []
                        for i in range(len(self.dados)):
                                valor_dados.append(self.dados[i].rolar())
                
                        return valor_dados  


        def toString(self):
                s = ""
                for i in range(6):
                        base = i*8
                        for i in range(len(self.dados)):
                                p = self.dados[i].toString()
                                s += p[base:base + 7:1]
                                s += "    "
                        s += "\n"

                return s




                
                        
