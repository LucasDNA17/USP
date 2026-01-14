
def pd(dias, diamantes):
    M = [[[- 1  for h in range(2)] for i in range(2)] for j in range(len(dias))]


    M[0][0][0] = diamantes
    if dias[0] <= diamantes:
        M[0][0][1] = diamantes - dias[0]


    for i in range(1, len(dias)):
        #Calcular M[i][0][0]
        valor_max = max(M[i - 1][0][0], M[i - 1][1][0])
        M[i][0][0] = valor_max


        #Calcular M[i][0][1]
        valor_max = max(M[i - 1][0][1], M[i - 1][1][1], M[i - 1][0][0] - dias[i])
        M[i][0][1] = valor_max

        #Calcular M[i][1][0]
        valor_max = M[i - 1][0][1] + dias[i]
        M[i][1][0] = valor_max


    n = len(dias) - 1
    return max(M[n][0][0], M[n][0][1], M[n][1][0], M[n][1][1])


    

def main():
    n_fases = int(input())
    for _ in range(n_fases):
        n_diamantes_iniciais = int(input())
        n_dias = int(input())
        dias = list(map(int, input().split(" ")))
        result = pd(dias, n_diamantes_iniciais)
        print(result)



if __name__ == "__main__": main()