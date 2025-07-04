/*
Atividade desenvolvida por:
    Lucas Dúckur Nunes Andreolli - N° USP: 15471518
    Rafael Perez Carmanhani - N° USP: 15485420
*/

public class ArvAVL extends ArvBin {
    
    
    ArvAVL(int len) {
        super(len);
    }


    private int filho_esquerdo(int raiz) {
        return 2*raiz + 1;
    }

    private int filho_direito(int raiz) {
        return 2*raiz + 2;
    }

    private int get_balance(int raiz) {
        if(isEmpty(raiz))
            return 0;

        int h_esq = super.node_height(2*raiz + 1);
        int h_dir = super.node_height(2*raiz + 2);
        
        return h_esq - h_dir;
    }


    private void desloca_cima(int raiz, int direcao) {
        if(isEmpty(raiz)) return;

        super.insert_place(direcao, super.get_place(raiz));
        super.insert_place(raiz, null);
        desloca_cima(filho_esquerdo(raiz), filho_esquerdo(direcao));
        desloca_cima(filho_direito(raiz), filho_direito(direcao));
    }
    
    private void desloca_baixo(int raiz, int direcao) {
        if(isEmpty(raiz)) return;

        desloca_baixo(filho_esquerdo(raiz), filho_esquerdo(direcao));
        desloca_baixo(filho_direito(raiz), filho_direito(direcao));
        super.insert_place(direcao, super.get_place(raiz));
        super.insert_place(raiz, null);
    } 


    private void rotacao_esq(int raiz) {
        int filho_esq = filho_esquerdo(raiz);
        int filho_dir = filho_direito(raiz);

        desloca_baixo(filho_esq, filho_esquerdo(filho_esq));
        super.insert_place(filho_esq, super.get_place(raiz));

        super.insert_place(raiz, super.get_place(filho_dir));
        desloca_baixo(filho_esquerdo(filho_dir), filho_direito(filho_esq));
        desloca_cima(filho_direito(filho_dir), filho_dir);
    }

    private void rotacao_dir(int raiz) {
        int filho_esq = filho_esquerdo(raiz);

        desloca_baixo(filho_direito(raiz), filho_direito(filho_direito(raiz)));
        super.insert_place(filho_direito(raiz), super.get_place(raiz));
         
        super.insert_place(raiz, super.get_place(filho_esq));
        desloca_baixo(filho_direito(filho_esq), filho_esquerdo(filho_direito(raiz)));

        desloca_cima(filho_esquerdo(filho_esquerdo(raiz)), filho_esq); 
    }

    private void rotacao_dir_esq(int raiz) {
        int filho_esq = filho_esquerdo(raiz);
        int nova_raiz = filho_esquerdo(filho_direito(raiz));

        desloca_baixo(filho_esq, filho_esquerdo(filho_esq));
        super.insert_place(filho_esq, super.get_place(raiz));

        desloca_cima(filho_esquerdo(nova_raiz), filho_direito(filho_esquerdo(raiz)));


        super.insert_place(raiz,super.get_place(nova_raiz));
        super.insert_place(nova_raiz, null);
        desloca_cima(filho_direito(nova_raiz), nova_raiz);
    }


     
    private void rotacao_esq_dir(int raiz) {
        int nova_raiz = filho_direito(filho_esquerdo(raiz));

        desloca_baixo(filho_direito(raiz), filho_direito(filho_direito(raiz)));
        super.insert_place(filho_direito(raiz), super.get_place(raiz));

        desloca_cima(filho_direito(nova_raiz), filho_esquerdo(filho_direito(raiz)));

        super.insert_place(raiz, super.get_place(nova_raiz));
        super.insert_place(nova_raiz, null);

        desloca_cima(filho_esquerdo(nova_raiz), nova_raiz);
    }
    

    @Override public void insert(String value) {
        super.insert(value);
        int posicao = super.find_position(value);


         
        int pai = (int) Math.floor((posicao - 1)/2);

         
        while(pai >= 0) {

            int balance = get_balance(pai);
            if(balance > 1 && value.compareTo(super.get_place(filho_esquerdo(pai))) < 0) {
                rotacao_dir(pai);
            }

            else if(balance < -1 && value.compareTo(super.get_place(filho_direito(pai))) > 0) {
                rotacao_esq(pai);
            }

            else if(balance > 1 && value.compareTo(super.get_place(filho_esquerdo(pai))) > 0) {
                rotacao_esq_dir(pai);
            }

            else if(balance < -1 && value.compareTo(super.get_place(filho_direito(pai))) < 0) {
                rotacao_dir_esq(pai);
            }
    
            if(pai == 0)
                pai = -1;
            else 
                pai = (int) Math.floor((pai - 1)/2);
            
        }    
    }


    @Override public boolean remove(String value) {        
        int i = 0;
        int posicao = super.find_position(value);

        if(posicao == -1)
            return false;
        
        super.remove_aux(posicao, 1);
        super.decrease_len();
            
        int pai;
        if(isEmpty(posicao))
            pai = (int) Math.floor((posicao - 1)/2);
        else
            pai = posicao;

        while(pai >= 0) {
            int balance = get_balance(pai);
            if(balance > 1 && get_balance(filho_esquerdo(pai)) >= 0) {
                rotacao_dir(pai);
            }

            else if(balance < -1 && get_balance(filho_direito(pai)) <= 0) {
                rotacao_esq(pai);
            }

            else if(balance > 1 && get_balance(filho_esquerdo(pai)) < 0) {
                rotacao_esq_dir(pai);
            }

            else if(balance < -1 && get_balance(filho_direito(pai)) > 0) {
                rotacao_dir_esq(pai);
            }

            

            if(pai == 0)
                pai = -1;
            else 
                pai = (int) Math.floor((pai - 1)/2);
            
        }

        return true;        
    }
    
}


