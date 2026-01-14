
###### Força Bruta ######

def casos_base(reliquias):
    #print(f"Caso base: {reliquias}")
    n_reliquias = len(reliquias)
    match n_reliquias:
        case 0: return 0
        case 1: return reliquias[0]
        case 2: return reliquias[0] + reliquias[1] - 1

# def solucao(reliquias):
#     n_reliquias = len(reliquias)
#     if n_reliquias < 3: return casos_base(reliquias)

#     if reliquias[0] <= 0:
#         copia = reliquias[1:]
#         copia[0] -= 1
#         return solucao(copia)
        

#     resultado = float('inf')
#     for i in range(0, len(reliquias) - 1):
#         #print(f"Reliquias: {reliquias}")
#         copia_esq = reliquias[:i]
#         #print(f"copia_esq: {copia_esq}")
#         copia_dir = reliquias[i + 1:]
#         copia_dir[0] = max(copia_dir[0] - (i + 1), 0)
#         #print(f"copia_dir: {copia_dir}")

#         resultado_parcial = reliquias[i] + solucao(copia_esq) + solucao(copia_dir)

#         if resultado_parcial < resultado: resultado = resultado_parcial

#     return resultado



def solucao(reliquias, i, j, M):
    #print(f"{j}, {i}")
    if M[i][j] == -1:
        if abs(i - j) < 2: M[i][j] = casos_base(reliquias[i:j + 1])
        else:

            melhor_solucao = float('inf')
            for k in range(i, j):
                custo, M = solucao(reliquias, i, k - 1, M)

                custo += reliquias[k]
        

                pos_inicial = k + 1
                if reliquias[pos_inicial] <= k + 1 - i:
                    if pos_inicial != j:
                        while(pos_inicial + 1 < j + 1 and reliquias[pos_inicial] == 1): pos_inicial += 1
                        
                        custo_dir, M = solucao(reliquias, pos_inicial, j, M)
                        custo += max(custo_dir - 1, 0)
                else:
                    custo_dir, M = solucao(reliquias, pos_inicial, j, M)
                    
                    custo += custo_dir - (k + 1 - i)



                desconto = 0
                if k < j: desconto = min(reliquias[k + 1], k)
                custo_dir, M = solucao(reliquias, k + 1, j, M)
                custo += custo_dir - desconto

                

                if custo < melhor_solucao: melhor_solucao = custo



            M[i][j] = melhor_solucao
            print(f"{i}, {j}")

    
    return M[i][j], M



def melhor_solucao(reliquias, M):
    for j in range(len(reliquias)):
        for i in range(j + 1):
            result, M = solucao(reliquias, i, j, M)

    return M[0][len(reliquias) - 1]
            









def main():
    n_reliquias = int(input())
    reliquias = []

    entrada = input().split(' ')
    if '' in entrada: entrada.remove('')
    estabilidades = map(int, entrada)

    for estabilidade in estabilidades:
        reliquias.append(estabilidade)

    M = [[-1 for i in range(n_reliquias)] for j in range(n_reliquias)]
    #print(M)
    #resultado, M = solucao(reliquias, 0, len(reliquias) - 1, M)
    resultado = melhor_solucao(reliquias, M)
    print(f"{resultado}") 


if __name__ == '__main__': main()   






