

def bf(s, n_locais, pistas, ash_joga):
    if(not ash_joga):
        pistas_copy = pistas.copy()
        for vizinho in pistas[s]:
            vizinhos_copy = pistas[s].copy()
            vizinhos_copy.remove(vizinho)
            pistas_copy[s] = vizinhos_copy
            if not bf(vizinho, n_locais, pistas_copy, True): return False
        
        return True

    else:
        pistas_copy = pistas.copy()
        for vizinho in pistas[s]:
            vizinhos_copy = pistas[s].copy()
            vizinhos_copy.remove(vizinho)
            pistas_copy[s] = vizinhos_copy
            if bf(vizinho, n_locais, pistas_copy, False): return True

        return False


def main():
    n_testes = int(input())
    
    for _ in range(n_testes):
        valores = list(map(int, input().split(' ')))
        n_locais, n_pistas, s = valores[0], valores[1], valores[2]

        pistas = [[] for k in range(n_locais)]

        for _ in range(n_pistas):
            valores = list(map(int, input().split(' ')))
            pistas[valores[0]].append(valores[1])

        result = bf(s, n_locais, pistas, True)

        if(result): print(f"Ash")
        else: print("Noir")
        


if __name__ == '__main__': main()