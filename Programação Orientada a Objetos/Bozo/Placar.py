class Placar:
    def __init__(self):
        self.POSICOES = 10
        self.placar = [0]*self.POSICOES
        self.taken = [False]*self.POSICOES


    def add(self, posicao, dados):
        if(self.taken[posicao - 1]):
            raise ValueError("Posição ocupada")
        k = 0
        match posicao:
            case 1: 
                k = self.conta(1, dados)
            case 2:
                k = 2 * self.conta(2, dados)
            case 3: 
                k = 3 * self.conta(3, dados)
            case 4: 
                k = 4 * self.conta(4, dados)
            case 5: 
                k = 5 * self.conta(5, dados)
            case 6: 
                k = 6 * self.conta(6, dados)
            case 7: 
                if self.checkFull(dados):
                    k = 15
            case 8:
                if self.checkSeqMaior(dados):
                    k = 20
            case 9: 
                if self.checkQuadra(dados):
                    k = 30
            case 10: 
                if self.checkQuina(dados):
                    k = 40
            case _:
                raise ValueError("Valor da posição ilegal")
        
        self.placar[posicao-1] = k
        self.taken[posicao-1] = True
                

    def getScore(self):
        t = 0
        for i in range(self.POSICOES):
            if(self.taken[i]):
                t += self.placar[i]

        return t
    
    def conta(self, n, vet):
        cont = 0
        for i in range(len(vet)):
            if(vet[i] == n):
                cont += 1

        return cont

    def checkFull(self, dados):
        v = dados.copy()
        v.sort()
        return(v[0] == v[1] and v[1] == v[2] and v[3] == v[4]) or (v[0] == v[1] and v[2] == v[3] and v[3] == v[4])


    def checkQuadra(self, dados):
        v = dados.copy()
        v.sort()
        return (v[0] == v[1] and v[1] == v[2] and v[2] == v[3]) or (v[1] == v[2] and v[2] == v[3] and v[3] == v[4])

    def checkQuina(self, dados):
        v = dados.copy()
        return (v[0] == v[1] and v[1] == v[2] and v[2] == v[3] and v[3] == v[4])


    def checkSeqMaior(self, dados):
        v = dados.copy()
        v.sort()
        return (v[0] == v[1]-1 and v[1] == v[2]-1 and v[2] == v[3]-1 and v[3] == v[4]-1)


    def toString(self):
        num = ""
        s = ""
        for i in range(3):
            num = f" {self.placar[i]:<2}" if self.taken[i] else f"({i + 1})" 
            s += num + "    |   "
            num = f" {self.placar[i + 6]:<2}" if self.taken[i + 6] else f"({i + 7})"
            s += num + "    |  "
            num = f" {self.placar[i + 3]:<2}" if self.taken[i + 3] else f"({i + 4})"
            s+= num + "\n-------|----------|-------\n"


        num = f" {self.placar[9]:<4}" if self.taken[9] else f"({10}) "
        s += "       |   " + num + "  |"
        s += "\n       +----------+\n"
        return s


