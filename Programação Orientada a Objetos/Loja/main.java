import java.util.Scanner;

public class main {

    private static boolean ehLong(String string) {
        try {
            Long.parseLong(string);
            return true;
        }

        catch(NumberFormatException e) {
            return false;
        }
    }
 

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        Loja loja = new Loja();


        while(scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String campos[] = line.split(",");

            if(campos[0].equals("I")) {
                long codigo = Long.parseLong(campos[2]);

                if(campos[1].equals("Livro")) {
                    int ano = Integer.parseInt(campos[6]);
                    int edicao = Integer.parseInt(campos[7]);
                    int n_paginas = Integer.parseInt(campos[8]); 
                    Livro livro = new Livro(codigo, campos[3], campos[4], campos[5], ano, edicao, n_paginas, campos[9]);
                    loja.insere_produto(livro);
                }

                if(campos[1].equals("CD")) {
                    int n_trilhas = Integer.parseInt(campos[5]);
                    int ano = Integer.parseInt(campos[7]);
                    CD cd = new CD(codigo, campos[3], ano, campos[4], n_trilhas, campos[6]);
                    loja.insere_produto(cd);
                }

                if(campos[1].equals("DVD")) {
                    int ano = Integer.parseInt(campos[7]);
                    DVD dvd = new DVD(codigo, campos[3], ano, campos[4], campos[5], campos[6], campos[8]);
                    loja.insere_produto(dvd);
                }
            }

            else if(campos[0].equals("A")) {
                long codigo = Long.parseLong(campos[1]);
                int quantidade = Integer.parseInt(campos[2]);
                loja.adicionar_produtos_estoque(codigo, quantidade);
            }

            else if(campos[0].equals("V")) {
                long codigo = Long.parseLong(campos[1]);
                int quantidade = Integer.parseInt(campos[2]);
                loja.vender_produtos_estoque(codigo, quantidade);
            }


            else if(campos[0].equals("P")) {
                if(ehLong(campos[1])) {
                    long codigo = Long.parseLong(campos[1]);
                    loja.procurar_produto(codigo, campos[1]);
                }
                
                else { 
                     loja.procurar_produto(campos[1]);
                }
            }

            else if(campos[0].equals("S"))
                loja.Sumarizar();

        }

        scanner.close();
    }
}
