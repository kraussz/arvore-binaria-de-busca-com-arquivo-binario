#include "arvore.h"
#include "curso.h"

void escreverArvore(FILE* fb, Arvore* r, int pos) {
    fseek(fb, sizeof(Cabecalho) + sizeof(Arvore) * pos, SEEK_SET);
    fwrite(r, sizeof(Arvore), 1, fb);
}

Arvore* lerArvore(FILE* fb, int pos) {
    Arvore* root = (Arvore*)malloc(sizeof(Arvore));
    fseek(fb, sizeof(Cabecalho) + sizeof(Arvore) * pos, SEEK_SET);
    fread(root, sizeof(Arvore), 1, fb);
    return root;
}

void inserir_em_lote(FILE* fb, FILE* arq) {
    Cabecalho* cab = lerCabecalho(fb);
    Arvore* root = (Arvore*)malloc(sizeof(Arvore));

    root->left = root->right = -1;

        fscanf(arq, "%d;%[^;]%*c%c\n", &root->data.position, root->data.name, &root->data.category);
        printf("%d ", root->data.position);
        printf("%s ", root->data.name);
        printf("%c\n", root->data.category);

        if (buscarProduto_pos(fb, root->data.position, cab->posCabeca) == -1)inserirProduto(fb, root);
    

    free(cab);
    free(root);
}


int buscarProduto_pos(FILE* fb, int cod, int pos) {
    if (pos == -1)
        return -1;
    else {
        Arvore* root = lerArvore(fb, pos);

        if (root->data.position > cod)
            return buscarProduto_pos(fb, cod, root->left);
        else if (root->data.position < cod)
            return buscarProduto_pos(fb, cod, root->right);
        free(root);
    }
    printf("ERRO... CODIGO JA EXISTENTE\n");
    return pos;
}

void inserirProduto(FILE* fb, Arvore* new_node) {
    Cabecalho* cab = lerCabecalho(fb);

    if (cab->posLivre == -1)
        inserir_semNosLivres(fb, new_node, cab->posCabeca);
    else
        inserir_comNosLivres(fb, new_node, cab->posCabeca);

    free(cab);
}

void inserir_semNosLivres(FILE* fb, Arvore* new_node, int pos) {
    Cabecalho* cab = lerCabecalho(fb);

    if (pos == -1) {
        if (vaziaArvore(cab))
            cab->posCabeca = 0;

        escreverArvore(fb, new_node, cab->posTopo);
        cab->posTopo++;
        escreverCabecalho(fb, cab);
    } else {
        Arvore* next_node = lerArvore(fb, pos);

        if (new_node->data.position < next_node->data.position) {
            if (next_node->left == -1) {
                next_node->left = cab->posTopo;
                escreverArvore(fb, next_node, pos);
                inserir_semNosLivres(fb, new_node, -1);
            } else {
                inserir_semNosLivres(fb, new_node, next_node->left);
            }
        } else {
            if (new_node->data.position > next_node->data.position) {
                if (next_node->right == -1) {
                    next_node->right = cab->posTopo;
                    escreverArvore(fb, next_node, pos);
                    inserir_semNosLivres(fb, new_node, -1);
                } else {
                    inserir_semNosLivres(fb, new_node, next_node->right);
                }
            }
        }
        free(next_node);
    }
    free(cab);
}

void inserir_comNosLivres(FILE* fb, Arvore* new_node, int pos) {
    Cabecalho* cab = lerCabecalho(fb);

    if (pos == -1) {
        Arvore* free_node = lerArvore(fb, cab->posLivre);
        escreverArvore(fb, new_node, cab->posLivre);

        if (vaziaArvore(cab))
            cab->posCabeca = cab->posLivre;

        cab->posLivre = free_node->left;
        escreverCabecalho(fb, cab);

        free(free_node);
    } else {
        Arvore* next_node = lerArvore(fb, pos);

        if (new_node->data.position < next_node->data.position) {
            if (next_node->left == -1) {
                next_node->left = cab->posLivre;
                escreverArvore(fb, next_node, pos);
                inserir_comNosLivres(fb, new_node, -1);
            } else {
                inserir_comNosLivres(fb, new_node, next_node->left);
            }
        } else {
            if (new_node->data.position > next_node->data.position) {
                if (next_node->right == -1) {
                    next_node->right = cab->posLivre;
                    escreverArvore(fb, next_node, pos);
                    inserir_comNosLivres(fb, new_node, -1);
                } else {
                    inserir_comNosLivres(fb, new_node, next_node->right);
                }
            }
        }
        free(next_node);
    }
    free(cab);
}

    //Descrição: Imprime a Interface e puxa a função recursiva de impressão da arvore
    //Pré-Condição: Árvore já salva no arquivo binário
    //Pós-Condição: -----------

void imprimir_inOrdem(FILE* fb) {
    Cabecalho* cab = lerCabecalho(fb);

    printf("\n*cursos*\n");

   if(vaziaArvore(cab)) printf("\nNAO HA PRODUTOS...\n");
    else {
        printf("\n%-11s%-55s%-11s\n", "numero", "nome", "area");
    }
imprimir_inOrdem_rec(fb,cab->posCabeca);

        free(cab);
   
}


    //Descrição: Monta a árvore a partir do arquivo e imprime-a do menor número ao maior
    //Pré-Condição: Árvore já existente salva no arquivo binário
    //Pós-Condição: -----------

void imprimir_inOrdem_rec(FILE* fb,int pos){
        if(pos!=-1){
            Arvore* root=lerArvore(fb,pos);
            imprimir_inOrdem_rec(fb,root->left);//imprime primeiro os elementos da esquerda
            printf("%-10d%-55s%-11c\n",root->data.position,root->data.name,root->data.category);//imprime a raiz
            imprimir_inOrdem_rec(fb,root->right);//imprime então os elementos da direita
            free(root);
        }
    }


void cadastrarCurso(FILE* fb){
        Cabecalho* cab=lerCabecalho(fb);
        Arvore* root=(Arvore*)malloc(sizeof(Arvore));

        root->left=root->right=-1;//no ainda nao possui filhos. inicializados como "null"

        printf("Digite o codigo do Curso:\n");
        scanf("%d%*c",&root->data.position);

        

        //não permite inserir um codigo já existente
        if(buscarProduto_pos(fb,root->data.position,cab->posCabeca)==-1){

            printf("Digite o nome do Curso:\n");
            scanf("%[^\n]%*c",&root->data.name);

            printf("Digite o area do Curso:\n");
            scanf("%c%*c",&root->data.category);

            inserirProduto(fb,root);//função recursiva de inserir no arquivo binario
            printf("\nPRODUTO INSERIDO COM SUCESSO...\n");
        }
        else printf("\nCODIGO EXISTENTE: NAO FOI POSSIVEL CONCLUIR O CADASTRO...\n");

        free(cab);
        free(root);
    }