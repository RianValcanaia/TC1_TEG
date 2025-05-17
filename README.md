# 🗃️ Trabalho – Análise e Processamento de Grafos

Este repositório contém a implementação de um sistema para processamento e análise de vértices tridimensionais, com cálculo de distâncias euclidianas (DE), distâncias euclidianas normalizadas (DEN) e geração de matrizes de adjacência. O projeto faz parte da disciplina de Teoria dos Grafos (TEG).

## 📌 Objetivos

- Ler vértices com coordenadas tridimensionais (x, y, z)
- Calcular a distância euclidiana entre os vértices (DE)
- Calcular a distância euclidiana normalizada (DEN)
- Determinar pares de vértices com DEN <= 0.3
- Alocar e manipular estruturas dinâmicas como listas e matrizes

## 📥 Entradas do sistema

- Arquivo .csv onde cada linha representa um vértice com índice e coordenadas (x, y, z) 

## 🧱 Estruturas de Dados

No programa, são usadas duas estruturas principais para representar os vértices do grafo e as informações calculadas durante a construção do grafo: `No` e `Info_grafo`.

### 🔸 `No`

A estrutura `No` representa um vértice no grafo, que é um ponto no espaço tridimensional. Cada vértice possui um identificador único e suas coordenadas espaciais.

```c
typedef struct no {
    int indice;  // Identificador único do vértice.
    float x, y, z;  // Coordenadas do vértice no espaço 3D.
} No;
```

### 🔸 `Info_grafo`
A estrutura `Info_grafo` armazena informaçõe relacionadas ao grafo como um todo. Ela guarda métricas sobre as distâncias entre os vértices, tanto as distâncias Euclidianas quanto as distâncias Euclidianas normalizadas, e também os pares de vértices que determinam esses valores extremos.

```c
typedef struct info_grafo {
    int totalVertices;  // Número total de vértices no grafo.
    float maxDE, minDE, maxDEN, minDEN;  // Maior e menor distância Euclidiana e Normalizada.
    struct no maxDE_1, maxDE_2;  // Vértices que determinam a maior distância Euclidiana.
    struct no minDE_1, minDE_2;  // Vértices que determinam a menor distância Euclidiana.
    struct no maxDEN_1, maxDEN_2;  // Vértices que determinam a maior distância Normalizada.
    struct no minDEN_1, minDEN_2;  // Vértices que determinam a menor distância Normalizada.
} Info_grafo;
```

## 🛠️ Funcionalidades

### 🔹 Funções Principais

Estas funções representam os **processos centrais** do programa:

- `carregaArquivo()`
    Lê um arquivo.csv contendo vértices no formato x,y,z e armazena em um vetor dinâmico de estruturas no.  

- `criaGrafo()`
    Cria um grafo não-direcionado a partir de um conjunto de vértices, com base na distância euclidiana entre eles.

- `salvaGrafo()`
    Salva as informações do grafo em um arquivo : 
    - Grafo.csv: grafo que é possível fazer a leitura no sistema, bem como possui uma estrutura bem clara para leitura do usuário.

- `carregaGrafo()`
    Lê um grafo salvo em arquivo .csv, reconstruindo as informações estruturais e a matriz de adjacência.
    ❗ obs: esta função só carrega um grafo se o grafo possuir a saída gerada por este sistema, use aqui o arquivo gerado Grafo.csv.
- `pltar_grafo_3d()`
    Recebe um arquivo .txt com uma lista de arestas e chama o script de Python para plotar o grafo em 3D a partir da linha de comando da máquina utilizando a função system(). Vale ressaltar que só funcionará se a sua máquina for Linux com Python instalado.


### 🔸 Funções Secundárias

Estas funções oferecem suporte essencial à lógica principal do sistema:

- `limpaTela()`
    Limpa a tela do terminal com comandos compatíveis com o sistema operacional (Windows ou Unix).

- `limpaBuffer()`
    Remove caracteres residuais do buffer de entrada (stdin) para evitar leituras incorretas.

- `entrada(int ini, int fim, int *num)`
    Garante que o valor inserido esteja dentro de um intervalo válido [ini, fim].

- `alocaVertices(struct no **vertices, int alocar)`
    Realoca memória para um vetor de vértices tridimensionais de forma segura.

- `calculaDE(struct no A, struct no B)`
    Calcula a distância euclidiana entre dois pontos tridimensionais.

- `normalizaDE(float x, float min, float max)`
    Normaliza uma distância com base nos valores mínimos e máximos observados.

- `alocaMatriz(int tam)`
    Aloca dinamicamente uma matriz quadrada de inteiros.

- `liberaMatriz(int **matriz, int tam)`
    Libera a memória de uma matriz quadrada alocada dinamicamente.

- `converteCSVparaTXT()`
   Abre um arquivo .csv e converte-o para um arquivo .txt para ser utilizado posteriormente para o plot do grafo em 3D 

- `dfs(int v, int **matrizADJ, int *visitados, int totalVertices, int *tamanhoComponente)`
    Realiza uma busca em profundidade a partir de um vértice inicial, marcando vértices visitados e calculando o tamanho do componente conexo.

- `contaComponentesConexos(int **matrizADJ, int totalVertices, Info_grafo *infos)`
    Identifica e conta todos os componentes conexos do grafo, registrando a frequência de componentes por tamanho.
## 📊 Exemplo de Execução

1. Usuário entra com arquivo.csv contendo os vértices em cada linha;
2. Arquivos de saída são gerados na pasta Arquivos.
3. Usuário pode entrar com um grafo.csv já gerado anteriormente pelo sistema, sem ter que calcular novamente DE, DEN.

❗ obs: a pasta do trabalho contém um `grafoteste.csv` com 204 vértices.

## 📂 Como executar

1. Compile o código com um compilador C (recomenda-se o `gcc`):
   ```bash
   gcc trabalho.c -lm  && ./a.out  

## 👨‍🏫 Envolvidos

- Professor: GILMARIO BARBOSA DOS SANTOS
- Estudantes: Lucas Oliveira Macedo, Matheus Azevedo de Sá e [Rian Valcanaia](https://github.com/RianValcanaia)


## 📅 Curso

- Universidade: Universidade do Estado de Santa Catarina (UDESC)
- Disciplina: Teoria dos Grafos
- Semestre: 4º 

## 📄 Arquivo-fonte

O código completo do projeto está disponível no GitHub:  
[https://github.com/RianValcanaia/TC1_TEG](https://github.com/RianValcanaia/TC1_TEG)