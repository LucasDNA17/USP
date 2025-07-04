import random

class Dado:
    def __init__(self, n, seed):
        if(n == None):
            self.lados = 6
        else:
            self.lados = n
        
        if(seed == None):
            self.r = random.Random()
        else:
            self.r = random.Random(seed)

        self.atual = -1
        self.s010 = "|  *  |\n"
        self.s100 = "|*    |\n"
        self.s001 = "|    *|\n"
        self.s000 = "|     |\n"
        self.s101 = "|*   *|\n"
        self.s111 = "|* * *|\n"
        self.rolar()


    def rolar(self):
        self.atual = self.r.randint(1, self.lados)
        return self.atual

    def getLado(self):
        return self.atual

    
    def toString(self):
        if (self.lados != 6):
            return "Não há representação para esse dados"
        s = "+-----+\n"
        match(self.getLado()):
            case 1:
                s += (self.s000 + self.s010 + self.s000)
            case 2:
                s += (self.s100 + self.s000 + self.s001)
            case 3:
                s += (self.s100 + self.s010 + self.s001)
            case 4:
                s += (self.s101 + self.s000 + self.s101)
            case 5:
                s += (self.s101 + self.s010 + self.s101)
            case 6:
                s += (self.s111 + self.s000 + self.s111)

        s += ("+-----+\n")
        return s


    

    

    

