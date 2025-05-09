#include<stdio.h>
#include<stdlib.h>
#include<fstream.h>

struct no{
    float x;
    float y;
    float z;
}No;

// Funcoes secundarias
void limpaTela(){
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}

void limpaBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void entrada(int ini, int fim, int *num){
    while (scanf("%i", num) != 1 && *num < ini && *num > fim){
        printf("Número inválido. Digite um número dentro do intervalo [%i, %i]: " ini, fim);
        limpaBuffer(); 
    }
}

void 

// Funcoes primarias
int carregaArquivo(struct no **vertices, char nomeArquivo[100]){
    FILE *arquivo = fopen(nomeArquivo, "rt");

    if (arquivo == NULL){
        printf("Arquivo não encontrado, aperte enter para voltar. ");
        limpaBuffer();
        getchar();
        return 0;
    }

    
    
}

void salvaArquivo(){

}


int main(){
    limpaTela();

    char nomeArquivo[100];
    printf("Digite o nome do arquivo de dados: ");
    scanf("%[^\n]", nomeArquivo);

    No *vertices = NULL;

    carregaArquivo(&vertice, nomeArquivo);

    


    salvaArquivo(nomeArquivo);
    limpaTela();
    return 0;
}