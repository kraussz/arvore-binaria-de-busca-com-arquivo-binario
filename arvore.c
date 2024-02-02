
#include "arvore.h"

/*FILE* initializeBinaryFile(char *arqName) {
    FILE *fb = fopen(arqName, "r+b");
    if(fb == NULL) {
        fb = fopen(arqName, "w+b");
        Cabecalho cab = { -1, 0, -1 };  // Inicializa o cabeçalho
        escreverCabecalho(fb, &cab);
    }
    return fb;
}*/

FILE* initializeBinaryFile(char* file_name){
        FILE* fb=fopen(file_name,"r+b");//tenta abrir o arquivo binário, caso ele exista

        if(fb==NULL){//caso ele não exista, é criado um novo
            fb=fopen(file_name,"w+b");
            inicializarArvore(fb);//se inicializa o cabeçalho
        }

    return fb;
    }

    void inicializarArvore(FILE* fb){
        Cabecalho *cab=(Cabecalho*)malloc(sizeof(Cabecalho));

        cab->posCabeca=-1;//inicializar "cabeca" como "NULL"
        cab->posTopo=0;//indica que a proximo posicao livre como a primeira posicao disponivel
        cab->posLivre=-1;//inicializar lista de nós livres como "NULL"

        escreverCabecalho(fb,cab);//escreve o cabecalho inicializado
        free(cab);//desaloca memória do ponteiro auxiliar
    }

void escreverCabecalho(FILE* fb, Cabecalho* cab) {
    fseek(fb, 0, SEEK_SET);
    fwrite(cab, sizeof(Cabecalho), 1, fb);
}

Cabecalho* lerCabecalho(FILE* fb) {
    Cabecalho *cab = (Cabecalho*)malloc(sizeof(Cabecalho));
    fseek(fb, 0, SEEK_SET);
    fread(cab, sizeof(Cabecalho), 1, fb);
    return cab;
}

/*void inicializarArvore(FILE* fb) {
    Cabecalho cab = { -1, 0, -1 };
    escreverCabecalho(fb, &cab);
}*/

int vaziaArvore(Cabecalho* cab) {
    return (cab->posCabeca == -1);
}

