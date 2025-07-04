public class Livro extends Produto{
    private String editora;
    private int edicao;
    private int paginas;
    private String idioma;


    public Livro (long codigo, String Nome, String autor, String editora, int ano, int edicao, int paginas, String idioma) {
        super(codigo, Nome, ano, autor);
        this.editora = editora;
        this.edicao = edicao;
        this.paginas = paginas;
        this.idioma = idioma ;
    }

    public String get_editora() {return this.editora;}
    public int get_edicao() {return this.edicao;}
    public int get_paginas() {return this.paginas;}
    public String get_idioma() {return this.idioma;}
    
    public String toString() {
        String resultado = "Livro\n";
        resultado += "Código: " + this.get_codigo() + "\n";
        resultado += "Título: " + this.get_nome() + "\n";
        resultado += "Autor: " + this.get_autor() + "\n";
        resultado += "Editora: " + this.get_editora() + "\n";
        resultado += "Edição: " + this.get_edicao() + "\n";
        resultado += "Ano: " + this.get_ano() + "\n";
        resultado += "Páginas: " + this.get_paginas() + "\n";
        resultado += "Idioma: " + get_idioma();
        return resultado;
    }
}
