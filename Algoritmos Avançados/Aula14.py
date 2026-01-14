

def prefixo_sufixo(string):
    idx = -1
    
    for i in range(1, len(string)):
      
        if string[:i] == string[-i:]:
            idx = i
       
    if idx == -1: return ''
    else: return string[:idx]



def main():
    n_testes = int(input())
    for _ in range(n_testes):
        string = input()
        print(prefixo_sufixo(string))


if __name__ == '__main__': main()