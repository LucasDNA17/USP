
def read_item():
    linha = input()
    valores = linha.split()
    codigo, peso = valores[0], float(valores[1])
    return codigo, peso

def cadastrar_item(cadastros, codigo, peso):
    if codigo not in cadastros:
        cadastros[codigo] = peso
    else:
        print(f"Produto com código {codigo} já cadastrado.") 

def calcular_preco(cadastros, codigo, peso):
    if codigo in cadastros:
        return peso*cadastros[codigo]
    else:
        print(f"Produto com código {codigo} não cadastrado.")
        return 0


def main():

    #Cadastro dos itens
    cadastro_produtos = {}
    qtd_itens_cadastrados = int(input())
    for i in range(0, qtd_itens_cadastrados):
        codigo, peso = read_item()
        cadastrar_item(cadastro_produtos, codigo, peso)

    #Compras
    qtd_compras = int(input())
    while(qtd_compras != -1):
        total_compras = 0
        for j in range(0, qtd_compras):
            codigo, peso = read_item()
            total_compras += calcular_preco(cadastro_produtos, codigo, peso)
        
        print(f"R${total_compras:.2f}")
        qtd_compras = int(input())


if __name__ == "__main__":
    main()



