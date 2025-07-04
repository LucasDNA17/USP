//Atividade desenvolvida por:
//Lucas Dúckur Nunes Andreolli     N°USP: 15471518

import java.util.*;
import java.io.*;


//Classe que representa um país
class Pais {
    private String nome;
    private int Confirmed;
    private int Deaths;
    private int Recovery;
    private int Active;

    public Pais(String nome, int Confirmed, int Deaths, int Recovery, int Active)
    {
        this.nome = nome;
        this.Confirmed = Confirmed;
        this.Deaths = Deaths;
        this.Recovery = Recovery;
        this.Active = Active;
    } 

    public String get_nome() {return nome;}
    public int get_Confirmed() {return Confirmed;}
    public int get_Deaths() {return Deaths;}
    public int get_Recovery() {return Recovery;}
    public int get_Active() {return Active;}
}


public class Main {
    

    //Método para ler os números de entrada
    private static int[] leitura()
    {
        int[] vet = new int[4];
        Scanner leitor = new Scanner(System.in);

        String line = leitor.nextLine();
        leitor.close();

        String tokens[] = line.split("\\s+");

        for(int i = 0; i < 4; i++)
            vet[i] = Integer.parseInt(tokens[i]);

        return vet;
    }
    
    //Método para ler os dados do arquivo .csv
    private static List<Pais> ler_arquivo_csv()
    {
        List<Pais> paises = new ArrayList<Pais>();
        String nome_arquivo = "dados.csv";
        try (Scanner leitor = new Scanner(new File(nome_arquivo)))
        {
            while(leitor.hasNextLine()) 
            {
                String line = leitor.nextLine();
                String[] tokens = line.split(",");
                paises.add(new Pais(tokens[0], Integer.parseInt(tokens[1]), Integer.parseInt(tokens[2]), 
                Integer.parseInt(tokens[3]), Integer.parseInt(tokens[4])));
            }
        }

        catch (IOException e) 
        {
            e.printStackTrace();
        }

        return paises;
    }
    

    public static void main (String args[]) {
        int[] nums = leitura();
        List<Pais> paises = ler_arquivo_csv();

        //Soma de "Active" de todos os países em que "Confirmed" é maior o igual que n1
        int soma_active = paises.stream()
                        .filter(p -> p.get_Confirmed() >= nums[0])
                        .map(Pais::get_Active)
                        .reduce(0, (x1, x2) -> x1 + x2);

        System.out.println(soma_active);


        //Dentre os n2 países com maiores valores de "Active", a soma das "Deaths" dos n3 países com menores valores de "Confirmed".
        int soma_deaths = paises.stream()
                        .sorted(Comparator.comparing(Pais::get_Active).reversed())
                        .limit(nums[1])
                        .sorted(Comparator.comparing(Pais::get_Confirmed))
                        .limit(nums[2])
                        .map(Pais::get_Deaths)
                        .reduce(0, (x1, x2) -> x1 + x2);

        System.out.println(soma_deaths);


        //Os n4 países com os maiores valores de "Confirmed". Os nomes devem estar em ordem alfabética.
        paises.stream()
            .sorted(Comparator.comparing(Pais::get_Confirmed).reversed())
            .limit(nums[3])
            .sorted(Comparator.comparing(Pais::get_nome))
            .map(Pais::get_nome)
            .forEach(System.out::println);
    }
}
