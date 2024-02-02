#include "Arvore.h"
#include "Matricula.h"
#include "curso.h"

void escreverArvore_Matricula(FILE* fb, Arvore_Matricula* r, int pos) {
    fseek(fb, sizeof(Cabecalho) + sizeof(Arvore_Matricula) * pos, SEEK_SET);
    fwrite(r, sizeof(Arvore_Matricula), 1, fb);
}

Arvore_Matricula* lerArvore_Matricula(FILE* fb, int pos) {
    Arvore_Matricula* root = (Arvore_Matricula*)malloc(sizeof(Arvore_Matricula));
    fseek(fb, sizeof(Cabecalho) + sizeof(Arvore_Matricula) * pos, SEEK_SET);
    fread(root, sizeof(Arvore_Matricula), 1, fb);
    return root;
}

void inserir_em_lote_Mat(FILE* fb, FILE* arq) {
    Cabecalho* cab = lerCabecalho(fb);
    Arvore_Matricula* root = (Arvore_Matricula*)malloc(sizeof(Arvore_Matricula));
    char aux[10];

    root->esq = root->dir = -1;

        fscanf(arq,"%d;%d;%d\n", &root->Mat.code, &root->Mat.ano,&root->Mat.codprof);
        printf("%d\n ", root->Mat.code);
        printf("%d\n", root->Mat.ano);
        printf("%d\n", root->Mat.codprof);

        if(root->Mat.code < 10){
            sprintf(aux, "%d0%d", root->Mat.ano, root->Mat.code);
            root->Mat.tracker = atoi(aux);
            printf("tracker = %d\n", root->Mat.tracker);
        }
        else{
            sprintf(aux, "%d%d", root->Mat.ano, root->Mat.code);
            root->Mat.tracker = atoi(aux);
            printf("tracker = %d\n", root->Mat.tracker);
        }

        inserirMatricula(fb, root);
        //inserirArvore_bin(fb, root);
    

    free(cab);
    free(root);
}

int inserirArvore_bin(FILE* fb, Arvore_Matricula* root){
        Cabecalho* cab = lerCabecalho(fb);
        int insertion_pos;

        if(cab->posLivre == -1){
            insertion_pos = cab->posTopo;
            escreverArvore_Matricula(fb, root, cab->posTopo);
            cab->posTopo++;
        }
        else{
            insertion_pos = cab->posLivre;
            Arvore_Matricula* rootLoose = lerArvore_Matricula(fb, cab->posLivre);
            escreverArvore_Matricula(fb, root, cab->posLivre);
            cab->posLivre = rootLoose->esq;
            free(rootLoose);
        }

        if(vaziaArvore(cab)) cab->posCabeca = insertion_pos;
        
        escreverCabecalho(fb, cab);
        
        free(cab);

        return insertion_pos;
    }

    int inserirArvore(FILE* fb, Arvore_Matricula* new_root, int pos){
        if(pos == -1){ //significa que a arvore está vazia ou que foi encontrada uma posição livre a ser inserida o novo nós
            int insertion_pos = inserirArvore_bin(fb, new_root);
            return insertion_pos;
        }
        else{
            Arvore_Matricula* current_root = lerArvore_Matricula(fb, pos);

            if(new_root->Mat.tracker < current_root->Mat.tracker){
                current_root->esq = inserirArvore(fb, new_root, current_root->esq);
                escreverArvore_Matricula(fb, current_root, pos);
            }
            else{
                current_root->dir = inserirArvore(fb, new_root, current_root->dir);
                escreverArvore_Matricula(fb, current_root, pos);
            }

            free(current_root);
        }
        return pos;
    }


int buscarMatricula_pos(FILE* fb, int cod, int pos) {
    if (pos == -1) return -1;
    else {
        Arvore_Matricula* root = lerArvore_Matricula(fb, pos);

        if (root->Mat.tracker > cod) return buscarMatricula_pos(fb, cod, root->esq);
        else if (root->Mat.tracker < cod) return buscarMatricula_pos(fb, cod, root->dir);
        
        free(root);
    }
    //printf("ERRO... CODIGO NAO ENCONTRADO\n");
    return pos;
}

void inserirMatricula(FILE* fb, Arvore_Matricula* new_node) {
    Cabecalho* cab = lerCabecalho(fb);

    if (cab->posLivre == -1)
        inserir_semNosLivresMat(fb, new_node, cab->posCabeca);
    else
        inserir_comNosLivresMat(fb, new_node, cab->posCabeca);

    free(cab);
}

void inserir_semNosLivresMat(FILE* fb, Arvore_Matricula* new_node, int pos) {
    Cabecalho* cab = lerCabecalho(fb);

    if (pos == -1) {
        if (vaziaArvore(cab)) cab->posCabeca = 0;
        escreverArvore_Matricula(fb, new_node, cab->posTopo);
        cab->posTopo++;
        escreverCabecalho(fb, cab);
    } else {
        Arvore_Matricula* next_node = lerArvore_Matricula(fb, pos);

        // Comparação apenas por code
        if (new_node->Mat.tracker < next_node->Mat.tracker) {
            if (next_node->esq == -1) {
                next_node->esq = cab->posTopo;
                escreverArvore_Matricula(fb, next_node, pos);
                inserir_semNosLivresMat(fb, new_node, -1);
            } else {
                inserir_semNosLivresMat(fb, new_node, next_node->esq);
            }
        } else {
            if (next_node->dir == -1) {
                next_node->dir = cab->posTopo;
                escreverArvore_Matricula(fb, next_node, pos);
                inserir_semNosLivresMat(fb, new_node, -1);
            } else {
                inserir_semNosLivresMat(fb, new_node, next_node->dir);
            }
        }
        free(next_node);
    }
    free(cab);
}


void inserir_comNosLivresMat(FILE* fb, Arvore_Matricula* new_node, int pos) {
    Cabecalho* cab = lerCabecalho(fb);

    if (pos == -1) {
        Arvore_Matricula* free_node = lerArvore_Matricula(fb, cab->posLivre);
        escreverArvore_Matricula(fb, new_node, cab->posLivre);

        if (vaziaArvore(cab))
            cab->posCabeca = cab->posLivre;

        cab->posLivre = free_node->esq;
        escreverCabecalho(fb, cab);

        free(free_node);
    } else {
        Arvore_Matricula* next_node = lerArvore_Matricula(fb, pos);

        if (new_node->Mat.tracker < next_node->Mat.tracker) {
            if (next_node->esq == -1) {
                next_node->esq = cab->posLivre;
                escreverArvore_Matricula(fb, next_node, pos);
                inserir_comNosLivresMat(fb, new_node, -1);
            } else {
                inserir_comNosLivresMat(fb, new_node, next_node->esq);
            }
        } else {
            if (new_node->Mat.code > next_node->Mat.code) {
                if (next_node->dir == -1) {
                    next_node->dir = cab->posLivre;
                    escreverArvore_Matricula(fb, next_node, pos);
                    inserir_comNosLivresMat(fb, new_node, -1);
                } else {
                    inserir_comNosLivresMat(fb, new_node, next_node->dir);
                }
            }
        }
        free(next_node);
    }
    free(cab);
}

    //Descrição: Imprime a Interface e puxa a função recursiva de impressão da Arvore_Matricula
    //Pré-Condição: Árvore já salva no arquivo binário
    //Pós-Condição: -----------

void imprimir_inOrdemM(FILE* fb) {
    Cabecalho* cab = lerCabecalho(fb);

    printf("\n*Matricula*\n");

   if(vaziaArvore(cab)) printf("\nNAO HA MatriculaS...\n");
    else {
        printf("\n%-11s%-55s%-11s\n", "numero", "ano","codMat");
    }
    imprimir_inOrdem_recM(fb,cab->posCabeca);

        free(cab);
   
}


    //Descrição: Monta a árvore a partir do arquivo e imprime-a do menor número ao maior
    //Pré-Condição: Árvore já existente salva no arquivo binário
    //Pós-Condição: -----------

void imprimir_inOrdem_recM(FILE* fb,int pos){
        if(pos!=-1){
            Arvore_Matricula* root=lerArvore_Matricula(fb,pos);
            imprimir_inOrdem_recM(fb,root->esq);//imprime primeiro os elementos da esquerda
            printf("%-10d%-55d%-10d\n",root->Mat.code,root->Mat.ano,root->Mat.codprof);//imprime a raiz
            imprimir_inOrdem_recM(fb,root->dir);//imprime então os elementos da direita
            free(root);
            
        }
    }


void cadastrarMatricula(FILE* fb){
        Cabecalho* cab=lerCabecalho(fb);
        Arvore_Matricula* root=(Arvore_Matricula*)malloc(sizeof(Arvore_Matricula));

        root->esq=root->dir=-1;//no ainda nao possui filhos. inicializados como "null"

        printf("Digite o codigo do Matricula:\n");
        scanf("%d%*c",&root->Mat.code);

        //não permite inserir um codigo já existente
        if(buscarMatricula_pos(fb,root->Mat.code,cab->posCabeca)==-1){

            printf("Digite o ano da Matricula:\n");
            scanf("%d%*c",&root->Mat.ano);

            printf("Digite o codMat da Matricula:\n");
            scanf("%d%*c",&root->Mat.codprof);

            inserirMatricula(fb,root);//função recursiva de inserir no arquivo binario
            printf("\nMatricula INSERIDO COM SUCESSO...\n");
        }
        else printf("\nCODIGO EXISTENTE: NAO FOI POSSIVEL CONCLUIR O CADASTRO...\n");

        free(cab);
        free(root);
    }

    void remover_em_lote(FILE *fb, FILE *fr){
        Cabecalho *cab=lerCabecalho(fb);
        int cod, ano, track;
        char aux[10];

        fscanf(fr,"%d;%d\n",&cod,&ano);

        printf("AQUII:::: %d %d\n", cod, ano);

         if(cod < 10){
            sprintf(aux, "%d0%d", ano, cod);
            track = atoi(aux);
            printf("tracker = %d\n", track);
        }
        else{
            sprintf(aux, "%d%d", ano, cod);
            track = atoi(aux);
            printf("tracker = %d\n", track);
        }
    
        removerNo(fb,cab->posCabeca, track);

        free(cab);
    }

  int removerNo(FILE *fb,int pos,int cod){
        Cabecalho* cab=lerCabecalho(fb);
        printf("POS EH %d\n",pos);
        printf("O COD EH %d\n",cod);

        if(pos == -1){
            if(vaziaArvore(cab)) printf("\nNAO HA PRODUTOS: ");
            else printf("\nCODIGO INEXISTENTE: ");
            printf("NAO FOI POSSIVEL REALIZAR A REMOCAO...\n");
            return -1;
        }//se posCabeca for -1 (arvore vazia) ou se root->(esq || drt) for -1 (ramos vazios)
        else{
            Arvore_Matricula* root=lerArvore_Matricula(fb,pos);
            printf("CHEGAMOS AQUI\n");
            if(root->Mat.tracker>cod){//todos os codigos menores que a raiz se encontram a esquerda
            printf("CHEGAMOS AQUI22222IIII\n");
                root->esq=removerNo(fb,root->esq,cod);//pode receber novamente sua propria posicao esquerda ou -1 (ramo-folha removido)
                escreverArvore_Matricula(fb,root,pos);
            }
            else{
                if(root->Mat.tracker < cod){//todos os codigos maiores que a raiz se encontram a direita
                    printf("CHEGAMOS AQUIIIIIIIIIIIII\n");
                    root->dir=removerNo(fb,root->dir,cod);//pode receber novamente sua propria posicao direito ou -1 (ramo-folha removido)
                    escreverArvore_Matricula(fb,root,pos);
                }
                else{//nó encontrado
                    printf("CHEGAMOS ACA\n");
                    if(root->esq==-1 && root->dir==-1){
                    //nó folha. esse é o nó que será removido
                    //encadeia-se a lista de nós livres
                        if(pos==cab->posCabeca) cab->posCabeca=-1;//árvore fica vazia
                        root->esq=root->dir=cab->posLivre;
                        cab->posLivre=pos;
                        escreverCabecalho(fb,cab);//escreve o cabecalho atualizado
                        escreverArvore_Matricula(fb,root,pos);
                        printf("%d",pos);
                        pos=-1;//sinaliza que essa folha foi removida e -1 (null) retorna para sua raiz imediata
                        printf("\nPRODUTO REMOVIDO COM SUCESSO...\n");
                    }
                    else{
                        if(root->esq == -1){//possui apenas ramo direito
                            printf("achamos ele!!!!!!!!!!!!!\n");
                            int cod_min=minimo(fb,root->dir);//recebe o menor codigo do ramo direito
                            trocar_info(fb,pos,buscarMatricula_pos(fb,cod_min,cab->posCabeca));
                            root=lerArvore_Matricula(fb,pos);//lê a nova arvore que teve suas informacoes trocacadas
                            root->dir=removerNo(fb,root->dir,cod_min);//remove o no minimo cujo as informacoes foram copiadas
                            escreverArvore_Matricula(fb,root,pos);//escreve novamente a arvore atualizada
                        }
                        else{//possui apenas ramo esquerdo ou dois ramos
                            printf("CHEGAMOS AQUEI\n");
                            int cod_max=maximo(fb,root->esq);//recebe o maior codigo do ramo esquerdo
                            trocar_info(fb,pos,buscarMatricula_pos(fb,cod_max,cab->posCabeca));
                            root=lerArvore_Matricula(fb,pos);//lê a nova arvore que teve suas informacoes copiadas do no maximo
                            root->esq=removerNo(fb,root->esq,cod_max);//remove o no minimo cujo as informacoes foram copiadas
                            escreverArvore_Matricula(fb,root,pos);//escreve novamente a arvore atualizada
                        }
                    }
                }
            }
            free(root);
        }
        free(cab);

    return pos;
    }



void remover_manual(FILE* fb){
  Cabecalho *cab=lerCabecalho(fb);
        int cod, ano, track;
        char aux[10];
printf("informe o codigo e o ano de qual deseja remover\n");
printf("informe o ano:\n");

        scanf("%d",&ano);
        printf("informe o cod:\n");
        scanf("%d",&cod);
        printf("AQUII:::: %d %d\n", cod, ano);

         if(cod < 10){
            sprintf(aux, "%d0%d", ano, cod);
            track = atoi(aux);
            printf("tracker = %d\n", track);
        }
        else{
            sprintf(aux, "%d%d", ano, cod);
            track = atoi(aux);
            printf("tracker = %d\n", track);
        }
        removerNo(fb,cab->posCabeca, track);

}


 int maximo(FILE* fb,int pos){
        Arvore_Matricula* root=lerArvore_Matricula(fb,pos);

        int cod=root->Mat.tracker;
        pos=root->dir;//faz a busca do ultimo nó, passando apenas pelos ramos da direito das sub-arvores
        free(root);

        if(pos!=-1) cod=maximo(fb,pos);

    return cod;
    }

      int minimo(FILE* fb,int pos){
        Arvore_Matricula* root=lerArvore_Matricula(fb,pos);

        int cod=root->Mat.tracker;
        pos=root->esq;//faz a busca do ultimo nó, passando apenas pelos ramos da esqueda das sub-arvores
        free(root);

        if(pos!=-1) cod=minimo(fb,pos);

    return cod;
    }

     void trocar_info(FILE* fb,int pos_dest,int pos_source){
    /*faz a troca de informacoes entre ROOT (dest) e COD_(MAX || MIN) (source), utilizando-se de uma ARVORE-AUXILIAR,
    pois o nó que será verdadeiramente desencadeado da árvore é um nó-folha
    (maior da subarvore esquerda ou o menor da subarvore direita)
    e para não ocorrer perda de informações desse nó-folha, é feita uma troca de informações*/
    
        Arvore_Matricula* dest=lerArvore_Matricula(fb,pos_dest);
        Arvore_Matricula* source=lerArvore_Matricula(fb,pos_source);
        Arvore_Matricula* aux=(Arvore_Matricula*)malloc(sizeof(Arvore_Matricula));

        aux->Mat.codprof=dest->Mat.codprof;
        aux->Mat.ano=dest->Mat.ano;
     
        dest->Mat.code=source->Mat.code;
        dest->Mat.codprof=source->Mat.codprof;
        dest->Mat.ano=source->Mat.ano;
        dest->Mat.tracker=source->Mat.tracker;
  
        source->Mat.codprof=aux->Mat.codprof;
        source->Mat.ano=aux->Mat.ano;   
             

        escreverArvore_Matricula(fb,dest,pos_dest);
        escreverArvore_Matricula(fb,source,pos_source);

        free(dest);
        free(source);
        free(aux);
    }

        void imprimir_listaLivres(FILE *fb){
        Cabecalho* cab=lerCabecalho(fb);

        printf("\n*LISTA DE NOS LIVRES (REMOVIDOS)*\n");

        //verificação necessária apenas para a estética da função
        if(cab->posLivre==-1) printf("\nNAO HA NOS LIVRES...\n");

        imprimir_nosLivres(fb,cab->posLivre);

        free(cab);
    }

    void imprimir_nosLivres(FILE *fb,int pos){
        if(pos!=-1){
            Arvore_Matricula* root=lerArvore_Matricula(fb,pos);

            printf("-> %.2d: %d\n",pos,root->Mat.tracker);
            imprimir_nosLivres(fb,root->esq);//posicão esquerda e direita são iguais, pois é uma lista, não uma árvore

            free(root);
        }
    }

      void imprimir_em_arvore(Lista* l,int altura_arvore){
        if(l!=NULL){
            Lista* aux=l;
            int altura_no=aux->h_node;//altura atual em que os nós serão impressos

            espaco(altura_arvore,altura_no);
            while(aux!=NULL){
                printf("|%d|",aux->cod);
                if(aux->prox!=NULL && aux->h_node != aux->prox->h_node){//pula uma linha ao mudar o nível do nó
                    altura_no=aux->prox->h_node;
                    printf("\n");
                    espaco(altura_arvore,altura_no);
                }
                aux=aux->prox;
            }
            printf("\n");
        }
    }

    void espaco(int altura_arvore,int altura_no){
        for(int i=altura_arvore-altura_no;i>=0;i--) printf("  ");
    }

      Lista* inserir_ordenado(Lista* l,int cod,int h_node){
        if(l==NULL || l->h_node > h_node){
            Lista* aux=(Lista*)malloc(sizeof(Lista));
            aux->cod=cod;
            aux->h_node=h_node;
            aux->prox=l;
            return aux;
        }
        else{
            l->prox=inserir_ordenado(l->prox,cod,h_node);
            return l;
        }
    }

      Lista* percorrer_arvore(FILE* fb,Lista* l,int pos,int h_node){
        if(pos!=-1){
            Arvore_Matricula* root=lerArvore_Matricula(fb,pos);

            l=inserir_ordenado(l,root->Mat.tracker,h_node);//insere os códigos na lista de maneira ordenada pela altura do nó
            percorrer_arvore(fb,l,root->esq,h_node+1);//incrementa a altura do nó, passando para o próximo nível
            percorrer_arvore(fb,l,root->dir,h_node+1);//incrementa a altura do nó, passando para o próximo nível

            free(root);
        }
    return l;
    }

    void imprimir_arvore(FILE* fb){
        Cabecalho* cab=lerCabecalho(fb);
        Lista* l=NULL;//inicialização padrão de lista

        printf("\n*ARVORE BINARIA*\n\n");

        //verificação feita apenas para a estética da interface do programa
        if(vaziaArvore(cab)) printf("NAO HA PRODUTOS...\n");

        l=percorrer_arvore(fb,l,cab->posCabeca,0);//passa a arvore para uma lista encadeada, ordenada pela altura do nó
        imprimir_em_arvore(l,altura_arvore(fb,cab->posCabeca));//imprime no formato de árvore binária

        free(cab);
        liberar_lista(l);
    }

       int altura_arvore(FILE* fb,int pos){
        if(pos==-1) return -1;
        else{
            Arvore_Matricula* root=lerArvore_Matricula(fb,pos);

            int h_esq=altura_arvore(fb,root->esq);//recebe a altura da subarove esquerda
            int h_dir=altura_arvore(fb,root->dir);//recebe a altura da subarove direita
            return (h_esq > h_dir) ? h_esq+1 : h_dir+1;//compara a altura entre os ramos. o ramo maior representa a altura

            free(root);
        }
    }

      void liberar_lista(Lista *l){
        if(l!=NULL){
            liberar_lista(l->prox);
            free(l);
        }
    }