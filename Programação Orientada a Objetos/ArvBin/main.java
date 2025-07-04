/*
Atividade desenvolvida por:
    Lucas Dúckur Nunes Andreolli - N° USP: 15471518
    Rafael Perez Carmanhani - N° USP: 15485420
*/


import java.util.Scanner;

public class main {
    private static Scanner leitor;
    private static ArvBin arv_bin;
    private static ArvBal arv_bal;
    private static ArvAVL arv_avl;
    public static void main(String args[]) {
        leitor = new Scanner(System.in);
        arv_bin = new ArvBin(100);
        arv_bal = new ArvBal(100);
        arv_avl = new ArvAVL(100);


        while(leitor.hasNextLine()) {
            String line = leitor.nextLine();
            String tokens[] = line.split("\\s+");
            
            if(tokens[0].equals("i")) {
                arv_bin.insert(tokens[1]);
                arv_bal.insert(tokens[1]);
                arv_avl.insert(tokens[1]);
            }

            else if(tokens[0].equals("d")) {
                arv_bin.remove(tokens[1]);
                arv_bal.remove(tokens[1]);
                arv_avl.remove(tokens[1]);
            }

            else
                break;
        }

        System.out.println(arv_bin.toString());
        System.out.println();
        System.out.println(arv_bal.toString());
        System.out.println();
        System.out.println(arv_avl.toString());
        System.out.println();

    }
    
}
