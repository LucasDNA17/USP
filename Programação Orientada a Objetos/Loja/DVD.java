public class DVD extends Produto {
    private String idioma;
    private String genero;
    private String nacionalidade;


    public DVD(long codigo, String nome, int ano, String diretor, String idioma, String genero, String nacionalidade) {
        super(codigo, nome, ano,  diretor );
        this.idioma = idioma;
        this.genero = genero;
        this.nacionalidade = nacionalidade;
    }


    public String get_idioma() {return this.idioma;}
    public String get_genero() {return this.genero;}
    public String get_nacionalidade() {return this.nacionalidade;}


    public String toString() {
        String resultado = "DVD\n";
        resultado += "Código: " + this.get_codigo() + "\n";
        resultado += "Título: " + this.get_nome() + "\n";
        resultado += "Diretor: " + this.get_autor() + "\n";
        resultado += "Gênero: " + this.get_genero() + "\n";
        resultado += "Ano: " + this.get_ano() + "\n";
        resultado += "Nacionalidade: " + this.get_nacionalidade() + "\n";
        resultado += "Idioma: " + this.get_idioma();
        return resultado;
    }
}
