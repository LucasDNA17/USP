
class person:
    def __init__(self, tem_doenca, pai, mae):
        self.tem_doenca = tem_doenca
        self.pai = pai
        self.mae = mae


def string_to_boolean(string):
    return string=="sim"


def search_hereditary_diabetes(arvore_genealogica):
    qtd_diabetes_hereditaria = 0
    for i in range(len(arvore_genealogica)):
        person = arvore_genealogica[i]
        if(person.tem_doenca and ((person.pai != -1 and arvore_genealogica[person.pai - 1].tem_doenca)
        or (person.mae != -1 and arvore_genealogica[person.mae - 1].tem_doenca))):
            qtd_diabetes_hereditaria += 1

    return qtd_diabetes_hereditaria


def main():
    n_testes = int(input())
    
    for i in range(n_testes):
        n_pessoas = int(input())
        arvore_genealogica = [None]*n_pessoas

        for j in range(n_pessoas):
            id, tem_doenca, pai, mae = input().split(' ')
            id, pai, mae = int(id), int(pai), int(mae)
            tem_doenca = string_to_boolean(tem_doenca)

            arvore_genealogica[id - 1] = person(tem_doenca, pai, mae)

        print(search_hereditary_diabetes(arvore_genealogica))
        

if __name__ == "__main__":
    main()