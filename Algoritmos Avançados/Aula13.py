from collections import deque

def solucao(s, t, arestas):
    flow = 0

    
    while(True):
        pais = [None]*(len(arestas) + 1)
        fila = deque()
        fila.append(s)


        while fila and pais[t] is None:
            atual = fila.popleft()

            for aresta in arestas[atual]:
                no_t = aresta[1]
                capacidade = aresta[2]
                flow_aresta = aresta[3]
                if pais[no_t] is None and no_t != s and capacidade > flow_aresta:
                    pais[no_t] = aresta
                    fila.append(no_t)


        if pais[t] is not None:
            flow_encontrado = float('inf')
        
            aresta_atual = pais[t]
            while aresta_atual is not None and aresta_atual != pais[s]:
                flow_encontrado = min(flow_encontrado, aresta_atual[2] - aresta_atual[3])
                aresta_atual = pais[aresta_atual[0]]


            aresta_atual = pais[t]


            while aresta_atual is not None:
                no_s, no_t = aresta_atual[0], aresta_atual[1]
                aresta_reversa = None
                for aresta in arestas[no_t]:
                    if aresta[1] == no_s:
                        aresta_reversa = aresta
                        break

                aresta_atual[3] += flow_encontrado
                aresta_reversa[3] -= flow_encontrado
                aresta_atual = pais[no_s]

            
            flow += flow_encontrado

        else: break

    return flow




def main():
    valores = input().split(' ')
    n_computadores, n_redes = int(valores[0]), int(valores[1])
    
    redes = {i :[] for i in range(1, n_computadores + 1)}
    for _ in range(n_redes):
        valores = input().split(' ')
        c1, c2, v = int(valores[0]), int(valores[1]), int(valores[2])
        redes[c1].append([c1, c2, v, 0])
        redes[c2].append([c2, c1, -v, 0])
        

    print(solucao(1, n_computadores, redes))
    


if __name__ == '__main__': main()