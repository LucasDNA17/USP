

def solucao(pontes, n_acampamentos):
    arvores = {}
    arvores = {i + 1 : set([i + 1]) for i in range(n_acampamentos)} 
    pontes.sort(key=lambda ponte: ponte[0])

    min_custo = 0
    pontes_sol = []
    for ponte in pontes:
        custo, p1, p2 = ponte[0], ponte[1], ponte[2]
        
        if arvores[p1] != arvores[p2]:
            nova_arvore = arvores[p1].union(arvores[p2])
            for acampamento in nova_arvore:
                arvores[acampamento] = nova_arvore
            min_custo += custo

            ponte_selecionada = None
            if p2 >= p1: ponte_selecionada = (p1, p2)
            else: ponte_selecionada = (p2, p1)

            pontes_sol.append(ponte_selecionada)

    #Não é possível formar o caminho
    arvore = arvores[1]
    for i in range(1, n_acampamentos):
        if arvores[i + 1] != arvore:
            min_custo, pontes_sol = -1, None
            break

    return min_custo, pontes_sol



def main():
    n_testes = int(input())

    for i in range(n_testes):
        valores = input().split(' ')
        n_acampamentos, n_pontes = int(valores[0]), int(valores[1])
        
        pontes = []
        custos = set()
        flag = False
        for _ in range(n_pontes):
            valores = input().split(' ')
            p1, p2, custo = int(valores[0]), int(valores[1]), int(valores[2])

            if custo in custos:
                print(f"Esse nao e o caminho correto para a Cidade Perdida de Z.")
                flag = True
            
            custos.add(custo)
            pontes.append((custo, p1, p2))

        if(not flag): 
            min_custo, pontes_sol = solucao(pontes, n_acampamentos)

            if min_custo == -1:
                print(f"O vale nao pode ser completamente atravessado.")
            else:
                print(f"Custo minimo: {min_custo}")
                print(f"Pontes reconstruidas:")

                for ponte in pontes_sol:
                    print(f"{ponte[0]} - {ponte[1]}")

        print()

    return 




if __name__ == '__main__': main()