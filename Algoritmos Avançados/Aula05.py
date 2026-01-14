from math import floor

def merge(pos_iniciais, pos_finais, e, m, d):
    n_esquerda = m - e + 1
    n_direita = d - m

    esq = pos_finais[e:m + 1]
    dir = pos_finais[m + 1: d + 1]

    n_ultrapassagens = 0

    i = 0
    j = 0
    k = e
    while i < n_esquerda and j < n_direita:
        id_i, id_j = esq[i][1], dir[j][1]
        if pos_iniciais[id_i] <= pos_iniciais[id_j]:
            pos_finais[k] = esq[i]
            i += 1
        else:
            pos_finais[k] = dir[j]
            j += 1
            n_ultrapassagens += n_esquerda - i

        k += 1

    while i < n_esquerda:
        pos_finais[k] = esq[i]
        i += 1
        k += 1
    while j < n_direita:
        pos_finais[k] = dir[j]
        j += 1
        k += 1

    return n_ultrapassagens


def get_ultrapassagens(pos_iniciais, pos_finais, e, d):
    n_ultrapassagens = 0
    if e < d:
        m = floor((e + d)/2)

        n_ultrapassagens += get_ultrapassagens(pos_iniciais, pos_finais, e, m)
        n_ultrapassagens += get_ultrapassagens(pos_iniciais, pos_finais, m + 1, d)

        n_ultrapassagens += merge(pos_iniciais, pos_finais, e, m, d)

    return n_ultrapassagens


def solve(pos_iniciais, pos_finais):
    pos_finais.sort()
    return get_ultrapassagens(pos_iniciais, pos_finais, 0, len(pos_finais) - 1)


def main():
    n_trechos = int(input())
    qtds_ultrapassagens = []
    for i in range(n_trechos):
        pos_iniciais, pos_finais = [], []
        n_jogadores = int(input())

        for j in range(n_jogadores):
            valores = input().split(' ')
            pos_iniciais.append(int(valores[0]))
            pos_finais.append((int(valores[1]), j))

        qtd_ultrapassagens = solve(pos_iniciais, pos_finais)
        qtds_ultrapassagens.append((qtd_ultrapassagens, i))

    qtds_ultrapassagens.sort(reverse=True)


    for qtd_ultrapassagens, trecho in qtds_ultrapassagens:
        print(f"{trecho} {qtd_ultrapassagens}")

    
if __name__  == '__main__':
    main()


