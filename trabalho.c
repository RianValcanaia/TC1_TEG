#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

typedef struct no{
    int indice;
    float x, y, z;
}No;

typedef struct info_grafo{
    int totalVertices;
    float maxDE, minDE, maxDEN, minDEN; 
    struct no maxDE_1, maxDE_2;
    struct no minDE_1, minDE_2;
    struct no maxDEN_1, maxDEN_2;
    struct no minDEN_1, minDEN_2;
}Info_grafo;

// FUNCOES SECUNDÁRIAS
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
    while (scanf("%i", num) != 1 || *num < ini || *num > fim){
        printf("Número inválido. Digite um número dentro do intervalo [%i, %i]: ", ini, fim);
        limpaBuffer(); 
    }
}

int alocaVertices(struct no **vertices, int alocar){
    No *temp = realloc(*vertices, sizeof(No) * alocar);
    if (temp == NULL) {
        printf("Erro ao alocar memória. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
        return 0;
    }
    *vertices = temp; // Só atualize o ponteiro original após sucesso
    return 1;
}

double calculaDE(struct no A, struct no B){
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) + (A.z - B.z)*(A.z - B.z));
}

float normalizaDE(float x, float min, float max){
    if (max == min) return 0;
    return (x - min)/(max - min);
}

int **alocaMatriz(int tam){
    int **matriz = malloc(sizeof(int*) * tam);
    if (matriz == NULL) return NULL;

    for (int i = 0; i < tam; i++){
        matriz[i] = malloc(sizeof(int) * tam);
        if (matriz[i] == NULL){
            for (int j = 0; j < i; j++) free(matriz[j]);
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

void liberaMatriz(int **matriz, int tam){
    if(matriz == NULL) return;
    for(int i = 0; i < tam; i++) free(matriz[i]);
    free(matriz);
}

void removePasta(const char *caminho){
    DIR* d = opendir(caminho);
    struct dirent* dir;
    char filepath[512];

    if (!d) return;

    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;

        snprintf(filepath, sizeof(filepath), "%s/%s", caminho, dir->d_name);
        remove(filepath);
    }

    closedir(d);
    rmdir(caminho);
}

void criaPasta(const char* caminho) {
    struct stat st = {0};

    if (stat(caminho, &st) == 0) {
        removePasta(caminho);
    }

    mkdir(caminho, 0777);
}

// FUNCOES PRIMÁRIAS
int carregaArquivo(struct no **vertices, int *qtAlocada, int *totalVertices, char nomeArquivo[100]){
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL){
        printf("\n\u274C Arquivo não encontrado, aperte enter para voltar. ");
        getchar();
        return 0;
    }

    char linha[100];
    float x,y,z;

    while (fgets(linha, sizeof(linha), arquivo)){
        if(sscanf(linha, "%f,%f,%f", &x, &y, &z) == 3){
            if (*totalVertices >= *qtAlocada){
                *qtAlocada += 10;
                if (!alocaVertices(vertices, *qtAlocada)) return 0;
            }

            (*vertices)[*totalVertices].indice = (*totalVertices);
            (*vertices)[*totalVertices].x = x;
            (*vertices)[*totalVertices].y = y;
            (*vertices)[*totalVertices].z = z;

            (*totalVertices)++;
        }else{
            printf("\n\u274C Linha %d inválida. Aperte enter para voltar. ", *totalVertices+1);
            limpaBuffer();
            getchar();
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

int criaGrafo(No *vertices, int qtVertices, struct info_grafo *infos, int ***matrizADJ){
    float matrizDE[qtVertices][qtVertices];

    float aux;

    if(qtVertices <= 0 || vertices == NULL || infos == NULL) return 0;

    *matrizADJ = alocaMatriz(qtVertices);

    if (*matrizADJ == NULL){
        printf("\n\u274C Erro ao alocar memória. Aperte enter para voltar. ");
        limpaBuffer();
        getchar();
        return 0;
    }

    infos->totalVertices = qtVertices;
    infos->minDE = infos->minDEN = FLT_MAX;
    infos->maxDE = infos->maxDEN = -FLT_MAX;

    for (int i = 0; i < qtVertices; i++){
        for (int j = i+1; j < qtVertices; j++){
            aux = calculaDE(vertices[i], vertices[j]);
            matrizDE[i][j] = aux; 
            matrizDE[j][i] = aux;

            if (aux < infos->minDE) {
                infos->minDE = aux;
                infos->minDE_1 = vertices[i];
                infos->minDE_2 = vertices[j];
            }
            if (aux > infos->maxDE) {
                infos->maxDE = aux;
                infos->maxDE_1 = vertices[i];
                infos->maxDE_2 = vertices[j];
            }
        }
    }

    for (int i = 0; i < qtVertices; i++){
        for (int j = i+1; j < qtVertices; j++){
            aux = normalizaDE(matrizDE[i][j], infos->minDE, infos->maxDE);
            if (aux <= 0.3) {
                (*matrizADJ)[i][j] = 1;
                (*matrizADJ)[j][i] = 1;
            }
            else {
                (*matrizADJ)[i][j] = 0;
                (*matrizADJ)[j][i] = 0;
            }

            if (aux < infos->minDEN) {
                infos->minDEN = aux;
                infos->minDEN_1 = vertices[i];
                infos->minDEN_2 = vertices[j];
            }
            if (aux > infos->maxDEN) {
                infos->maxDEN = aux;
                infos->maxDEN_1 = vertices[i];
                infos->maxDEN_2 = vertices[j];
            }
        }
    }  

    return 1;
}

int salvaGrafo(struct info_grafo infos, int qtVertices, int **matrizADJ, struct no *vertices){
    criaPasta("Arquivos");

    FILE *arquivo_saida = fopen("Arquivos/Grafo.csv", "w");
    FILE *arquivo_saida_python = fopen("Arquivos/Grafo_python.txt", "w");
    FILE *arquivo_saida_estruturado = fopen("Arquivos/Grafo_estruturado.csv", "w"); 

    if (arquivo_saida == NULL || arquivo_saida_python == NULL || arquivo_saida_estruturado == NULL){
        printf("\n\u274C Erro ao criar arquivos de saida. Aperte enter para voltar.");
        getchar();
        return 0;
    }
    
    if (matrizADJ == NULL) {
        printf("\n\u274C Matriz de adjacência nula. Aperte enter para voltar. ");
        limpaBuffer();
        getchar();
        return 0;
    }
/*
    a) O total de vértices lidos;  ok
    b) A maior DE e o par de vértices (vi vj) que a determinaram;  ok
    c) A menor DE e o par de vértices (vi vj) que a determinaram;  ok
    d) A maior DEN e o par de vértices (vi vj) que a determinaram;  ok
    e) A menor DEN e o par de vértices (vi vj) que a determinaram;  ok
    f) Quantos componentes conexos e respectivos tamanhos (quantidades de vértices);
*/

    //GERA ARQUIVO ESTRUTURADO, COM DETALHES DOS DADOS
    fprintf(arquivo_saida_estruturado, "Total de vértices lidos, %i\n", infos.totalVertices);  //a)

    fprintf(arquivo_saida_estruturado, "Maior distância euclidiana, %f\n", infos.maxDE); // b)
    fprintf(arquivo_saida_estruturado, "Par de maior distância euclidiana, \"[%i](%.1f,%.1f,%.1f)\", \"[%i](%.1f,%.1f,%.1f)\"\n", infos.maxDE_1.indice, infos.maxDE_1.x, infos.maxDE_1.y, infos.maxDE_1.z, infos.maxDE_2.indice, infos.maxDE_2.x, infos.maxDE_2.y, infos.maxDE_2.z);

    fprintf(arquivo_saida_estruturado, "Menor distância euclidiana, %.1f\n", infos.minDE); //c)
    fprintf(arquivo_saida_estruturado, "Par de menor distância euclidiana, \"[%i](%.1f,%.1f,%.1f)\", \"[%i](%.1f,%.1f,%.1f)\"\n", infos.minDE_1.indice, infos.minDE_1.x, infos.minDE_1.y, infos.minDE_1.z, infos.minDE_2.indice, infos.minDE_2.x, infos.minDE_2.y, infos.minDE_2.z);

    fprintf(arquivo_saida_estruturado, "Maior distância euclidiana normalizada, %.1f\n", infos.maxDEN);  //d)
    fprintf(arquivo_saida_estruturado, "Par de maior distância euclidiana normalizada, \"[%i](%.1f,%.1f,%.1f)\", \"[%i](%.1f,%.1f,%.1f)\"\n", infos.maxDEN_1.indice, infos.maxDEN_1.x, infos.maxDEN_1.y, infos.maxDEN_1.z, infos.maxDEN_2.indice, infos.maxDEN_2.x, infos.maxDEN_2.y, infos.maxDEN_2.z);

    fprintf(arquivo_saida_estruturado, "Menor distância euclidiana normalizada, %.1f\n", infos.minDEN);  //e)
    fprintf(arquivo_saida_estruturado, "Par de menor distância euclidiana normalizada, \"[%i](%.1f,%.1f,%.1f)\", \"[%i](%.1f,%.1f,%.1f)\"\n", infos.minDEN_1.indice, infos.minDEN_1.x, infos.minDEN_1.y, infos.minDEN_1.z, infos.minDEN_2.indice, infos.minDEN_2.x, infos.minDEN_2.y, infos.minDEN_2.z);

    //GERA ARQUIVO PARA POSTERIOR LEITURA DO SISTEMA
    fprintf(arquivo_saida, "%i\n", infos.totalVertices);  //a)

    fprintf(arquivo_saida, "%f\n", infos.maxDE); // b)
    fprintf(arquivo_saida, "%i, %.1f, %.1f, %.1f, %i, %.1f, %.1f, %.1f\n", infos.maxDE_1.indice, infos.maxDE_1.x, infos.maxDE_1.y, infos.maxDE_1.z, infos.maxDE_2.indice, infos.maxDE_2.x, infos.maxDE_2.y, infos.maxDE_2.z);

    fprintf(arquivo_saida, "%.1f\n", infos.minDE); //c)
    fprintf(arquivo_saida, "%i, %.1f, %.1f, %.1f, %i, %.1f, %.1f, %.1f\n", infos.minDE_1.indice, infos.minDE_1.x, infos.minDE_1.y, infos.minDE_1.z, infos.minDE_2.indice, infos.minDE_2.x, infos.minDE_2.y, infos.minDE_2.z);

    fprintf(arquivo_saida, "%.1f\n", infos.maxDEN);  //d)
    fprintf(arquivo_saida, "%i, %.1f, %.1f, %.1f, %i, %.1f, %.1f, %.1f\n", infos.maxDEN_1.indice, infos.maxDEN_1.x, infos.maxDEN_1.y, infos.maxDEN_1.z, infos.maxDEN_2.indice, infos.maxDEN_2.x, infos.maxDEN_2.y, infos.maxDEN_2.z);

    fprintf(arquivo_saida, "%.1f\n", infos.minDEN);  //e)
    fprintf(arquivo_saida, "%i, %.1f, %.1f, %.1f, %i, %.1f, %.1f, %.1f\n", infos.minDEN_1.indice, infos.minDEN_1.x, infos.minDEN_1.y, infos.minDEN_1.z, infos.minDEN_2.indice, infos.minDEN_2.x, infos.minDEN_2.y, infos.minDEN_2.z);
    
    // PRINTA MATRIZ DE ADJACÊNCIA
    fprintf(arquivo_saida_estruturado, "\n\n");
    fprintf(arquivo_saida_estruturado, "MATRIZ DE ADJACÊNCIA\n");

    fprintf(arquivo_saida_estruturado, ","); // canto superior esquerdo vazio

    for (int i = 0; i < qtVertices; i++) {
        fprintf(arquivo_saida_estruturado, "\"(%.1f,%.1f,%.1f)\"", vertices[i].x, vertices[i].y, vertices[i].z);
        if (i < qtVertices - 1) fprintf(arquivo_saida_estruturado, ",");
    }
    fprintf(arquivo_saida_estruturado, "\n");

    for (int i = 0; i < qtVertices; i++) {
        fprintf(arquivo_saida_estruturado, "\"(%.1f,%.1f,%.1f)\"", vertices[i].x, vertices[i].y, vertices[i].z);
    
        for (int j = 0; j < qtVertices; j++) {
            fprintf(arquivo_saida_estruturado, ",%d", matrizADJ[i][j]);
            fprintf(arquivo_saida, "%d", matrizADJ[i][j]);
            if (j< qtVertices-1) fprintf(arquivo_saida, ",");

            if (matrizADJ[i][j] == 1 && i < j) fprintf(arquivo_saida_python, "%i %i\n", i+1, j+1); 
        }
        fprintf(arquivo_saida_estruturado, "\n");
        fprintf(arquivo_saida, "\n");
    }
    
    fclose(arquivo_saida_estruturado);
    fclose(arquivo_saida_python);
    return 1;
}

int carregaGrafo(struct info_grafo *infos, int ***matrizADJ){
    char nome_arquivo[100] = "Arquivos/Grafo.csv";
    FILE *arquivo = fopen(nome_arquivo, "r");

    while (arquivo == NULL && strcmp(nome_arquivo, "0") != 0){
        printf("\n\u274C Arquivo inexistente. Digite '0' para voltar ou digite o nome do arquivo: ");
        limpaBuffer();
        scanf("%s", nome_arquivo);
        arquivo = fopen(nome_arquivo, "r");
    }
    
    if (arquivo == NULL || strcmp(nome_arquivo, "0") == 0) return 0;

    int qtVertices;
    fscanf(arquivo, "%d\n", &qtVertices);
    infos->totalVertices = qtVertices;

    *matrizADJ = alocaMatriz(qtVertices);
    if (matrizADJ == NULL){
        printf("\n\u274C Erro ao alocar memória. Aperte enter para voltar. ");
        limpaBuffer();
        getchar();
    }

    fscanf(arquivo, "%f\n", &infos->maxDE);
    fscanf(arquivo, "%d, %f, %f, %f, %d, %f, %f, %f\n",&infos->maxDE_1.indice, &infos->maxDE_1.x, &infos->maxDE_1.y, &infos->maxDE_1.z, &infos->maxDE_2.indice, &infos->maxDE_2.x, &infos->maxDE_2.y, &infos->maxDE_2.z);

    fscanf(arquivo, "%f\n", &infos->minDE);
    fscanf(arquivo, "%d, %f, %f, %f, %d, %f, %f, %f\n", &infos->minDE_1.indice, &infos->minDE_1.x, &infos->minDE_1.y, &infos->minDE_1.z, &infos->minDE_2.indice, &infos->minDE_2.x, &infos->minDE_2.y, &infos->minDE_2.z);

    fscanf(arquivo, "%f\n", &infos->maxDEN);
    fscanf(arquivo, "%d, %f, %f, %f, %d, %f, %f, %f\n", &infos->maxDEN_1.indice, &infos->maxDEN_1.x, &infos->maxDEN_1.y, &infos->maxDEN_1.z, &infos->maxDEN_2.indice, &infos->maxDEN_2.x, &infos->maxDEN_2.y, &infos->maxDEN_2.z);

    fscanf(arquivo, "%f\n", &infos->minDEN);
    fscanf(arquivo, "%d, %f, %f, %f, %d, %f, %f, %f\n", &infos->minDEN_1.indice, &infos->minDEN_1.x, &infos->minDEN_1.y, &infos->minDEN_1.z, &infos->minDEN_2.indice, &infos->minDEN_2.x, &infos->minDEN_2.y, &infos->minDEN_2.z);

    // Leitura da matriz de adjacência
    for (int i = 0; i < qtVertices; i++) {
        for (int j = 0; j < qtVertices; j++) {
            fscanf(arquivo, "%d", &(*matrizADJ)[i][j]);
            if (j < qtVertices - 1) fscanf(arquivo, ",");  // ignora ","
        }
        fscanf(arquivo, "\n");
    }

    fclose(arquivo);
    return 1;
}

int main(){
    int qtVertices = 0, qtAlocada = 10, continuar = 1, opcao, **matrizADJ = NULL;
    //char nomeArquivo[100] = "grafoteste.csv";
    char nomeArquivo[100];
    No *vertices = malloc(sizeof(No) * qtAlocada);
    Info_grafo infos;

    while (continuar){
        limpaTela();
        printf("1 - Criar grafo apartir de dataset de dados\n");
        printf("2 - Carregar grafo gerado\n");
        printf("3 - Sair\n");
    
        printf("Difite uma opção: ");
        entrada(1, 3, &opcao);
        limpaTela();

        switch (opcao){
            case 1:{
                printf("Digite o nome do arquivo de dados: ");
                limpaBuffer();
                scanf("%s", nomeArquivo);
                limpaBuffer();

                if(carregaArquivo(&vertices, &qtAlocada, &qtVertices, nomeArquivo)) printf("\n\u2714 Vertices carregados com sucesso.\n");
                else break;                         

                if(criaGrafo(vertices, qtVertices, &infos, &matrizADJ)) printf("\n\u2714 Grafo criado com sucesso.\n");
                else break;


                if(salvaGrafo(infos, qtVertices, matrizADJ, vertices)) printf("\n\u2714 Grafo e demais informações salvos nos arquivos de saída.\n");
                else break;

                limpaBuffer();
                printf("\nAperte enter para voltar. ");
                getchar();
            }
            break;
            case 2:
                if(matrizADJ != NULL) liberaMatriz(matrizADJ, infos.totalVertices);

                if(carregaGrafo(&infos, &matrizADJ)) printf("\n\u2714 Grafo carregado com sucesso.\n");
                else break;

                printf("\nAperte enter para voltar. ");
                limpaBuffer();
                getchar();    
            break;
            case 3:
                continuar = 0;
            break;
        }
    }

    liberaMatriz(matrizADJ, infos.totalVertices);
    free(vertices);
    return 0;
}