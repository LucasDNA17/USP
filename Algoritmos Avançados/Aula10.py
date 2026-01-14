from math import sqrt


def is_prime(n):
    limit = int(sqrt(n))

    for i in range(2, limit + 1):
        if n % i == 0: return False

    return True

def next_prime(n):
    counter = 1
    while(True):
        number = n + counter
        if is_prime(number): return number
        else: counter += 1


#Pequeno Teorema de Fermat
def find_multiplicative_inverse(t, p):
    return pow(t, p - 2, p)
    

def main():
    valores = input().split(' ')
    n, t = int(valores[0]), int(valores[1])

    p = next_prime(n)
    a = find_multiplicative_inverse(t, p)
    print(a)


if __name__ == '__main__':
    main()