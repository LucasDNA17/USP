import java.util.Scanner;
import java.lang.Math; 

public class principal {    
    private static Scanner reader;
    private static int[] vet;
    private static tabuleiro tab;

    /*Retorna a quantidade de valores lidos */
    private static int leitura() {
        reader = new Scanner(System.in);
        int contador = 0;
        while(reader.hasNextInt()) {
            vet[contador] = reader.nextInt();
            contador++;
        }

        return(contador);
    } 

    private static void operacoes() {
        tab.printa_tabuleiro();
        if(reader.hasNext());
        String s = reader.next();
        for(int i = 0; i < s.length(); i++) {
            tab.movimento(s.charAt(i));
            tab.printa_tabuleiro();
        }
    }


    public static void main(String[] args) {
        
        /*Tamanho máximo da leituea = 36*/
        int max_tam = 36;
        vet = new int[max_tam];

        int quantidade = leitura();

        tab = new tabuleiro( (int) Math.sqrt(quantidade), (int) Math.sqrt(quantidade));
        tab.preencher_tabuleiro(vet, quantidade);

        operacoes();
        System.out.println("Posicao final:" + " " + tab.Ehsolucao());
        reader.close();
    }

}
