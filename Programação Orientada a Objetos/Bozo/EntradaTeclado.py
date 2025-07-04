class EntradaTeclado:
    def leString(self):
        x = input()
        return x


    def leInt(self):
        y = self.leString()
        y = y.split()
        x = []

        for i in range(len(y)):
            if(y[i].isdigit()):
                x.append(int(y[i]))
        return x

    def leFloat(self):
        x = self.leString
        x = x.split()
        for i in range(len(x)):
            x[i] = float(x[i])

        

    