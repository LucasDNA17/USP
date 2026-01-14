from functools import cmp_to_key


def get_min_dias(dias):
    #Ordena os dias em ordem decrescente de ganho
    dias.sort(key = lambda dia: dia[1], reverse=True)

    #Restante = total - ganhos_dos_dias_selecionados
    #Inicialmente, é igual a soma dos ganhos de todos os dias
    restante = sum(map(lambda dia: dia[1], dias))
    
    dias_selecionados = []
    total_escolhido = 0

    #Escolhe os dias com os maiores ganhos até que o total_escolhido seja maior que o resto
    while(restante >= total_escolhido):
        melhor_dia = dias[len(dias_selecionados)]
        dias_selecionados.append(melhor_dia)
        restante -= melhor_dia[1]
        total_escolhido += melhor_dia[1]

    return dias_selecionados


#Transforma uma string de data na forma DD/MM/AAAA em três valores de dia, mês, ano
def dia_string_to_int(dia_string):
    valores = dia_string.split('/')
    return int(valores[0]), int(valores[1]), int(valores[2]) 
    

#Função de comparação que decide qual data antecede cronologicamente outra
def compara_dia(dia1, dia2):
    dia1, mes1, ano1 = dia_string_to_int(dia1[0])
    dia2, mes2, ano2 = dia_string_to_int(dia2[0])

    if(ano1 < ano2):
        return -1
    elif(ano2 < ano1):
        return 1
    elif(mes1 < mes2):
        return -1
    elif(mes2 < mes1):
        return 1
    elif(dia1 < dia2):
        return -1
    elif(dia2 < dia1):
        return 1
    else:
        return 0


#Função que printa os dias escolhidos (em ordem cronológica), a soma dos ganhos dos dias escolhidos
#e a razão (em porcentagem) entre o número de dias escolhidos e o número total de dias
def get_estatisticas_dias(dias_selecionados, qtd_total_dias):
    dias_selecionados.sort(key = cmp_to_key(compara_dia))

    print(f"{len(dias_selecionados)} dias (", end="")
    for i in range(len(dias_selecionados) - 1):
        print(f"{dias_selecionados[i][0]}, ", end="")
    
    if(len(dias_selecionados) > 0):
        print(f"{dias_selecionados[len(dias_selecionados) - 1][0]}", end="")


    print(f") | soma={sum(map(lambda dia: dia[1], dias_selecionados)):.2f} | {100*len(dias_selecionados)/qtd_total_dias:.2f}% dos dias totais")



def main():
    
    qtd_testes = int(input())
    for i in range(qtd_testes):
        dias = []
        qtd_dias = int(input())
        for j in range(qtd_dias):
            data_valor = input().split(' ')
            data, valor = data_valor[0], float(data_valor[1])
            dias.append((data, valor))

        dias_selecionados = get_min_dias(dias)
        get_estatisticas_dias(dias_selecionados, len(dias))
    

    
if __name__ == "__main__":
    main()