
nivelHeroi_velocidade ={'Aprendiz': 0.75, 'Aventureiro': 1.00, 'Cavaleiro': 1.20, 'Mestre' : 1.50, 'Lenda': 2.00}


#### Funções para imprimir os resultados ####

def print_resultados(herois, min_tempo):
    for heroi in herois:
        print(f"{heroi.nome} = ", end='')
        print("{", end='')
        for i in range(len(heroi.quests_finais) - 1):
            print(f"{heroi.quests_finais[i]},", end='')

        if len(heroi.quests_finais) > 0:
            print(f"{heroi.quests_finais[len(heroi.quests_finais) - 1]}", end='')
        print("}")

    print(f"Tempo mínimo: {min_tempo:.2f}")


#### Classes ####

class Quest:
    def __init__(self, id, tempo, dependencias, tempo_ser_feita=0):
        self.id = id
        self.tempo = tempo
        self.dependencias = dependencias
        self.tempo_ser_feita = tempo_ser_feita

class Heroi:
    def __init__(self, nome, nivel, quests=[], quests_finais=[], tempo_ocupado=0):
        self.nome = nome
        self.nivel = nivel
        self.tempo_ocupado = tempo_ocupado
        self.quests = quests
        self.quests_finais = quests_finais



#### Funções que resolvem o problema ####

#Escolhe o melhor heŕoi para uma quest pronta
def get_melhor_heroi(herois, quests, quest, min_tempo):
    heroi_escolhido = None
    tempo_conclusao = float('inf')
    velocidade = 0

    for heroi in herois:
        velocidade = nivelHeroi_velocidade[heroi.nivel]
        tempo_total  = max(heroi.tempo_ocupado + quest.tempo/velocidade, quest.tempo_ser_feita + quest.tempo/velocidade)

        if tempo_total < tempo_conclusao:
            heroi_escolhido = heroi
            tempo_conclusao = tempo_total

    heroi_escolhido.tempo_ocupado = tempo_conclusao
    heroi_escolhido.quests.append(quest)
    heroi_escolhido.quests_finais.append(quest.id)
    quest.tempo_ser_feita = tempo_conclusao

    for og_quest in quests:
        if quest.id in og_quest.dependencias: og_quest.tempo_ser_feita = max(og_quest.tempo_ser_feita, quest.tempo_ser_feita)


    min_tempo = max(min_tempo, quest.tempo_ser_feita)
    return herois, quest, quests, min_tempo



#Resolve o problema
def solve(herois, quests):
    min_tempo = 0

    quests_prontas = []
    quests_ja_processadas = set()

    for quest in quests:
        if len(quest.dependencias) == 0: 
            quests_prontas.append(quest)

    #Enquanto houver quests prontas, escolha os heróis para elas
    while(len(quests_prontas) != 0):
        quest_a_ser_feita = quests_prontas.pop(0)
        
        herois, quest_a_ser_feita, quests, min_tempo = get_melhor_heroi(herois, quests, quest_a_ser_feita, min_tempo)
    
        quests_ja_processadas.add(quest_a_ser_feita.id)

        for quest in quests:
            if quest.id in quests_ja_processadas or quest in quests_prontas:
                continue

            pronta = True
            for dependenciaId in quest.dependencias:
                if dependenciaId not in quests_ja_processadas:
                    pronta = False
                    break

            if pronta: 
                quests_prontas.append(quest)

        
    return min_tempo, herois


def main():
    n_testes = int(input())

    for i in range(n_testes):
        qtds = input().split(' ')
        n_herois, n_quests = int(qtds[0]), int(qtds[1])

        #Leitura dos heróis
        herois = []
        for _ in range(n_herois):
            strings = input().split(' ')
            nome, nivel = strings[0].replace("\r", ""), strings[1].replace("\r", "")
            herois.append(Heroi(nome, nivel, quests=[], quests_finais=[]))
            
        #Leitura das quests
        quests = []
        for _ in range(n_quests):
            valores = input().split(' ')
            id, tempo = int(valores[0]), int(valores[1])

            dependencias = []
            if(len(valores) > 3 or int(valores[2]) != 0):
                dependencias = [int(valores[i]) for i in range(2, len(valores))]

            quests.append(Quest(id, tempo, dependencias))


        min_tempo, herois = solve(herois, quests)
        print_resultados(herois, min_tempo)
        
        if i < n_testes - 1:
            print()

            

if __name__ == '__main__':
    main()
            
