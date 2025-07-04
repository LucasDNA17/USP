public class CD extends Produto {
    private int n_trilhas;
    String gravadora;


    public CD (long codigo, String Album, int ano, String cantor_banda, int n_trilhas, String gravadora) {
        super(codigo, Album, ano, cantor_banda);
        this.n_trilhas = n_trilhas;
        this.gravadora = gravadora;
    }


    public int get_ntrilhas() {return this.n_trilhas;}
    public String get_gravadora() {return this.gravadora;}

    public String toString() {
        String resultado = "CD\n";
        resultado += "Código: " + this.get_codigo() + "\n";
        resultado += "Título: " + this.get_nome() + "\n";
        resultado += "Banda: " + this.get_autor() + "\n";
        resultado += "Gravadora: " + this.get_gravadora() + "\n";
        resultado += "Ano: " + this.get_ano() + "\n";
        resultado += "trilhas: " + this.get_ntrilhas();
        return resultado;
    }
}
