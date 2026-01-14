from math import dist, floor

#### PARTE 1 ####

#Na parte 1, é implementado o algoritmo de Kruskal (algoritmo guloso)
#para se encontrar a árvore geradora mínima. Para se atingir a complexidade
#desejada, é necessário utilizar a estrutura de dados "Disjoint Set" (união-busca)
#para realizar a união das árvores formadas durante a execução do algoritmo
#e verificar se uma dada aresta gera ciclos se for incluída, isso em tempo
#O(log(V)).
#A complexidade final é, assim, O(E*log(E)). 


#Estrutura de dados união-busca
class disjoint_set:

    #No ínicio, cada ponto é o representante de seu conjunto, que possui
    #apenas um elemento
    def __init__(self, n_pontos):
        self.pai = list(range(n_pontos))
        self.descendentes = [1]*n_pontos

    #Busca o representante do conjunto ao qual um elemento pertence.
    #Se o elemento não for o representante de seu conjunto, basta apenas
    #chamar a busca para o representante do conjunto do elemento.
    def busca(self, idx):
        if self.pai[idx] != idx:
            self.pai[idx] = self.busca(self.pai[idx])
            return self.pai[idx]
        else:
            return idx

    #Une dois conjuntos, transformando uma árvore (a com menos descendentes) em
    #descendente da outra.
    def uniao(self, idx1, idx2):
        pai_idx1 = self.busca(idx1)
        pai_idx2 = self.busca(idx2)

        #Se os representantes forem os mesmos, os conjuntos (árvores) são os mesmos.
        if pai_idx1 == pai_idx2: return

        #Garante que a quantidade de descendentes da raíz 1 é maior do que a quantidade
        #de descendentes da raíz 2
        if self.descendentes[pai_idx1] < self.descendentes[pai_idx2]:
            temp = pai_idx1
            pai_idx1 = pai_idx2
            pai_idx2 = temp
            
        #Raíz 2 torna-se descendente da raíz 1
        self.pai[pai_idx2] = pai_idx1
        #Raíz 1 ganha todos os descendentes da raíz 2
        self.descendentes[pai_idx1] += self.descendentes[pai_idx2]
        
#Função que encontra a melhor conexão de um conjunto de pontos
#de modo a minimizar a distância total. O algoritmo de Kruskal
#é utilizado.
#O algoritmo ordena as possíveis conexões em ordem crescente de
#distância e, em seguida, percorre-as selecionando a conexão sempre que
#ela não gerar ciclos. A lógica de verificação de ciclos é feita pela
#estrutura de dados união-busca.
def encontra_melhor_caminho(pontos, peso_max):
    n_pontos = len(pontos)
    
    #Calcula as possíveis conexões considerando uma distância máxima
    #a ser respeitada. Processo com complexidade O(E).
    distancias = []
    for i in range(n_pontos):
        for j in range(i+ 1, n_pontos):
            distancia = dist(pontos[i], pontos[j])
            if distancia <= peso_max: distancias.append([distancia, i, j])

    #Ordena as conexões em ordem crescente de distância.
    distancias.sort(key=lambda aresta: aresta[0])
    #Cria a estrutura de dados união-busca
    disjoint_set_vertices = disjoint_set(len(pontos))

    #Percorre as arestas, adicionando-as sempre que não gerarem ciclos.
    arestas_selecionadas = []
    contador = 0
    for aresta in distancias:
        p1, p2 = aresta[1], aresta[2]
        if disjoint_set_vertices.busca(p1) != disjoint_set_vertices.busca(p2):
            #Realiza a união (conexão) dos conjuntos correspondentes
            disjoint_set_vertices.uniao(p1, p2)
            #Adiciona a "aresta"
            arestas_selecionadas.append(aresta)
            contador += 1

        #Se já houver V - 1 "arestas", a árvore geradora mínima já está pronta
        if contador == n_pontos - 1: break

    return arestas_selecionadas


#Função que encontra os túneis que unem os sistemas mais importantes,
#minimizando a distância total.
def parte1(sistemas, n_importantes, tensao_max):
    #Coordenadas dos sistemas são transformados em uma lista.
    lista_sistemas = list(sistemas.keys())
    #Encontra os melhores túneis
    tuneis = encontra_melhor_caminho(lista_sistemas[:n_importantes], tensao_max)
    #Imprime cada túnel com seu custo
    for tunel in tuneis:
        sistema1, sistema2 = lista_sistemas[tunel[1]], lista_sistemas[tunel[2]]
        print(f"{sistemas[sistema1]}, {sistemas[sistema2]}, {tunel[0]:.2f}")


#### PARTE 2 ####

#Na parte 2, é implementado um algoritmo de divisão e conquista para
#encontrar o par mais próximo dentro de um conjunto de pontos.
#O algoritmo divide o conjunto de pontos em ordem crescente de coordenada
#abcissa; divide os pontos na metade e calcula os pares de distância mínima
#para as metades esquerda e direita.
#Em seguida, o algoritmo busca possíveis soluções no recorte dos pontos que 
#estão a uma distância inferior ao mínimo das duas distâncias mínimas calculadas
#anteriormente.
#Para cada ponto no fecho, a busca é feita em ordem crescente de coordenada do eixo 
#ordenado e apenas os sete valores seguintes são considerados. O recorte e a ordenação 
#dos pontos garantem que apenas os sete primeiros pontos podem estar a uma distância menor
#do que a mínima já obtida.
#O par mais próximo é, assim, o mais próximo dentre o resultado obtido para a metade esquerda,
#a direita, e os pontos no fecho.
#O algoritmo obedece a uma recorrência da forma T(n) = 2T(n/2) + O(n). Logo, sua complexidade é
#O(N*log(N)). 



#Critério de desempate para pares com a mesma distância.
#O critério de desempate é a ordem lexicográfica dos pares
#de pontos, considerando a ordem de entrada.
def comparador(par1, par2, indices_entrada):
    idx01 = indices_entrada[par1[0]]
    idx02 = indices_entrada[par1[1]]
    idx11 = indices_entrada[par2[0]]
    idx12 = indices_entrada[par2[1]]
        
    #Ponto 1 é priorizado
    if idx01 < idx11: return 1
    #Ponto 2 é priorizado
    elif idx11 < idx01: return -1
    #Ponto 1 é priorizado
    elif idx02 < idx12: return 1


#Função que resolve os casos base do problema (N=1, N=2 e N=3)
#por força bruta. Como a quantidade de elementos é sempre menor ou
#igual a 3, a complexidade é sempre constante e não altera a complexidade
#do algoritmo.
def casos_base(pontos, indices_entrada):
    n_pontos = len(pontos)
    
    #N=1: retorna apenas o ponto com distância 0
    if n_pontos == 1: return 0, (pontos[0], None)
    #N=2: retorna o único par de pontos com a distância entre eles
    elif n_pontos == 2: return dist(pontos[0], pontos[1]), (pontos[0], pontos[1])
    #N=3: calcula as três distâncias possíveis e escolhe a menor delas
    elif n_pontos == 3:
        dist1 = dist(pontos[0], pontos[1])
        dist2 = dist(pontos[0], pontos[2])
        dist3 = dist(pontos[1], pontos[2])
        min_dist = min(dist1, dist2, dist3)
        
        #Adiciona as soluções possíveis: pares de pontos podem ter
        #a mesma distância.
        solucoes_possiveis = []
        if(min_dist==dist1):    
            solucoes_possiveis.append((pontos[0], pontos[1]))
        if(min_dist==dist2):
            solucoes_possiveis.append((pontos[0], pontos[2]))
        if(min_dist==dist3):
            solucoes_possiveis.append((pontos[1], pontos[2]))

        #Seleciona a solução de acordo com a ordem de entrada.
        #Note que a complexidade aqui é constante, pois "solucoes_possiveis"
        #tem tamanho no máximo 3.
        solucao_final = solucoes_possiveis[0]
        for i in range(1, len(solucoes_possiveis)):
            if comparador(solucao_final, solucoes_possiveis[i], indices_entrada) == 1:
                solucao_final = solucoes_possiveis[i]

        return min_dist, solucao_final 


            

#Função que calcula o par de pontos mais próximas entre si e a
#distância entre eles.
def encontra_par_mais_proximo(pontos_x, pontos_y, indices_entrada):
    #Casos base (N=1; N=2;N=3)
    if(len(pontos_x) <= 3): return casos_base(pontos_x, indices_entrada)

    #Divisão dos pontos ao meio
    meio = floor(len(pontos_x)/2)
    ponto_meio = pontos_x[meio]
    
    #Par mais próximo à esquerda    
    mais_prox_esq = encontra_par_mais_proximo(pontos_x[:meio], pontos_y, indices_entrada)
    #Par mais próximo à direita
    mais_prox_dir = encontra_par_mais_proximo(pontos_x[meio:], pontos_y, indices_entrada)
    #Distância mínima até o momento
    min_dist = min(mais_prox_esq[0], mais_prox_dir[0])

    #Cria o recorte dos pontos cuja distância no eixo das abcissas ao
    #ponto do meio é menor do que a mínima distância até o momento.
    recorte_min_dist = []
    for ponto in pontos_y:
        if abs(ponto[0] - ponto_meio[0]) <= min_dist:
            recorte_min_dist.append(ponto)

    #Busca as soluções no fecho criado
    melhor_dist = float('inf')
    solucao_recorte = None
    #Percorre todos os pontos no recorte
    for i in range(len(recorte_min_dist)):
        #Considera apenas os 7 pontos seguintes. Se todos fossem considerados,
        #o algoritmo teria complexidade igual a O(n²).
        for j in range(i + 1, min(i + 8, len(recorte_min_dist))):
            #Tentativa de solução
            dist_atual = dist(recorte_min_dist[i], recorte_min_dist[j])
            solucao_atual = (recorte_min_dist[i], recorte_min_dist[j])
            #Atualiza a solução do fecho se a distância for menor ou se o par for
            #priorizado pelo critério de desempate.
            if (melhor_dist > dist_atual) or (melhor_dist==dist_atual and comparador(solucao_atual, solucao_recorte, indices_entrada) == 1):
                melhor_dist = dist_atual
                solucao_recorte = (recorte_min_dist[i], recorte_min_dist[j])
    
    #Distância é a mínima da esquerda, direita e do fecho
    melhor_dist_encontrada = min(min_dist, melhor_dist)
    
    #Inclui todas as soluções encontradas com a mesma distância
    solucoes_possiveis = []
    if mais_prox_esq[0] == melhor_dist_encontrada: solucoes_possiveis.append(mais_prox_esq[1])
    if mais_prox_dir[0] == melhor_dist_encontrada: solucoes_possiveis.append(mais_prox_dir[1])
    if melhor_dist == melhor_dist_encontrada: solucoes_possiveis.append(solucao_recorte)

    #Seleciona a solução de acordo com a ordem de entrada.
    #Note que a complexidade aqui é constante, pois "solucoes_possiveis"
    #tem tamanho no máximo 3
    solucao_final = solucoes_possiveis[0]
    for i in range(1, len(solucoes_possiveis)):
        if comparador(solucoes_possiveis[i], solucao_final, indices_entrada) == 1:
            solucao_final = solucoes_possiveis[i]


    return melhor_dist_encontrada, solucao_final 
    

#Função que encontra o par de sistemas mais próximo.
def parte2(sistemas, indices_entrada):
    #Coordenadas dos sistemas.
    lista_sistemas = list(sistemas.keys())
    #Ordenação crescente de acordo com o eixo das abcissas.
    sistemas_x_sorted = sorted(lista_sistemas)
    #Ordenação crescente de acordo com o eixo das ordenadas.
    sistemas_y_sorted = sorted(lista_sistemas, key=lambda ponto: ponto[1])
    #Calcula o par e a distância correspondente
    min_dist, solucao = encontra_par_mais_proximo(sistemas_x_sorted, sistemas_y_sorted, indices_entrada)

    #Garante que os sistemas do par serão impressos na ordem de entrada.
    solucao_final = None
    if indices_entrada[solucao[0]] > indices_entrada[solucao[1]]:
        solucao_final = (solucao[1], solucao[0])
    else:
        solucao_final = solucao
        
    print(f"Ponto de Ressonância: {sistemas[solucao_final[0]]}, {sistemas[solucao_final[1]]}, {min_dist:.2f}")
    print()

            
def main():
    n_testes = int(input())

    for n in range(n_testes):
        valores = list(map(int, input().split(' ')))
        n_sistemas, n_importantes, tensao_max = valores[0], valores[1], valores[2]

        #Dicionário de sistemas: coordenadas - nome
        sistemas = {}
        #Dicionário de sistemas: coordenadas - índice de entrada
        indices_entrada = {}
        #Leitura dos sistemas
        for i in range(n_sistemas):
            inf_sistema = input().split(' ')
            nome = inf_sistema[0]
            coord = (float(inf_sistema[1]), float(inf_sistema[2]))
            sistemas[coord] = nome
            indices_entrada[coord] = i

        parte1(sistemas, n_importantes, tensao_max)
        parte2(sistemas, indices_entrada)
        

        
if __name__ == '__main__':
    main()