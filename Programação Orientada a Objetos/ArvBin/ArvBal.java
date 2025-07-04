/*
Atividade desenvolvida por:
    Lucas Dúckur Nunes Andreolli - N° USP: 15471518
    Rafael Perez Carmanhani - N° USP: 15485420
*/


public class ArvBal extends ArvBin {
    
    ArvBal(int len) {
        super(len);
    }


    private boolean eh_balanceado(int raiz) {
        if(this.len() <= 2)
            return true;

        if(isEmpty(raiz))
            return true;
        if(Math.abs(n_nodes(2*raiz + 1) - n_nodes(2*raiz + 2)) > 1)
            return false;
        else {
            return eh_balanceado(2*raiz + 1) && eh_balanceado(2*raiz + 2);
        }
    }

    private void reinsere(String[] array, int inicio, int fim, int posicao) {
        if (inicio > fim) return;
        
        int meio = inicio + (fim - inicio)/2;
        super.insert_place(posicao, array[meio]);
        
        reinsere(array, inicio, meio-1, 2*posicao+1);
        reinsere(array, meio+1, fim, 2*posicao+2);
    }

    @Override public void insert(String value) {
        super.insert(value);
        if(!this.eh_balanceado(0)) {
            String[] array = super.toArray();
            super.clear_heap();
            reinsere(array, 0, array.length - 1, 0);
        }
    }

    @Override public boolean remove(String value) {
        boolean result = super.remove(value);
        if(!this.eh_balanceado(0)) {
            String[] array = super.toArray();
            super.clear_heap();
            reinsere(array, 0, array.length - 1, 0);
        }
        return result;
    }
}
