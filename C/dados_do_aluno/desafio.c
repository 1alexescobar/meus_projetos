#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "desafio.h"

ALUNO a;

void apresentarinterface(ALUNO* lista, int qtd){
    int escolher;
    printf("\n\nSeja bem vindo! O que deseja fazer agora?\n\n");
    printf("1.Cadastrar novo aluno\n");
    printf("2.Remover aluno\n");
    printf("3.Listar todos os alunos\n");
    printf("4.Verifiar se o aluno ja esta cadastrado\n");
    printf("5.Ordenar os alunos\n");
    printf("6.Calcular a media dos alunos cadastrados\n");
    printf("7.Sair.\n");

    scanf("%i", &escolher);
    escolherfazer(lista, qtd, escolher);
}

void escolherfazer(ALUNO* lista, int qtd, int escolher){
    switch(escolher){
        case 1:
            cadastrar(&lista, &qtd);
            break;
        case 2:
            remover(&lista, &qtd); //pela matricula
            break;
        case 3:
            listaralunos(lista, qtd);
            break;
        case 4:
            //verificar(); //pelo nome
            break;
        case 5:
            //ordenar(); //pelo numero de matricula
            break;
        case 6:
            //cacularmedia();
            break;
        case 7:
            printf("\nOk. Saindo do programa\n");
            if(lista != 0){
                free(lista);
            }
            break;
        default:
            printf("\nOpção inválida! Tente novamente.\n");
            apresentarinterface(lista, qtd);
    }
}

void cadastrar(ALUNO** lista, int* qtd){
    printf("Digite o nome: ");
    scanf(" %49s", a.nome);
    printf("Digite o numero de matricula: ");
    scanf(" %i", &a.matricula);
    printf("Digite a nota do aluno: ");
    scanf(" %f", &a.nota);
    
    FILE* f;
    f = fopen("aluno.txt", "r+");
    if(f == 0){
        printf("Erro na leitura do bando de dados");
        exit(1);
    }

    *qtd++;

    *lista = realloc(*lista, (*qtd) * sizeof(ALUNO));
    (*lista)[(*qtd) - 1] = a;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%i", *qtd);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s %i %.1f", a.nome, a.matricula, a.nota);

    fclose(f);

    printf("\n");
    apresentarinterface(*lista, *qtd);
}

void remover(ALUNO** lista, int* qtd){
    int matricula;
    printf("Digite o numero de matricula do aluno:\n");
    scanf("%i", &matricula);

    for(int i = 0; i < qtd; i++){
        if((*lista)[i].matricula = matricula){
            
        }
    }
}

void listaralunos(ALUNO* lista, int qtd){
    for(int i = 0; i < qtd; i++){
        printf("nome: %s - matricula: %i - nota: %.2f\n", lista[i].nome, lista[i].matricula, lista[i].nota);
    }
    printf("\n aperte qualquer tecla para voltar ao menu. ");
    char t;
    scanf("%s", t);
    apresentarinterface(lista, qtd);
}

int main(){
    ALUNO* lista = 0;
    int qtd = 0;
    lerbancodedados(&lista, &qtd);
    apresentarinterface(lista, qtd);
}
