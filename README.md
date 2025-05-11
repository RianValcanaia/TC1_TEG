# 🗃️ Trabalho – Análise e Processamento de Grafos

Este repositório contém a implementação de um sistema para processamento e análise de vértices tridimensionais, com cálculo de distâncias euclidianas (DE), distâncias euclidianas normalizadas (DEN) e geração de matrizes de adjacência. O projeto faz parte da disciplina de Teoria dos Grafos (TEG).

## 📌 Objetivos

- Ler vértices com coordenadas tridimensionais (x, y, z)
- Calcular a distância euclidiana entre os vértices (DE)
- Calcular a distância euclidiana normalizada (DEN)
- Determinar pares de vértices com DEN <= 0.3
- Alocar e manipular estruturas dinâmicas como listas e matrizes

## 📥 Estruturas Principais

- Arquivo .csv onde cada linha representa um vértice com índice e coordenadas (x, y, z)

### 🔹 Funções Principais

Estas funções representam os **processos centrais** do programa:

- `carregaArquivo()`
    Lê um arquivo texto contendo vértices no formato x,y,z e armazena em um vetor dinâmico de estruturas no.  

- `criaGrafo()`
    Cria um grafo não-direcionado a partir de um conjunto de vértices, com base na distância euclidiana entre eles.

- `salvaGrafo()`
    Salva as informações do grafo em três arquivos diferentes: 
    - Grafo.csv: grafo que é possível fazer a leitura no sistema;
    - Grafo_estruturado.csv: para leitura humana, apresenta informações com dados;
    - Grafo_python.txt: para script de geração 3D de grafos em Python.
- `carregaGrafo()`
    Lê um grafo salvo em arquivo .csv, reconstruindo as informações estruturais e a matriz de adjacência.
    ❗ obs: esta função só carrega um grafo se o grafo possuir a saída gerada por este sistema, use aqui o arquivo gerado Grafo.csv 

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

- `removePasta(const char *caminho)`
    Remove uma pasta e todos os arquivos contidos nela.

- `criaPasta(const char* caminho)`
    Cria uma nova pasta, removendo a anterior se já existir.


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
- Estudante: Matheus Azevedo de Sá e [Rian Valcanaia](https://github.com/RianValcanaia)


## 📅 Curso

- Universidade: Universidade do Estado de Santa Catarina (UDESC)
- Disciplina: Teoria dos Grafos
- Semestre: 4º 

## 📄 Arquivo-fonte

O código completo do projeto está disponível no GitHub:  
[https://github.com/RianValcanaia/TC_Classificacao_de_Arquivos](https://github.com/RianValcanaia/TC1_TEG)