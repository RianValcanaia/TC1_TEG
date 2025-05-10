#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct no{
    float x;
    float y;
    float z;
}No;

typedef struct dadosSaida{
    float maxDE;
    struct no maxDE_1;
    struct no maxDE_2;

    float minDE;
    struct no minDE_1;
    struct no minDE_2;

    float maxDEN;
    struct no maxDEN_1;
    struct no maxDEN_2;

    float minDEN; 
    struct no minDEN_1;
    struct no minDEN_2;
}Dados_saida;

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
        printf("Número inválido. Digite um número dentro do intervalo [%i, %i]: ", ini, fim);
        limpaBuffer(); 
    }
}

int alocaVertices(struct no **vertices, int alocar){
    (*vertices) = realloc(*vertices, sizeof(No) * alocar);

    if (*vertices == NULL) {
        printf("Erro ao alocar memória. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
        return 0;
    }

    return 1;
}

double calculaDE(struct no A, struct no B){
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2) + pow(A.z - B.z, 2));
}

float normalizaDE(float x, float min, float max){
    return (x - min)/(max - min);
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
            printf("Linha %d inválida. Aperte enter para voltar. ", *totalVertices+1);
            limpaBuffer();
            getchar();
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

int criaGrafo(No *vertices, int qtVertices, struct dadosSaida *saida, int matrizADJ[][qtVertices]){
    float matrizDE[qtVertices][qtVertices];

    float aux;

    if(qtVertices <= 0 || vertices == NULL || saida == NULL) return 0;

    for (int i = 0; i < qtVertices; i++){
        for (int j = 0; j < qtVertices; j++){
            aux = calculaDE(vertices[i], vertices[j]);
            matrizDE[i][j] = aux;

            if ((i == 0 && j == 0) || aux < (*saida).minDE) {
                (*saida).minDE = aux;
                (*saida).minDE_1 = vertices[i];
                (*saida).minDE_2 = vertices[j];
            }
            if ((i == 0 && j == 0) || aux > (*saida).maxDE) {
                (*saida).maxDE = aux;
                (*saida).maxDE_1 = vertices[i];
                (*saida).maxDE_2 = vertices[j];
            }
        }
    }

    for (int i = 0; i < qtVertices; i++){
        for (int j = 0; j < qtVertices; j++){
            aux = normalizaDE(matrizDE[i][j], (*saida).minDE, (*saida).maxDE);
            if (aux <= 0.3) {
                matrizADJ[i][j] = 1;
                
            }
            else matrizADJ[i][j] = 0;

            if ((i == 0 && j == 0) || aux < (*saida).minDEN) {
                (*saida).minDEN = aux;
                (*saida).minDEN_1 = vertices[i];
                (*saida).minDEN_2 = vertices[j];
            }
            if ((i == 0 && j == 0) || aux > (*saida).maxDEN) {
                (*saida).maxDEN = aux;
                (*saida).maxDEN_1 = vertices[i];
                (*saida).maxDEN_2 = vertices[j];
            }
        }
    }  

    return 1;
}


int salvarArquivo(struct dadosSaida saida, int qtVertices, int matrizADJ[][qtVertices]){
    FILE *arquivo_saida = fopen("Grafo.csv", "w");
    FILE *arquivo_saida_python = fopen("Grafo_python.csv", "w");

    if (arquivo_saida == NULL || arquivo_saida_python == NULL){
        printf("Erro ao criar arquivos de saida. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
        return 0;
    }



}

int main(){
    limpaTela();


    int qtVertices = 0, qtAlocada = 10, continuar = 1;
    char nomeArquivo[100];
    No *vertices = NULL;

    Dados_saida saida;

    printf("Digite o nome do arquivo de dados: ");
    scanf("%[^\n]", nomeArquivo);
    limpaBuffer();

    alocaVertices(&vertices, qtAlocada);

    if(carregaArquivo(&vertices, &qtVertices, &qtAlocada, nomeArquivo)){
        printf("\nVertices carregados com sucesso.\n");
    }else{
        printf("\nErro ao carregar o arquivo.\n");
    }

    int matrizADJ[qtVertices][qtVertices];
    
    if(criaGrafo(vertices, qtVertices, &saida, matrizADJ)){
        printf("\nGrafo criado com sucesso.");
    }else {
        printf("\nErro ao criar o grafo.");
    }

    if(salvarArquivo(saida, qtVertices, matrizADJ)){
        printf("\nGrafo e demais dados salvos nos arquivos de saída.\n");
    }else{
        printf("\nErro ao salvar grafo e demais dados no arquivo de saída.\n");
    }


    while (continuar){
        limpaTela();
        switch (opcao){
            case 1:
                carregaArquivo()
            break;
            case 2:
            break;
            case 3;
            continuar = 0;
            break;
        }
    }

    free(vertices);
    return 0;
}