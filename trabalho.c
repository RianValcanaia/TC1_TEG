#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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

int alocaVertices(struct no **vertices, int alocar){
    (*vercices) = realloc(*vertices, sizeof(No) * alocar);

    if (*vertices == NULL) {
        printf("Erro ao alocar memória. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
        return 0;
    }

    return 1;
}

double calculaDE(struct no A, struct no B){
    return sqrt(
        pow(A.x - B.x, 2) +
        pow(A.y - B.y, 2) +
        pow(A.z - B.z, 2)
    );
}

float normalizaDE(float *x, float min, float max){
    return (*x - min)/(max - min);
}

// Funcoes primarias
int carregaArquivo(struct no **vertices, int *qtAlocada, int *totalVertices, char nomeArquivo[100]){
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL){
        printf("Arquivo não encontrado, aperte enter para voltar. ");
        limpaBuffer();
        getchar();
        return 0;
    }

    char linha[100];
    float x,y,z;

    while (fgets(linha, sizeof(linha), arquivo)){
        if(sscanf(linha, "%f,%f,%f", &x, &y, &z) == 3){
            if (*totalVertices >= *qtAlocada){
                *qtAlocada += 10;
                alocaVertices(vertices, *qtAlocada);
            }

            (*vertices)[*totalVertices].x = x;
            (*vertices)[*totalVertices].y = y;
            (*vertices)[*totalVertices].z = z;

            (*totalVertices)++;
        }else{
            pritf("Linha %d inválida. Aperte enter para voltar. ", *totalVertices+1);
            limpaBuffer();
            getchar();
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

int criaGrafo(struct no **vertices, int qtVertices){
    float matrizDE[qtVertices][qtVertices];
    int matrizADJ[qtVertices][qtVertices];

    float minDE, maxDE, aux, minDEN, maxDEN;
    No maxDE1, maxDE2, minDE1, minDE2, maxDEN1, maxDEN2, minDEN1, minDEN2;

    int qtConexos = 0; //aqui falta respectivos tamanhos, vou ter que rodar uma BFS e DFS;

    for (int i = 0; i < qtVertices; i++){
        for (int j = 0; j < qtVertices; j++){
            aux = calculaDE((*vertices)[i], *(vercices)[j]);
            matrizDE[i][j] = aux;

            if ((i = 0 && j == 0) || aux < minDE) {
                minDE = aux;
                minDE1 = (*vercices)[i];
                minDE2 = (*vertice)[j];
            }
            if ((i = 0 && j == 0) || aux > maxDE) {
                maxDE = aux;
                maxDE1 = (*vercices)[i];
                maxDE2 = (*vertice)[j];
            }
        }
    }

    for (int i = 0; i < qtVertices; i++){
        for (int j = 0; j < qtVertices; j++){
            aux = normalizaDE(matrizDE[i][j], minDE, maxDE)
            if (aux <= 0.3) {
                matrizADJ[i][j] = 1;
            }
            else matrizADJ[i][j] = 0;

            if ((i = 0 && j == 0) || aux < minDEN) {
                minDEN = aux;
                minDEN1 = (*vercices)[i];
                minDEN2 = (*vertice)[j];
            }
            if ((i = 0 && j == 0) || aux > maxDEN) {
                maxDEN = aux;
                maxDEN1 = (*vercices)[i];
                maxDEN2 = (*vertice)[j];
            }
        }
    }  
}



/*
void salvaArquivo(){

}

*/


int main(){
    limpaTela();

    int totalVertices = 0, qtAlocada = 10;
    char nomeArquivo[100];
    No *vertices = NULL;

    printf("Digite o nome do arquivo de dados: ");
    scanf("%[^\n]", nomeArquivo);
    limpaBuffer();

    alocaVertices(&vertices, qtAlocada);

    if(carregaArquivo(&vertice, &totalVertices, &qtAlocada, nomeArquivo)){
        printf("\nVertices carregados com sucesso.\n");
    }else{
        printf("\nErro ao carregar o arquivo.\n");
    }

    

    //salvaArquivo(nomeArquivo);

    free(vertices);
    limpaTela();
    return 0;
}