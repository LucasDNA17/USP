

def escolher_alugueis(alugueis_carros):
    for i in range(len(alugueis_carros)):
        alugueis_carros[i].sort(key=lambda tuple: (tuple[2], tuple[1]))
        alugueis_escolhidos = []
        fim_intervalo = -1

        for j in range(len(alugueis_carros[i])):
            if(alugueis_carros[i][j][1] >= fim_intervalo):
                alugueis_escolhidos.append(alugueis_carros[i][j])
                fim_intervalo = alugueis_carros[i][j][2]

        alugueis_escolhidos.sort(key=lambda tuple: tuple[1])
        alugueis_carros[i] = alugueis_escolhidos


def imprimir_alugueis(alugueis_carros):
    for i in range(len(alugueis_carros)):
        print(f"{i + 1}: {len(alugueis_carros[i])}", end='')
        if(len(alugueis_carros[i]) > 0):
            print(f" =", end='')
        for j in range(len(alugueis_carros[i])):
            print(f" {alugueis_carros[i][j][0]}", end='')

            if j < len(alugueis_carros[i]) - 1:
                print(f",", end='')

        if i < len(alugueis_carros) - 1:
            print(f" | ", end='')


    print()

    
def main():
    qtd_testes = int(input())

    for _ in range(qtd_testes):
        qtd_carros = int(input())
        qtd_solicitacoes = int(input())

        alugueis_carros = [[] for _ in range (qtd_carros)]
        for _ in range(qtd_solicitacoes):
            valores = input().split(' ')
            Idcliente, inicio, fim, Idcarro = int(valores[0]), int(valores[1].replace(':', '')), int(valores[2].replace(':', '')), int(valores[3])
            (alugueis_carros[Idcarro - 1]).append((Idcliente, inicio, fim))

        escolher_alugueis(alugueis_carros)
        imprimir_alugueis(alugueis_carros)



if __name__ == "__main__":
    main()

    

