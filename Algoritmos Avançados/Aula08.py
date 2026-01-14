
def pd(pecas, i, j, memo):
    if i > j: 
        return 0, i, j 
    else:
        if memo[i][j] == None:
            valor_esq = sum(pecas[i])
            valor_dir = sum(pecas[j])

            _, i_esq, j_esq = pd(pecas, i + 1, j, memo)
            _, i_dir, j_dir = pd(pecas, i, j - 1, memo)

            resultado_esq, _, _ = pd(pecas, i_esq, j_esq, memo)
            resultado_dir, _, _ = pd(pecas, i_dir, j_dir, memo)
            resultado_esq += valor_esq
            resultado_dir += valor_dir
            
            if resultado_esq >= resultado_dir:
                memo[i][j] = (resultado_esq, 0) 
                return resultado_esq, i + 1, j
            else:
                memo[i][j] = (resultado_dir, 1) 
                return resultado_dir, i, j - 1
            
        else:
            if memo[i][j][1] == 0: return memo[i][j][0], i + 1, j
            else: return memo[i][j][0], i, j - 1


    

def main():
    n_testes = int(input())

    for _ in range(n_testes):
        n_pecas = int(input())
        pecas_texto = input().split(' ')
        pecas = []

        for peca in pecas_texto:
            peca = list(peca)
            pecas.append((int(peca[1]), int(peca[3])))


        memo = [[None for _ in range(n_pecas)] for _ in range(n_pecas)]
        resultado, _, _ = pd(pecas, 0, len(pecas) - 1, memo)
    
        print(f"{resultado}")



if __name__ == '__main__': main()

