#include <stdio.h>
#include <stdlib.h>

struct aluno{
    char nome[50];
    int matricula;
    float nota;
};
typedef struct aluno ALUNO;

void apresentarinterface(ALUNO* lista, int qtd);
void escolherfazer(ALUNO* lista, int qtd, int escolher);
void lerbancodedados(ALUNO** lista, int* qtd);
void cadastrar(ALUNO** lista, int* qtd);
void remover(ALUNO** lista, int* qtd);
void listaralunos(ALUNO* lista, int qtd);

void lerbancodedados(ALUNO** lista, int* qtd){
    FILE* f;
    f = fopen("aluno.txt", "r");
    if(f == 0){
        printf("Erro na leitura do bando de dados");
        exit(1);
    }
    
    fscanf(f,"%i", qtd);

    *lista = (ALUNO*)malloc(*qtd * sizeof(ALUNO));
    
    for(int i = 0; i < *qtd; i++){
        fscanf(f,"%49s %i %f", (*lista)[i].nome, &(*lista)[i].matricula, &(*lista)[i].nota);
    }

    fclose(f);
}
