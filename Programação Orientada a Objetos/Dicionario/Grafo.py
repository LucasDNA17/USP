import queue
from sys import stdin

class Grafo:

    def __init__(self):
        self.grafo = {}


    def le_vertices(self):
        vertice = input()
        arestas = {}

        while True:
            try:
                line = input()

                while(line[0] == '\t'):
                    line = line.strip()
                    campos_aresta = line.split(' ')
                    if(len(campos_aresta) < 2):
                        campos_aresta = (campos_aresta[0]).split('\t')
                    arestas[campos_aresta[0]] = campos_aresta[1]
                    line = input()

                vertice = vertice.replace('\r', "")
                self.grafo[vertice] = arestas
                vertice = line
                arestas = {}

            except EOFError:
                vertice = vertice.replace('\r', "")
                self.grafo[vertice] = arestas
                vertice = line
                arestas = {}
                break

        
        
        
        
    def Dijkstra(self, inicio):
        vertices = {}
        vertices_nao_visitados = queue.PriorityQueue()

        for key in self.grafo:
            #Dicionário de distância, visitado e pai.
            if(key == inicio):
                vertices[key] = (0, False, None)
            else:
                vertices[key] = (float('inf'), False, None)


        atual = inicio
        while True:
            #Marca o vértice como já visitado.
            vertices[atual] = (vertices[atual][0], True, vertices[atual][2])


            distancia_atual = vertices[atual][0]

            for key in self.grafo[atual]:
                #Já foi visitado
                if vertices[key][1]:
                    continue

                aresta = float(self.grafo[atual][key])
                distancia_filho = vertices[key][0]
                pai = vertices[key][2]

                #Atualiza os filhos se necessário.
                if (aresta + distancia_atual) < distancia_filho:
                    distancia_filho = aresta + distancia_atual
                    pai = atual

                vertices[key] = (distancia_filho, False, pai)

                #Adiciona os filhos à fila de não visitados.
                vertices_nao_visitados.put((distancia_filho, key))
                

            #Visita o vértice não-visitado com a menor distância calculada. 
            if(vertices_nao_visitados.empty()):
                break
            else:
                atual = (vertices_nao_visitados.get())[1]
              
        return vertices
    

    def get_caminho(self, buscado, vertices):
        pai = vertices[buscado][2]

        if pai == None:
            return(" ")

        return(self.get_caminho(pai, vertices) + " --> " + buscado)
        

    def printa_caminhos_distancias(self):
        for key in self.grafo:
            caminhos_distancias = self.Dijkstra(key)
            for key_ in caminhos_distancias:
                if key != key_:
                    print(key + " para " + key_)
                    distancia = str(caminhos_distancias[key_][0])
                    print("	Distancia: " + distancia.replace(".", ","))
                    print("	Caminho:" + self.get_caminho(key_, caminhos_distancias))
            print("---------------------------------------------")
                

def main():
    grafo = Grafo()
    grafo.le_vertices()
    grafo.printa_caminhos_distancias()
    

main()