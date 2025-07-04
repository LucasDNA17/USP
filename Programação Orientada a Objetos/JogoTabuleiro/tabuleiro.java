public class tabuleiro {
    private int largura;
    private int comprimento;
    private int zero_fileira;
    private int zero_coluna;
    private int[][] tbl;

    public tabuleiro(int largura, int comprimento) {
        this.largura = largura;
        this.comprimento = comprimento;
        tbl = new int[comprimento][largura];
    }

    public void preencher_tabuleiro(int[] valores, int quantidade) {
        if(quantidade == comprimento*largura) {
            for(int i = 0; i < comprimento; i++) 
                for(int j = 0; j < largura; j++) {
                    tbl[i][j] = valores[largura*i + j];
                    if(valores[largura*i + j] == 0) {
                        zero_fileira = i;
                        zero_coluna = j;
                    }
                } 
        }
    }

    private void swap(int i1, int j1, int i2, int j2) {
        int aux = tbl[i1][j1];
        tbl[i1][j1] = tbl[i2][j2];
        tbl[i2][j2] = aux;
    } 

    private void tabuleiro_up() {
        if(zero_fileira < comprimento - 1) {
            swap(zero_fileira + 1, zero_coluna, zero_fileira, zero_coluna);
            zero_fileira += 1;
        }
    }
    private void tabuleiro_down() {
        if(zero_fileira > 0) {
            swap(zero_fileira - 1, zero_coluna, zero_fileira, zero_coluna);
            zero_fileira -= 1;
        }
    }

    private void tabuleiro_left() {
        if(zero_coluna < largura - 1) {
            swap(zero_fileira, zero_coluna + 1, zero_fileira, zero_coluna);
            zero_coluna += 1;
        }
    }

    private void tabuleiro_right() {
        if(zero_coluna > 0) {
            swap(zero_fileira, zero_coluna - 1, zero_fileira, zero_coluna);
            zero_coluna -= 1;
        }
    }


    public void movimento(char c) {
        switch (c) {
            case 'u':
                tabuleiro_up();
                break;
        
            case 'd':
                tabuleiro_down();
                break;
    
            case 'l':
                tabuleiro_left();
                break;
        
            case 'r':
                tabuleiro_right();
                break; 
        }
    }

    private void print_line(int tamanho) {
        for(int i = 0; i < tamanho; i++) {
            System.out.print("+------");
        }
        System.out.println("+");
    }

    
    public void printa_tabuleiro() {
        print_line(largura);
        
        for(int i = 0; i < comprimento; i++) {
            System.out.print("|");
            for(int j = 0; j < largura; j++) {
                if(tbl[i][j] >= 10)
                    System.out.print("  " + tbl[i][j] + "  |");
                else
                    System.out.print("   " + tbl[i][j] + "  |");
            }

            System.out.println();
            print_line(largura);
        }

        System.out.println();
    }


    public boolean Ehsolucao() {
        for(int i = 0; i < comprimento; i++)
            for(int j = 0; j < largura; j++)
                if((tbl[i][j]) != largura*i + j)
                    return false;

        return(true);
    }



}
