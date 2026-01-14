from math import floor
from functools import cmp_to_key


centroide = [0, 0]

def get_centroide(pontos):
    x = sum(p[0] for p in pontos)/len(pontos)
    y = sum(p[1] for p in pontos)/len(pontos)
    return x, y


def get_quadrante(p):
    if p[0] >= 0 and p[1] >= 0:
        return 1
    if p[0] <= 0 and p[1] >= 0:
        return 2
    if p[0] <= 0 and p[1] <= 0:
        return 3
    return 4


def comparadora(p1, q1):
    p = [p1[0]-centroide[0], p1[1]-centroide[1]]
    q = [q1[0]-centroide[0], q1[1]-centroide[1]]
    quadrante_p = get_quadrante(p)
    quadrante_q = get_quadrante(q)

    if quadrante_p < quadrante_q:
        return -1
    elif quadrante_p > quadrante_q:
        return 1
    
    if p[0]*q[1] - p[1]*q[0] > 0:
        return -1
    elif p[0]*q[1] - p[1]*q[0] < 0:
        return 1
    else:
        if (p[0] > q[0]) or (p[0] == q[0] and p[1] > q[1]): return 1
        else: return -1


def orientacao(a, b, c):
    res = (b[1]-a[1]) * (c[0]-b[0]) - (c[1]-b[1]) * (b[0]-a[0])
    if res == 0:
        return 0
    if res > 0:
        return 1
    return -1



def força_bruta(pedras):
    fecho = []
    for i in range(len(pedras)):
        for j in range(i + 1, len(pedras)):
            x1, y1 = pedras[i][0], pedras[i][1]
            x2, y2 = pedras[j][0], pedras[j][1]

            sinal_inicial = None
            pontos_validos = True
            for k in range(len(pedras)):
                if k == i or k == j: continue

                xk, yk = pedras[k][0], pedras[k][1]
                valor = (x2 - x1) * (yk - y1) - (y2 - y1) * (xk - x1)
                if sinal_inicial == None:
                    sinal_inicial = 0 if valor >= 0 else 1
                else:
                    sinal = 0 if valor >= 0 else 1
                    if(sinal != sinal_inicial):
                        pontos_validos = False
                        break

            if(pontos_validos):
                if pedras[i] not in fecho: fecho.append(pedras[i])
                if pedras[j] not in fecho: fecho.append(pedras[j])
    return fecho


                
def merge(pedras_esq, pedras_dir):
    l1, l2 = len(pedras_esq), len(pedras_dir)
    
    mais_dir, mais_esq = 0, 0

    #Mais à direita do esquerdo
    for i in range(len(pedras_esq)):
        if pedras_esq[i][0] > pedras_esq[mais_dir][0]: mais_dir = i

    #Mais à esquerda do direito
    for i in range(len(pedras_dir)):
        if pedras_dir[i][0] < pedras_dir[mais_esq][0]: mais_esq = i

    #Caso degenerado: apenas uma reta
    eh_linha = False

    #Tangente superior
    vertice_esq_up, vertice_dir_up = mais_dir, mais_esq
    achou = False
    while not achou:
        achou = True
        contador = 0
        while(orientacao(pedras_dir[vertice_dir_up], pedras_esq[vertice_esq_up], pedras_esq[(vertice_esq_up + 1)%l1]) >= 0):
            if(contador == l1):
                eh_linha = True
                break
                 
            vertice_esq_up = (vertice_esq_up + 1) % l1
            contador += 1
        
        if(not eh_linha):
            while(orientacao(pedras_esq[vertice_esq_up], pedras_dir[vertice_dir_up], pedras_dir[(vertice_dir_up + l2 - 1)%l2]) <= 0):
                vertice_dir_up = (vertice_dir_up - 1) % l2
                achou = False

    #Tangente inferior
    vertice_esq_down, vertice_dir_down = mais_dir, mais_esq
    achou = False
    if(not eh_linha):
        while not achou:
            achou = True
            while(orientacao(pedras_esq[vertice_esq_down], pedras_dir[vertice_dir_down], pedras_dir[(vertice_dir_down + 1)%l2]) >= 0):
                vertice_dir_down = (vertice_dir_down + 1) % l2
        
            while(orientacao(pedras_dir[vertice_dir_down], pedras_esq[vertice_esq_down], pedras_esq[(vertice_esq_down + l1 - 1)%l1]) <= 0):
                vertice_esq_down = (vertice_esq_down - 1) % l1
                achou = False

    if(eh_linha):
        return sorted(pedras_esq) + sorted(pedras_dir)
    else:
        fecho = []
        ind = vertice_esq_up
        fecho.append(pedras_esq[vertice_esq_up])
        while(ind != vertice_esq_down):
            ind = (ind + 1) % l1
            fecho.append(pedras_esq[ind])

        ind = vertice_dir_down
        fecho.append(pedras_dir[vertice_dir_down])
        while(ind != vertice_dir_up):
            ind = (ind + 1) % l2
            fecho.append(pedras_dir[ind])

        return fecho

    
def solve(pedras):
    #Casos menores do que cinco ou resolve por força bruta (>3) ou retornando o próprio polígono (<=3),
    #para evitar casos especiais em que o algoritmo não termina
    if len(pedras) <= 5:
        fecho = []
        if(len(pedras) <= 3):
            fecho = pedras
        else:
            fecho = força_bruta(pedras)
        
        global centroide
        centroide = get_centroide(fecho)
        return sorted(fecho, key=cmp_to_key(comparadora))

    
    meio = floor(len(pedras)/2)
    fecho_esq = solve(pedras[:meio])
    fecho_dir = solve(pedras[meio:])

    fecho = merge(fecho_esq, fecho_dir)
    return fecho


def print_resultado(fecho):
    x_min = float('inf')
    y_min = float('inf')
    indice = -1

    for i in range(len(fecho)):
        if(fecho[i][0] < x_min or (fecho[i][0] == x_min and fecho[i][1] < y_min)):
            x_min, y_min, indice = fecho[i][0], fecho[i][1], i

    print(f"Tamanho do colar: {len(fecho)}")
    print(f"Pedras ancestrais: ", end='')

    for i in range(len(fecho)):
        ponto = fecho[(indice + i) % len(fecho)]
        print(f"({ponto[0]:.4f},{ponto[1]:.4f})", end='')
        if i < len(fecho) - 1: print(f",", end='')

    print('\n')


def main():
    n_testes = int(input())
    for i in range(n_testes):
        n_pedras = int(input())

        pedras = []
        for _ in range(n_pedras):
            valores = input().split()
            pedras.append([float(valores[0]), float(valores[1])])

        pedras.sort()
        fecho = solve(pedras)
        
        print(f"Caso {i + 1}:")
        print_resultado(fecho)


if __name__ == '__main__':
    main()
