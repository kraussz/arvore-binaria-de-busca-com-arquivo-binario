#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "curso.h"
#include "arvore.h"
#include "disciplina.h"
#include "professor.h"
#include "matricula.h"



int main()
{
  
  FILE *fbCurso = initializeBinaryFile("curso.bin");
  FILE *fbDisciplina = initializeBinaryFile("disciplina.bin");
  FILE *fbProfessor = initializeBinaryFile("professor.bin");
  FILE *fbMatricula = initializeBinaryFile("Matricula.bin");
    int imprime;
    int escolha;

    char categoria;
    int cadastro;
    char txt[100];
    char nome_arquivo[100];
    


  // Abre o arquivo
 


    while (escolha != 0)
    {
        
        printf("\n1-cadastrar\n2-ler arquivo texto\n 3-printar\n 4-remover distribuicao\n 5-remover manual\n 0-sair\n");

        scanf("%d%*c", &escolha);

        switch (escolha)
        {

        case 1:
            printf("1-cadastrar curso\n2-cadastrar disciplina\n3-cadastrar professor\n4-cadastrar distribuicao\n");
            scanf("%d%*c", &cadastro);
            
            
            if(cadastro == 1){
            cadastrarCurso(fbCurso);
            }
            
            if(cadastro == 2){
            cadastrarDisciplina(fbDisciplina);       
            }
            
            if(cadastro == 3){
            cadastrarProfessor(fbProfessor);
            }
            
            if(cadastro == 4){
              cadastrarMatricula(fbMatricula);
            {
                
            }
            }
            

            break;

        case 2:

        printf("Digite o nome do arquivo: ");
        scanf("%[^\n]%*c", nome_arquivo);

        // Abre o arquivo
        FILE *arq = fopen(nome_arquivo, "r");


        while(fscanf(arq, "%c;", &categoria) != EOF){
             if(categoria == 'C'){

             inserir_em_lote(fbCurso,arq);
               
            }
            if(categoria == 'D'){
            
             inserir_em_lote_disc(fbDisciplina,arq);

            }

            if(categoria == 'P'){
                
             inserir_em_lote_prof(fbProfessor,arq);

            }
            if(categoria == 'M'){
              inserir_em_lote_Mat(fbMatricula,arq);
            }
          if(categoria == 'R'){
           
            remover_em_lote(fbMatricula,arq);
}
        }

        fclose(arq);
            break;

        case 3:
            printf("1-imprimir curso\n2-imprimir disciplina\n3-imprimir professor\n4-imprimir distribuicao\n5-imprimir em arvore\n");
            scanf("%d",&imprime);
            if(imprime == 1){
            imprimir_inOrdem(fbCurso);
            }
            if(imprime == 2){
            imprimir_inOrdemD(fbDisciplina);
            }
            if(imprime == 3){
            imprimir_inOrdemP(fbProfessor);
            }
            if(imprime == 4){
           imprimir_inOrdemM(fbMatricula);
            }
            if(imprime == 5){
                imprimir_arvore(fbMatricula);
            }
            break;

        case 4:
        remover_manual(fbMatricula);
        
        
      break;
        case 5:

imprimir_listaLivres(fbMatricula);

}
    

  
        }
    
        
    


    return 0;
    
    
    }