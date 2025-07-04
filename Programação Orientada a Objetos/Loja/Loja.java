public class Loja {
    private int qtd_produtos;
    private int posicao_vazia;
    private int qtd_livros;
    private int qtd_cds;
    private int qtd_dvds;
    private Produto produtos[];
    private int estoque[];


    public Loja() {
        this.qtd_produtos = 0;
        this.posicao_vazia = 0;
        this.qtd_livros = 0;
        this.qtd_cds = 0;
        this.qtd_dvds = 0;
        this.produtos = new Produto[50];
        this.estoque = new int[50];
    }
    
    private void sucesso(boolean Ehestoque, long codigo) {
        if(!Ehestoque)
            System.out.println("Operação realizada com sucesso");
        else
            System.out.println("Operação realizada com sucesso: " + codigo);
    }

    private void printa_produto(Produto produto) {
        if(produto instanceof Livro) {
            Livro livro = (Livro) produto;
            System.out.println(livro.toString());
        }
        
        else if(produto instanceof CD) {
            CD cd = (CD) produto;
            System.out.println(cd.toString());
        }

        else if(produto instanceof DVD) {
            DVD dvd = (DVD) produto;
            System.out.println(dvd.toString());
        }       
    }
    
    private int procurar_pos_produto(long codigo) {
        int pos = -1;
        for(int i = 0; i < this.qtd_produtos; i++) {
            if(produtos[i].get_codigo() == codigo) {
                pos = i;
                break;
            }
        }

        return pos;
    }


    private int procurar_pos_produto(String nome) {
        int pos = -1;
        for(int i = 0; i < this.qtd_produtos; i++) {
            if(produtos[i].get_nome().equals(nome)) {
                pos = i;
                break;
            }
        }

        return pos;
    }


    public Produto procurar_produto(long codigo, String s_codigo) {
        System.out.println("\nProcurando: " + s_codigo);
        int pos = procurar_pos_produto(codigo);
        if(pos == -1) {
            System.out.println("Produto não encontrado: " + s_codigo);
            return null;
        }
        else {
            System.out.println("Encontrado:");
            printa_produto(produtos[pos]);
            return produtos[pos];
        }
        
    }

    public Produto procurar_produto(String nome) {
        System.out.println("\nProcurando: " + nome);
        int pos = procurar_pos_produto(nome);
        if(pos == -1) {
            System.out.println("Produto não encontrado: " + nome + "\n");
            return null;
        }
        else {
            System.out.println("Encontrado:");
            printa_produto(produtos[pos]);
            return produtos[pos];
        }
        
    }

    public boolean insere_produto(Produto produto) {
        int pos_produto = procurar_pos_produto(produto.get_codigo());
        String tipo = "Nenhum";
        if(produto instanceof Livro) tipo = "livro";
        else if(produto instanceof CD) tipo = "CD";
        else if(produto instanceof DVD) tipo = "DVD";
        System.out.println("\nOperação inserir " + tipo + ": " + produto.get_codigo());

        if(pos_produto != -1) {
            System.out.println("***Erro: Código já cadastrado: " + produto.get_codigo());
            return false;
        }

        else 
        {
            this.produtos[posicao_vazia] = produto;
            this.posicao_vazia++;
            this.qtd_produtos++;
            this.sucesso(false, -1);
            return true;
        }
    }



    public boolean adicionar_produtos_estoque(long codigo, int quantidade) {
        int pos = procurar_pos_produto(codigo);
        System.out.println("\nOperação de compra: " + codigo);
        if(pos == -1) {
            System.out.println("***Erro: Código inexistente: " + codigo);
            return false; //Produto não encontrado
        }

        this.sucesso(true, codigo);
        if(produtos[pos] instanceof Livro) this.qtd_livros += quantidade; 
        else if(produtos[pos] instanceof CD) this.qtd_cds += quantidade;
        else if(produtos[pos] instanceof DVD) this.qtd_dvds += quantidade;
        estoque[pos] += quantidade;
        return true;
    } 


    

    public boolean vender_produtos_estoque(long codigo, int quantidade) {
        int pos = procurar_pos_produto(codigo);
        System.out.println("\nOperação de venda: " + codigo);
        if(pos == -1) {
            System.out.println("***Erro: Código inexistente: " + codigo);
            return false; //Produto não encontrado
        }

        else if(estoque[pos] < quantidade) {
            System.out.println("***Erro: Estoque insuficiente: " + codigo + " Quantidade: " + quantidade);
            return false; //Não há produtos suficientes
        }

        this.sucesso(true, codigo);
        if(produtos[pos] instanceof Livro) this.qtd_livros -= quantidade; 
        else if(produtos[pos] instanceof CD) this.qtd_cds -= quantidade;
        else if(produtos[pos] instanceof DVD) this.qtd_dvds -= quantidade;
        estoque[pos] -= quantidade;
        return true;
    }
    
    
    public void Sumarizar() {
        System.out.println("\nOperação de sumarização: ");
        for(int i = 0; i < qtd_produtos; i++) {
            if(produtos[i] instanceof Livro) {
                printa_produto(produtos[i]);
                System.out.println("Quantidade: " + estoque[i] + "\n");
            }
        }

        System.out.println("Quantidade de Livros: " + this.qtd_livros + "\n");

        for(int i = 0; i < qtd_produtos; i++) {
            if(produtos[i] instanceof CD) {
                printa_produto(produtos[i]);
                System.out.println("Quantidade: " + estoque[i] + "\n");
            }
        }

        System.out.println("Quantidade de CDs: " + this.qtd_cds + "\n");

        for(int i = 0; i < qtd_produtos; i++) {
            if(produtos[i] instanceof DVD) {
                printa_produto(produtos[i]);
                System.out.println("Quantidade: " + estoque[i] + "\n");
            }
        }

        System.out.println("Quantidade de DVDs: " + this.qtd_dvds + "\n");
    }


}
