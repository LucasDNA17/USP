/*
Atividade desenvolvida por:
    Lucas Dúckur Nunes Andreolli - N° USP: 15471518
    Rafael Perez Carmanhani - N° USP: 15485420
*/


public class ArvBin {
    private int size;
    private int len;
    private String[] heap;

    
    ArvBin(int len) {
        this.size = len;
        this.len = 0;
        this.heap = new String[len];
        for(int i = 0; i < this.size; i++) {
            (this.heap)[i] = null;
        }
    }
    
    
    public int len() {
        return this.len;
    }


    protected int find_position(String value) {
        int posicao = -1;
        int i = 0;
        if(value == null) return posicao;
        while(i < size && this.heap[i] != null) {
            if(value.compareTo(this.heap[i]) > 0)
                i = 2*i + 2;
            else if(value.compareTo(this.heap[i]) < 0)
                i = 2*i + 1;
            else {
                posicao = i;
                break;
             }
        }

        return posicao;
    }


    public boolean find(String value) {
        int posicao = find_position(value);
        if(posicao > -1)
            return true;
        else
            return false;
    }

    private String toString_aux() {
        StringBuilder sb = new StringBuilder();
        if(this.len() == 1) {
            return "\"0 " + heap[0] + "\" ";
        }
        for(int i = 0; i < size; i++) {
            if(heap[i] != null) {
                if(2*i + 1 < this.size && (this.heap)[2*i + 1] != null)
                sb.append("\"" + i + " " + (this.heap)[i] + "\" " + "->" + "\"" + (2*i + 1) + " " +  (this.heap)[2*i + 1] + "\"\n");
            if(2*i + 2 < this.size &&(this.heap)[2*i + 2] != null)
                sb.append("\"" + i + " " + (this.heap)[i] + "\" " + "->" + "\"" + (2*i + 2) + " " +  (this.heap)[2*i + 2] + "\" \n");
            }
        }

        String result = sb.toString();
        return result;        
    }


    public String toString() {
        String result = "digraph {\n";
        result = result + toString_aux();
        result = result + "}";
        return result;
    }
        

    
    public void insert(String value) {
        int i = 0;
        boolean eh_igual = false;
        while(i < this.size && this.heap[i] != null) {
            if(value.compareTo(this.heap[i]) > 0)
                i = 2*i + 2;
            else if(value.compareTo(this.heap[i]) < 0)
                i = 2*i + 1;
            else {
                eh_igual = true;
                break;
            }
        }

        if(!eh_igual && i < this.size) {
            this.heap[i] = value;
            this.len++;
        }

    }

   
    
    public void removeUmFilho(int posicao, int esq, int dir) {
        int temp_esq = -1;
        int temp_dir = -1;
        if(heap[esq] == null) {
            heap[posicao] = heap[dir];
            temp_esq = 2*dir + 1;
            temp_dir = 2*dir + 2;
        }

        else if(heap[dir] == null) {
            heap[posicao] = heap[esq];
            temp_esq = 2*esq + 1;
            temp_dir = 2*esq + 2;
        }

        while (temp_dir < size && temp_esq < size) { 
            heap[esq] = heap[temp_esq]; 
            esq = temp_esq; 
            heap[dir] = heap[temp_dir]; 
            dir = temp_dir; 

            temp_dir = (2 * dir) + 2; 
            temp_esq = (2 * esq) + 1; 
        }

        heap[esq] = null;
        heap[dir] = null;

    }



    protected void remove_aux(int posicao, int modo) {
        int filho_esq = 2 * posicao + 1;
        int filho_dir = 2 * posicao + 2;
    
        if ((filho_esq >= size || heap[filho_esq] == null) && 
            (filho_dir >= size || heap[filho_dir] == null)) {
            heap[posicao] = null;
        }
        
        else if((filho_esq >= size || heap[filho_esq] == null) || 
        (filho_dir >= size || heap[filho_dir] == null)) {
            removeUmFilho(posicao, filho_esq, filho_dir);
        }

        else {
            int sucessor_dir = filho_dir;
            while (2 * sucessor_dir + 1 < size && heap[2 * sucessor_dir + 1] != null) {
                sucessor_dir = 2 * sucessor_dir + 1;
            }

            int sucessor_esq = filho_esq;
            while (2 * sucessor_esq + 2 < size && heap[2 * sucessor_esq + 2] != null) {
                sucessor_esq = 2 * sucessor_esq + 2;
            }


            int min = -1;
            if(modo == 0)
                min = Math.min(sucessor_esq, sucessor_dir);
            else if(modo == 1)
                min = sucessor_esq;

            
            heap[posicao] = heap[min];
            remove_aux(min, modo);
        }
    }
    
      

    public boolean remove(String value) {
        int i = 0;
        int posicao = -1;
        while(i < this.size && this.heap[i] != null) {
            if(value.compareTo(this.heap[i]) > 0)
                i = 2*i + 2;
            else if(value.compareTo(this.heap[i]) < 0)
                i = 2*i + 1;
            else {
                posicao = i;
                break;
            }
        }

        if(posicao > -1) {
            this.remove_aux(posicao, 0);
            this.len--;
            return true;
        }

        return false;
    }


    private void InorderTraversal(String array[], int raiz, int[] contador) {
        if(2*raiz + 1 < size && heap[2*raiz + 1] != null) {
            InorderTraversal(array, 2*raiz + 1, contador);
        }

        if(raiz < size && heap[raiz] != null) {
            array[contador[0]] = heap[raiz];
            contador[0]++;
        }

        if(2*raiz + 2 < size && heap[2*raiz + 2] != null) {
            InorderTraversal(array, 2*raiz + 2, contador);
        }


    }


    protected String[] toArray() {
        String array[] = new String[this.len()]; 
        int[] contador = {0};
        InorderTraversal(array, 0, contador);
        return array;
    }



    protected void insert_place(int place, String value) {
        if(!this.find(value))
            this.len++;
        heap[place] = value;    
    }


    protected String get_place(int place) {
        if(place >= size)
            return null;

        return heap[place];
    }

    protected void clear_heap() {
        this.heap = new String[size];
        this.len = 0;
        for(int i = 0; i < this.size; i++) {
            (this.heap)[i] = null;
        }
    }

    protected int n_nodes(int raiz) {
        if(raiz >= size || heap[raiz] == null)
            return 0;

        return 1 + n_nodes(2*raiz + 1) + n_nodes(2*raiz + 2);
    } 


    protected boolean isEmpty(int posicao) {
        if(posicao > size || heap[posicao] == null)
            return true;
        else
            return false;
    }


    protected int node_height(int posicao) {
        if(posicao >= size || heap[posicao] == null)
            return -1;

        return Math.max(node_height(2*posicao + 1), node_height(2*posicao + 2)) + 1;

    }

    protected void decrease_len() {
        this.len--;
    }


}


    


 
   

