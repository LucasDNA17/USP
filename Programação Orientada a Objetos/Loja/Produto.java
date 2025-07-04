public class Produto {
    private long codigo;
    private String nome;
    private int ano;
    private String autor;


    public Produto(long codigo, String nome, int ano, String autor) {
        this.codigo = codigo;
        this.nome = nome;
        this.ano = ano;
        this.autor = autor;
    }


    public long get_codigo() {return this.codigo;}
    public String get_nome() {return this.nome;}
    public int get_ano() {return this.ano;}
    public String get_autor() {return this.autor;}

}
