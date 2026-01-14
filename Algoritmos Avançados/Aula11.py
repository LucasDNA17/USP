def df(atomo_atual, atomos, ligacoes):
    vizinhos = ligacoes[atomo_atual]

    for vizinho in vizinhos:
        if atomos[vizinho]: continue

        atomos[vizinho] = True
        df(vizinho, atomos, ligacoes)

    return


def solucao(atomos, ligacoes):
    n_moleculas = 0

    for i in range(len(atomos)):
        #Átomo já visitado
        if atomos[i]: continue

        n_moleculas += 1
        atomos[i] = True

        df(i, atomos, ligacoes)

    return n_moleculas

        
def main():
    n_testes = int(input())

    for _ in range(n_testes):
        valores = input().split(' ')
        n_atomos, n_ligacoes = int(valores[0]), int(valores[1])

        atomos = [False]*n_atomos
        ligacoes = [[] for i in range(n_atomos)]

        for _ in range(n_ligacoes):
            vizinhos = input().split(' ')
            atomo1, atomo2 = int(vizinhos[0]), int(vizinhos[1])
            ligacoes[atomo1 - 1].append(atomo2 - 1)
            ligacoes[atomo2 - 1].append(atomo1 - 1)

        sol = solucao(atomos, ligacoes)
        print(f"{sol}")




if __name__ == '__main__': main()
