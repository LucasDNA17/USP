
import RolarDados
import EntradaTeclado
import Placar

def main():
    NRODADAS = 10
    entrada = EntradaTeclado.EntradaTeclado()
    print("Digite a semente (zero para aleatório): ", end="")
    seed = entrada.leInt()
    rd = RolarDados.RolarDados(5, seed[0])
    pl = Placar.Placar()
    print(pl.toString())

    for i in range(NRODADAS):
        print("****** Rodada",(i+1))
        print("Pressione ENTER para lançar os dados")
        entrada.leString()
        rd.rolar()
        print("1          2          3          4          5")
        print(rd.toString(), end="")

        print("Digite os números dos dados que quiser TROCAR. Separados por espaços.")
        muda = entrada.leInt()
        rd.rolar(muda)
        print("1          2          3          4          5")
        print(rd.toString(), end = "")


        print("Digite os números dos dados que quiser TROCAR. Separados por espaços.")
        muda = entrada.leInt()
        values = rd.rolar(muda)
        print("1          2          3          4          5")
        print(rd.toString(), end="")



        print("\n\n")
        print(pl.toString())
        pos = 0
        while(pos <= 0):
            try:
                print("Escolha a posição que quer ocupar com essa jogada ===> ", end="")
                pos = entrada.leInt()[0]
                if(pos > NRODADAS or pos <= 0):
                    pos = 0
                pl.add(pos, values)
            
            except:
                pos = 0

            if(pos == 0):
                print("Valor inválido. Posição ocupada ou inexistente.")


        print("\n\n")
        print(pl.toString())

    print("***********************************")
    print("***")
    print("*** Seu escore final foi: " + str(pl.getScore()))
    print("***")
    print("***********************************")  

    
main()