<<<<<<< HEAD
/* OTIMIZAÇÃO COMBINATÓRIA 2022/02 - APLICAÇÃO DE GRASP NO PROBLEMA DA SELEÇÃO DE MAIOR DISTÂNCIA MÍNIMA TOTAL */

/* VERSÃO DE BUSCA COM VIZINHANÇA DETERMINÍSTICA */

/* Andrei Pochmann Koenich - Cartão 00308680 */
/* Pedro Company Beck - Cartão 00324055 */
=======
/* OTIMIZACAO COMBINATORIA 2022/02 - APLICACAOO DE GRASP NO PROBLEMA DA SELECAO DE MAIOR DISTANCIA MINIMA TOTAL */

/* VERSAO DE BUSCA COM VIZINHANÃ‡A DETERMINISTICA */

/* Andrei Pochmann Koenich - Cartao 00308680 */
/* Pedro Company Beck - Cartao 00324055 */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
<<<<<<< HEAD

/* Valor que representa a quantidade máxima de caracteres para o nome do arquivo de entrada e o nome do arquivo de saída. */
#define DIMENSAONOME 100

/* Variável global inteira representando a seed para geração de valores aleatórios, a ser escolhida pelo usuário. */
int seed = 0;

/* Estrutura para armazenar as informações da instância do problema recebida como entrada, além dos valores
necessários para realizar a busca, escolhidos pelo usuário. */
typedef struct
{
    /* Os cinco componentes abaixo são parâmetros de execução escolhidos pelo usuário. */
=======
#include <string.h>

/* Valor que representa a quantidade maxima de caracteres para o nome do arquivo de entrada e o nome do arquivo de saida. */
#define DIMENSAONOME 100

/* Variavel global inteira representando a seed para geracao de valores aleatorios, a ser escolhida pelo usuario. */
int seed = 0;

/* Estrutura para armazenar as informacoes da instancia do problema recebida como entrada, alem dos valores
necessarios para realizar a busca, escolhidos pelo usuario. */
typedef struct
{
    /* Os cinco componentes abaixo sao parametros de execucao escolhidos pelo usuario. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)

    char nome_arquivo_entrada[DIMENSAONOME];
    char nome_arquivo_saida[DIMENSAONOME];

<<<<<<< HEAD
    /* Representa a quantidade de inícios gulosos-randomizados que ocorrerão no processo de busca. */
    int quantidade_inicios;

    /* Representa quantas das melhores soluções randomizadas de cada construção participarão do sorteio para escolher a
    solução inicial do processo de busca local, que ocorrerá após o sorteio. */
    int quantidade_sorteio;

    /* Representa o número total de soluções randomizadas que ocorrerão em cada início. Após a geração de todas essas
    construções, ocorre o sorteio (feito com alguns dos melhores indivíduos gerados),  para decidir qual das soluções
    randomizadas que foram geradas será considerada para iniciar o processo de busca local. */
    int quantidade_construcoes;

    /* Os quatro componentes abaixo são obtidos a partir da leitura do arquivo de entrada .ins */

    /* Representa a quantidade de vértices do subgrafo M. */
    int cardinalidade_M;

    /* Representa a quantidade de vértices do subgrafo L. */
    int cardinalidade_L;

    /* Representa a quantidade de vértices do subgrafo L que serão selecionados. */
    int constante_l;

    /* Vetor contendo todos os vértices (representados por valores inteiros) do subgrafo L. */
=======
    /* Representa a quantidade de inicios gulosos-randomizados que ocorrerao no processo de busca. */
    int quantidade_inicios;

    /* Representa quantas das melhores solucoes randomizadas de cada construcao participarao do sorteio para escolher a
    solucao inicial do processo de busca local, que ocorrera apos o sorteio. */
    int quantidade_sorteio;

    /* Representa o numero total de solucoes randomizadas que ocorrerao em cada inicio. Apos a geracao de todas essas
    construcoes, ocorre o sorteio (feito com alguns dos melhores individuos gerados),  para decidir qual das solucoes
    randomizadas que foram geradas sera considerada para iniciar o processo de busca local. */
    int quantidade_construcoes;

    /* Os quatro componentes abaixo sao obtidos a partir da leitura do arquivo de entrada .ins */

    /* Representa a quantidade de vertices do subgrafo M. */
    int cardinalidade_M;

    /* Representa a quantidade de vertices do subgrafo L. */
    int cardinalidade_L;

    /* Representa a quantidade de vertices do subgrafo L que serao selecionados. */
    int constante_l;

    /* Vetor contendo todos os vertices (representados por valores inteiros) do subgrafo L. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    int *conjunto_L;

} Instancia;

<<<<<<< HEAD
/* Estrutura para representar uma possível solução do problema de forma mais simplificada. Essa
estrutura será utilizada durante a busca local, para representação dos vizinhos. */
typedef struct
{
    int *vertices_selecionados; /* Vetor contendo todos os vértices do subgrafo L que foram selecionados. */
    float distancia; /* Valor da soma de todas as distâncias mínimas, representando um valor da função objetivo. */

} Vizinhos;

/* Estrutura para representar, de forma mais completa, uma possível solução do problema.
Ao longo do código, serão definidos vetores a partir dessa estrutura, com cada índice
do vetor representando o vértice M, que estará conectado com um vértice L e terá uma
certa distância de ligação. */
typedef struct
{
    /* Representa um vértice do subgrafo L que foi selecionado, para estar ligado a um vértice do subgrafo M. */
    int vertice_L;

    /* Representa a distância entre um vértice do subgrafo M e um vértice do subgrafo L. */
=======
/* Estrutura para representar uma possivel solucao do problema de forma mais simplificada. Essa
estrutura sera utilizada durante a busca local, para representacaoo dos vizinhos. */
typedef struct
{
    int *vertices_selecionados; /* Vetor contendo todos os vertices do subgrafo L que foram selecionados. */
    float distancia; /* Valor da soma de todas as distancias minimas, representando um valor da funcao objetivo. */

} Vizinhos;

/* Estrutura para representar, de forma mais completa, uma possivel solucao do problema.
Ao longo do codigo, serao definidos vetores a partir dessa estrutura, com cada indice
do vetor representando o vertice M, que estara conectado com um vertice L e terao uma
certa distancia de ligacao. */
typedef struct
{
    /* Representa um vertice do subgrafo L que foi selecionado, para estar ligado a um vertice do subgrafo M. */
    int vertice_L;

    /* Representa a distancia entre um vertice do subgrafo M e um vertice do subgrafo L. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    float distancia;

} Arestas;

<<<<<<< HEAD
/* Obtém o valor mínimo entre dois valores inteiros. */
=======
/* Obtem o valor minimo entre dois valores inteiros. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
int minimo(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

<<<<<<< HEAD
/* Função para posicionar todos os elementos existentes em X nas primeiras posições do vetor Y.
Exemplo: para uma entrada X = {4,5,6} e Y = {1,2,3,4,5,6}, com a chamada reordenar_vetores(X,3,Y,6),
teremos como saída X = {4,5,6} e Y = {4,5,6,1,2,3}. */
=======
/* Funcaoo para posicionar todos os elementos existentes em X nas primeiras posicoes do vetor Y.
Exemplo: para uma entrada X = {4,5,6} e Y = {1,2,3,4,5,6}, com a chamada reordenar_vetores(X,3,Y,6),
teremos como saida X = {4,5,6} e Y = {4,5,6,1,2,3}. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
void reordenar_vetores(int X[], int tamanho_X, int Y[], int tamanho_Y)
{
    int i, j = 0;
    for (i = 0; i < tamanho_X; i++)
    {
        int k;
        for (k = 0; k < tamanho_Y; k++)
        {
            if (X[i] == Y[k])
            {
                int temp = Y[j];
                Y[j] = Y[k];
                Y[k] = temp;
                j++;
            }
        }
    }
}

<<<<<<< HEAD
/* Função auxiliar do algoritmo quick sort, para realizar uma troca de posições entre dois elementos de um vetor. */
=======
/* Funcaoo auxiliar do algoritmo quick sort, para realizar uma troca de posicoes entre dois elementos de um vetor. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
void swap(Vizinhos v[], int i, int j)
{
    Vizinhos aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

<<<<<<< HEAD
/* Função auxiliar do quicksort para realizar o ordenamento de várias soluções em ordem decrescente, com particionamento de Hoare. */
=======
/* Funcao auxiliar do quicksort para realizar o ordenamento de varias solucoes em ordem decrescente, com particionamento de Hoare. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
int pHoareStructDecrescente(Vizinhos v[], int p, int r)
{
    Vizinhos pivo = v[p];
    int i = p - 1, j = r + 1;

    while (1)
    {
        do
        {
            i++;

        } while (v[i].distancia > pivo.distancia);

        do
        {
            j--;

        } while (v[j].distancia < pivo.distancia);

        if (i >= j)
            return j;

        swap(v, i, j);
    }
}

<<<<<<< HEAD
/* Função principal do quicksort para realizar o ordenamento de várias soluções em ordem decrescente. */
=======
/* Funcaoo principal do quicksort para realizar o ordenamento de varias solucoes em ordem decrescente. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
void quickSortStructDecrescente(Vizinhos v[], int p, int r)
{
    if (p < r)
    {
        int posicao = pHoareStructDecrescente(v, p, r);
        quickSortStructDecrescente(v, p, posicao);
        quickSortStructDecrescente(v, posicao+1, r);
    }
}

<<<<<<< HEAD
/* Função para percorrer um vetor contendo várias possíveis soluções, e encontrar o índice da melhor solução,
ou seja, a solução que possui o maior valor da soma de distâncias mínimas. */
=======
/* Funcao para percorrer um vetor contendo varias possiveis solucoes, e encontrar o indice da melhor solucao,
ou seja, a solucao que possui o maior valor da soma de distancias minimas. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
int acha_melhor(Vizinhos s[], int quantidade_solucoes)
{
    float melhor_valor = s[0].distancia;
    int indice_melhor = 0;

<<<<<<< HEAD
    /* Percorre todas as soluções disponíveis, atualizando o melhor valor obtido. */
=======
    /* Percorre todas as solucoes disponiveis, atualizando o melhor valor obtido. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    for (int i = 1; i < quantidade_solucoes; i++)
        if (melhor_valor < s[i].distancia)
        {
            melhor_valor = s[i].distancia;
            indice_melhor = i;
        }

    return indice_melhor;
}

<<<<<<< HEAD
/* Recebe um conjunto de vértices selecionados de L, e faz a conexao com os vertices de M, gerando uma possivel solucao para o problema. */
=======
/* Recebe um conjunto de vertices selecionados de L, e faz a conexao com os vertices de M, gerando uma possivel solucao para o problema. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
void conecta_vertices (Arestas solucao_parcial[], Instancia informacoes, float **matriz_adjacencia, int selecoes[])
{
    float menor_distancia;

    for (int i = 0; i < informacoes.cardinalidade_M; i++)
    {
<<<<<<< HEAD
        /* Inicializa os valores de menor distância, distância parcial e do vértice de L selecionado, antes da busca. */
=======
        /* Inicializa os valores de menor distancia, distancia parcial e do vertice de L selecionado, antes da busca. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
        menor_distancia = matriz_adjacencia[i][selecoes[0]];
        solucao_parcial[i].distancia = menor_distancia;
        solucao_parcial[i].vertice_L = selecoes[0];

<<<<<<< HEAD
        /* Para cada vértice de M, faz a conexão com o vértice de menor distancia, entre os vértices de L selecionados. */
        for (int j = 1; j < informacoes.constante_l; j++)
        {
            /* Atualiza a conexao entre um vértice de M e outro de L, cada vez que uma distancia menor é encontrada. */
=======
        /* Para cada vertice de M, faz a conexao com o vertice de menor distancia, entre os vertices de L selecionados. */
        for (int j = 1; j < informacoes.constante_l; j++)
        {
            /* Atualiza a conexao entre um vertice de M e outro de L, cada vez que uma distancia menor e encontrada. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
            if (matriz_adjacencia[i][selecoes[j]] < menor_distancia)
            {
                menor_distancia = matriz_adjacencia[i][selecoes[j]];
                solucao_parcial[i].distancia = menor_distancia;
                solucao_parcial[i].vertice_L = selecoes[j];
            }
        }
    }
}

<<<<<<< HEAD
/* Recebe um conjunto de vértices selecionados, e retorna a soma das distâncias mínimas com os vértices de M, para fins de análise. */
=======
/* Recebe um conjunto de vertices selecionados, e retorna a soma das distancias minimas com os vertices de M, para fins de analise. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
float analisa_solucao(int vertices_selecionados[], Instancia informacoes, float **matriz_adjacencia)
{
    float soma_distancias = 0.0;

    for(int i = 0; i < informacoes.cardinalidade_M; i++)
    {
        float menor_distancia = matriz_adjacencia[i][vertices_selecionados[0]];
<<<<<<< HEAD
        for (int j = 1; j < informacoes.constante_l; j++) /* Para cada vértice de M, obtem a menor distancia em relacao a um vértice selecionado em L. */
=======
        for (int j = 1; j < informacoes.constante_l; j++) /* Para cada vertice de M, obtem a menor distancia em relacao a um vertice selecionado em L. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
            if (matriz_adjacencia[i][vertices_selecionados[j]] < menor_distancia)
                menor_distancia = matriz_adjacencia[i][vertices_selecionados[j]];
        soma_distancias += menor_distancia; /* Atualiza a soma das distancias minimas em cada iteracao. */
    }

    return soma_distancias; /* Retorna a soma das distancias minimas. */
}

<<<<<<< HEAD
/* Recebe uma possível solução para o problema, e retorna a soma total das distâncias mínimas entre os vértices de M e os vértices de L selecionados, para fins de análise. */
float soma_distancias(Arestas solucao[], Instancia informacoes)
{
    float somatorio = 0.0;
    for (int i = 0; i < informacoes.cardinalidade_M; i++) /* Faz a soma parcial de cada distância mínima, da possível solução. */
=======
/* Recebe uma possivel solucao para o problema, e retorna a soma total das distancias minimas entre os vertices de M e os vertices de L selecionados, para fins de analise. */
float soma_distancias(Arestas solucao[], Instancia informacoes)
{
    float somatorio = 0.0;
    for (int i = 0; i < informacoes.cardinalidade_M; i++) /* Faz a soma parcial de cada distancia minima, da possivel solucao. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
        somatorio += solucao[i].distancia;
    return somatorio;
}

/* Embaralha todos os vertices do vetor de vertices, com o algoritmo de Fisher-Yates. */
void embaralha_vertices (int vertices[], int cardinalidade)
{
    for (int i = cardinalidade - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int aux = vertices[i];
        vertices[i] = vertices[j];
        vertices[j] = aux;
    }
}

<<<<<<< HEAD
/* Gera uma solução inicial do problema, a partir da qual será executada uma busca local
até que seja atingido um máximo local. */
void inicializa_solucao (Arestas solucao_inicial[], Instancia informacoes, float **matriz_adjacencia)
{
    /* Preenche todos os vértices do conjunto L, sequencialmente. */
    for(int i = 0; i < informacoes.cardinalidade_L; i++)
        informacoes.conjunto_L[i] = i;

    /* Inicializa um vetor com descrições de várias possíveis soluções iniciais.
    O número de construções iniciais foi definido pelo usuário. */
    Vizinhos *inicios;
    inicios = calloc(informacoes.quantidade_construcoes,sizeof(Vizinhos));

    /* Embaralha os vértices do conjunto L várias vezes, a fim de gerar várias seleções
    randomizadas de "l" vértices do conjunto L. */
    for(int i = 0; i < informacoes.quantidade_construcoes; i++)
    {
        inicios[i].vertices_selecionados = calloc(informacoes.constante_l,sizeof(int)); /* Aloca espaço de memória referente a cada uma das soluções iniciais. */
        embaralha_vertices(informacoes.conjunto_L,informacoes.cardinalidade_L); /* Embaralha os vértices do conjunto L em cada iteração, para gerar uma nova seleção de vértices. */
        for(int j = 0; j < informacoes.constante_l; j++) /* Obtém os vértices selecionados do conjunto L, após cada embaralhamento. */
            inicios[i].vertices_selecionados[j] = informacoes.conjunto_L[j];
        inicios[i].distancia = analisa_solucao(inicios[i].vertices_selecionados,informacoes,matriz_adjacencia); /* Para cada solução gerada, calcula a soma das distâncias mínimas. */
    }

    /* Ordena todas as soluções iniciais geradas em ordem decrescente com base nas somas das distâncias mínimas totais,
    utilizando o algoritmo quicksort. */
    quickSortStructDecrescente(inicios,0,informacoes.quantidade_construcoes-1);

    /* Após a ordenação, obtém de forma aleatória qual das melhores soluções geradas será considerada para iniciar a busca local. */
    int indice_vencedor = rand() % informacoes.quantidade_sorteio;

    /* Após obter a solução inicial que será considerada, realiza as conexões de vértices. */
    conecta_vertices(solucao_inicial,informacoes,matriz_adjacencia,inicios[indice_vencedor].vertices_selecionados);

    /* Após realizar uma seleção dentro do conjunto L de vértices, traz os "l" vértices selecionados para as primeiras "l" posições
    do vetor contido em informacoes.conjunto_L. Isso é usado posteriormente para gerar as vizinhanças, na busca local. */
    reordenar_vetores(inicios[indice_vencedor].vertices_selecionados,informacoes.constante_l,informacoes.conjunto_L,informacoes.cardinalidade_L);

    /* Libera todo o espaço de memória que foi utilizado para a construção das soluções aleatórias, no início da busca. */
=======
/* Gera uma solucao inicial do problema, a partir da qual sera executada uma busca local
ate que seja atingido um maximo local. */
void inicializa_solucao (Arestas solucao_inicial[], Instancia informacoes, float **matriz_adjacencia)
{
    /* Preenche todos os vertices do conjunto L, sequencialmente. */
    for(int i = 0; i < informacoes.cardinalidade_L; i++)
        informacoes.conjunto_L[i] = i;

    /* Inicializa um vetor com descricoes de varias possiveis solucoes iniciais.
    O numero de construcoes iniciais foi definido pelo usuario. */
    Vizinhos *inicios;
    inicios = calloc(informacoes.quantidade_construcoes,sizeof(Vizinhos));

    /* Embaralha os vertices do conjunto L varias vezes, a fim de gerar varias selecoes
    randomizadas de "l" vertices do conjunto L. */
    for(int i = 0; i < informacoes.quantidade_construcoes; i++)
    {
        inicios[i].vertices_selecionados = calloc(informacoes.constante_l,sizeof(int)); /* Aloca espaco de memoria referente a cada uma das solucoes iniciais. */
        embaralha_vertices(informacoes.conjunto_L,informacoes.cardinalidade_L); /* Embaralha os vertices do conjunto L em cada iteracao, para gerar uma nova selecao de vertices. */
        for(int j = 0; j < informacoes.constante_l; j++) /* Obtem os vertices selecionados do conjunto L, apos cada embaralhamento. */
            inicios[i].vertices_selecionados[j] = informacoes.conjunto_L[j];
        inicios[i].distancia = analisa_solucao(inicios[i].vertices_selecionados,informacoes,matriz_adjacencia); /* Para cada solucao gerada, calcula a soma das distancias minimas. */
    }

    /* Ordena todas as solucoes iniciais geradas em ordem decrescente com base nas somas das distancias minimas totais,
    utilizando o algoritmo quicksort. */
    quickSortStructDecrescente(inicios,0,informacoes.quantidade_construcoes-1);

    /* Apos a ordenacao, obtem de forma aleatoria qual das melhores solucoes geradas sera considerada para iniciar a busca local. */
    int indice_vencedor = rand() % informacoes.quantidade_sorteio;

    /* Apos obter a solucao inicial que sera considerada, realiza as conexoes de vertices. */
    conecta_vertices(solucao_inicial,informacoes,matriz_adjacencia,inicios[indice_vencedor].vertices_selecionados);

    /* Apos realizar uma selecao dentro do conjunto L de vertices, traz os "l" vertices selecionados para as primeiras "l" posicoes
    do vetor contido em informacoes.conjunto_L. Isso e usado posteriormente para gerar as vizinhancas, na busca local. */
    reordenar_vetores(inicios[indice_vencedor].vertices_selecionados,informacoes.constante_l,informacoes.conjunto_L,informacoes.cardinalidade_L);

    /* Libera todo o espaco de memoria que foi utilizado para a construcao das solucoes aleatorias, no inicio da busca. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    for (int i = 0; i < informacoes.quantidade_construcoes; i++)
        free(inicios[i].vertices_selecionados);
    free(inicios);
}

<<<<<<< HEAD
/* Função para gerar toda a vizinhança, a partir de uma certa solução.
A geração da vizinhança ocorre permutando cada vértice que está selecionado
por um vértice que não está selecionado.

Exemplo: se o conjunto L é dado por {1,2,3,4} e, em um determinado ponto da busca
selecionamos os vértices {1,2}, então os quatro vizinhos serão:

{3, 2} - trocamos o vértice 1 (que foi selecionado) pelo vértice 3 (que não estava selecionado)
{4, 2} - trocamos o vértice 1 (que foi selecionado) pelo vértice 4 (que não estava selecionado)
{1, 3) - trocamos o vértice 2 (que foi selecionado) pelo vértice 3 (que não estava selecionado)
{1, 4} - trocamos o vértice 2 (que foi selecionado) pelo vértice 4 (que não estava selecionado) */
void gera_vizinhos(Vizinhos vizinhos[], Instancia informacoes, int quantidade_vizinhos)
{
    for (int i = 0; i < quantidade_vizinhos; i++) /* Aloca espaço de memória suficiente para cada vizinho. */
        vizinhos[i].vertices_selecionados = calloc(informacoes.constante_l,sizeof(int));

    /* Transfere o conjunto atual de "l" vértices selecionados para o vetor correspondente a cada vizinho,
    para depois permutar os vértices, gerando toda a vizinhança. */
=======
/* Funcao para gerar toda a vizinhanca, a partir de uma certa solucao.
A geracao da vizinhanca ocorre permutando cada vertice que esta selecionado
por um vertice que nao esta selecionado.

Exemplo: se o conjunto L e dado por {1,2,3,4} e, em um determinado ponto da busca
selecionamos os vertices {1,2}, entao os quatro vizinhos serao:

{3, 2} - trocamos o vertice 1 (que foi selecionado) pelo vertice 3 (que nao estava selecionado)
{4, 2} - trocamos o vertice 1 (que foi selecionado) pelo vertice 4 (que nao estava selecionado)
{1, 3) - trocamos o vertice 2 (que foi selecionado) pelo vertice 3 (que nao estava selecionado)
{1, 4} - trocamos o vertice 2 (que foi selecionado) pelo vertice 4 (que nao estava selecionado) */
void gera_vizinhos(Vizinhos vizinhos[], Instancia informacoes, int quantidade_vizinhos)
{
    for (int i = 0; i < quantidade_vizinhos; i++) /* Aloca espaco de memoria suficiente para cada vizinho. */
        vizinhos[i].vertices_selecionados = calloc(informacoes.constante_l,sizeof(int));

    /* Transfere o conjunto atual de "l" vertices selecionados para o vetor correspondente a cada vizinho,
    para depois permutar os vertices, gerando toda a vizinhanca. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    for (int i = 0; i < quantidade_vizinhos; i++)
        for (int j = 0; j < informacoes.constante_l; j++)
            vizinhos[i].vertices_selecionados[j] = informacoes.conjunto_L[j];

<<<<<<< HEAD
    /* Nessa próxima iteração, ocorrem as permutações envolvendo um vértice selecionado e um vértice não-selecionado,
    para gerar toda a vizinhança. */
=======
    /* Nessa proxima iteracao, ocorrem as permutacoes envolvendo um vertice selecionado e um vertice nao-selecionado,
    para gerar toda a vizinhanca. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    int k = 0;
    for (int i = 0; i < informacoes.constante_l; i++)
    {
        int j = 0;
        while (informacoes.constante_l+j < informacoes.cardinalidade_L)
        {
            vizinhos[k].vertices_selecionados[i] = informacoes.conjunto_L[informacoes.constante_l+j];
            j++;
            k++;
        }
    }
}

<<<<<<< HEAD
/* Função para executar a busca local, gerando uma vizinhança e fazendo uma transição de forma
gulosa, para a próxima solução com a maior soma de distâncias mínimas. */
int examina_vizinhanca (Arestas solucao_parcial[],Instancia informacoes,float **matriz_adjacencia)
{
    int melhorou = 0; /* Variável para indicar se uma solução melhor foi obtida. */
    Vizinhos *vizinhos; /* Vetor para conter toda a vizinhança, durante um passo da busca local. */
=======
/* Funcao para executar a busca local, gerando uma vizinhanca e fazendo uma transicao de forma
gulosa, para a proxima solucao com a maior soma de distancias minimas. */
int examina_vizinhanca (Arestas solucao_parcial[],Instancia informacoes,float **matriz_adjacencia)
{
    int melhorou = 0; /* Variavel para indicar se uma solucao melhor foi obtida. */
    Vizinhos *vizinhos; /* Vetor para conter toda a vizinhanca, durante um passo da busca local. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    int quantidade_vizinhos = (informacoes.cardinalidade_L-informacoes.constante_l)*(informacoes.constante_l);
    vizinhos = calloc(quantidade_vizinhos,sizeof(Vizinhos));

    gera_vizinhos(vizinhos,informacoes,quantidade_vizinhos); /* Gera e armazena todos os vizinhos. */
<<<<<<< HEAD
    for (int i = 0; i < quantidade_vizinhos; i++) /* Para todos os vizinhos gerados, calcula o valor da soma das distâncias mínimas. */
        vizinhos[i].distancia = analisa_solucao(vizinhos[i].vertices_selecionados,informacoes,matriz_adjacencia);

    int indice_melhor = acha_melhor(vizinhos,quantidade_vizinhos); /* Obtém o índice do vizinho com a melhor soma de distâncias. */

    /* Faz o passo da busca local, atualizando a melhor solução disponível, caso ainda não tenha chegado em um máximo local. */
=======
    for (int i = 0; i < quantidade_vizinhos; i++) /* Para todos os vizinhos gerados, calcula o valor da soma das distancias minimas. */
        vizinhos[i].distancia = analisa_solucao(vizinhos[i].vertices_selecionados,informacoes,matriz_adjacencia);

    int indice_melhor = acha_melhor(vizinhos,quantidade_vizinhos); /* Obtem o indice do vizinho com a melhor soma de distancias. */

    /* Faz o passo da busca local, atualizando a melhor solucao disponivel, caso ainda nao tenha chegado em um maximo local. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    if (soma_distancias(solucao_parcial,informacoes) < analisa_solucao(vizinhos[indice_melhor].vertices_selecionados,informacoes,matriz_adjacencia))
    {
        conecta_vertices(solucao_parcial,informacoes,matriz_adjacencia,vizinhos[indice_melhor].vertices_selecionados);
        reordenar_vetores(vizinhos[indice_melhor].vertices_selecionados,informacoes.constante_l,informacoes.conjunto_L,informacoes.cardinalidade_L);
<<<<<<< HEAD
        melhorou = 1; /* Indica que foi obtida uma solução melhor. */
    }

    /* Libera todo o espaço de memória que foi ocupado pela vizinhança. */
=======
        melhorou = 1; /* Indica que foi obtida uma solucao melhor. */
    }

    /* Libera todo o espaco de memoria que foi ocupado pela vizinhanca. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    for (int i = 0; i < quantidade_vizinhos; i++)
        free(vizinhos[i].vertices_selecionados);
    free(vizinhos);

<<<<<<< HEAD
    return melhorou; /* Retorna a informação de que foi obtida uma solução melhor do que a que foi recebida. */
}

/* Função principal para realizar a inicialização de uma solução aleatória, e seguir com a busca local. */
void grasp(float **matriz_adjacencia, Instancia informacoes)
{
    /* Inicializa vetor contendo todas as informações de conexão de vértices entre M e L, que será atualizado nos passos da busca local. */
=======
    return melhorou; /* Retorna a informacao de que foi obtida uma solucao melhor do que a que foi recebida. */
}

/* Funcao principal para realizar a inicializacao de uma solucao aleatoria, e seguir com a busca local. */
void grasp(float **matriz_adjacencia, Instancia informacoes)
{
    /* Inicializa vetor contendo todas as informacoes de conexao de vertices entre M e L, que sera atualizado nos passos da busca local. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    Arestas *solucao_parcial;
    solucao_parcial = calloc(informacoes.cardinalidade_M,sizeof(Arestas));
    for(int i = 0; i < informacoes.cardinalidade_L; i++)
        solucao_parcial[i].distancia = 0;

<<<<<<< HEAD
    /* Inicializa vetor contendo todas as informações de conexão de vértices entre M e L, que contém a melhor solução encontrada,
    considerando todos os inícios aleatórios e todas as buscas locais efetuadas. */
=======
    /* Inicializa vetor contendo todas as informacoes de conexao de vertices entre M e L, que contem a melhor solucao encontrada,
    considerando todos os inicios aleatorios e todas as buscas locais efetuadas. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    Arestas *melhor_solucao;
    melhor_solucao = calloc(informacoes.cardinalidade_M,sizeof(Arestas));
    for(int i = 0; i < informacoes.cardinalidade_L; i++)
        melhor_solucao[i].distancia = 0;

<<<<<<< HEAD
    int melhorou = 1; /* Variável para indicar se uma solução melhor foi obtida. */
=======
    int melhorou = 1; /* Variavel para indicar se uma solucao melhor foi obtida. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)

    float solucoes_iniciais[informacoes.quantidade_inicios]; /* Vetor para armazenar o valor de cada solucao inicial, usada para iniciar a busca local. */
    int melhor_inicio = 0; /* Valor inteiro utilizado para indicar qual foi o valor inicial que resultou na melhor busca local. */

    FILE *arq_saida;
<<<<<<< HEAD
    if (!(arq_saida = fopen(informacoes.nome_arquivo_saida,"w"))) /* Controle dos casos em que não e possivel abrir o arquivo de saída. */
=======
    if (!(arq_saida = fopen(informacoes.nome_arquivo_saida,"w"))) /* Controle dos casos em que nao e possivel abrir o arquivo de saida. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    {
        printf("\nErro na abertura do arquivo texto de saida. Fim do programa.\n");
        system("PAUSE");
        exit(1);
    }

    printf("\nExecutando a busca no arquivo %s...\n", informacoes.nome_arquivo_entrada);

<<<<<<< HEAD
    /* Realiza a quantidade de inícios aleatórios que foi escolhida pelo usuário, selecionando a solução inicial
    de acordo com a meta-heurística GRASP. Após a inicialização, é executada uma busca local, até que um máximo
    local seja atingido. Durante todos os processos, o valor da melhor solução obtida é sempre atualizado e armazenado. */
    for (int i = 0; i < informacoes.quantidade_inicios; i++)
    {
        inicializa_solucao(solucao_parcial,informacoes, matriz_adjacencia); /* Inicializa uma solução de forma gulosa-randomizada, segundo a meta-heurística GRASP. */
        solucoes_iniciais[i] = soma_distancias(solucao_parcial,informacoes); /* Armazena cada uma das soluções, após cada início guloso-randomizado. */
        melhorou = 1; /* Reinicia o valor da variável que indica se a busca deve continuar. */
        while (melhorou == 1) /* Executa a busca local, até atingir um máximo local. */
        {
            melhorou = examina_vizinhanca(solucao_parcial,informacoes,matriz_adjacencia);
            printf("\nDeu um passo, com solucao atual igual a %0.2f\n", soma_distancias(solucao_parcial,informacoes)); /* DESCOMENTAR PARA VER A SOLUÇÃO OBTIDA EM CADA PASSO DE EXECUÇÃO. */
        }

        /* Cada vez que uma solução melhor é obtida, as suas características são armazenadas no vetor destinado para isso. */
=======
    /* Realiza a quantidade de inicios aleatorios que foi escolhida pelo usuario, selecionando a solucao inicial
    de acordo com a meta-heuristica GRASP. Apos a inicializacao, e executada uma busca local, ate que um maximo
    local seja atingido. Durante todos os processos, o valor da melhor solucao obtida e sempre atualizado e armazenado. */
    for (int i = 0; i < informacoes.quantidade_inicios; i++)
    {
        inicializa_solucao(solucao_parcial,informacoes, matriz_adjacencia); /* Inicializa uma solucao de forma gulosa-randomizada, segundo a meta-heuristica GRASP. */
        solucoes_iniciais[i] = soma_distancias(solucao_parcial,informacoes); /* Armazena cada uma das solucoes, apos cada inicio guloso-randomizado. */
        melhorou = 1; /* Reinicia o valor da variavel que indica se a busca deve continuar. */
        while (melhorou == 1) /* Executa a busca local, ate atingir um maximo local. */
        {
            melhorou = examina_vizinhanca(solucao_parcial,informacoes,matriz_adjacencia);
            printf("\nDeu um passo, com solucao atual igual a %0.2f", soma_distancias(solucao_parcial,informacoes)); /* Mostra a solucao obtida em cada passo da execucao. */
        }

        /* Cada vez que uma solucao melhor e obtida, as suas caracteristicas sao armazenadas no vetor destinado para isso. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
        if(soma_distancias(solucao_parcial,informacoes) > soma_distancias(melhor_solucao,informacoes))
        {
            for (int j = 0; j < informacoes.cardinalidade_M; j++)
            {
                melhor_solucao[j].vertice_L = solucao_parcial[j].vertice_L;
                melhor_solucao[j].distancia = solucao_parcial[j].distancia;
                melhor_inicio = i;
            }
        }
    }

    printf("\nFim da busca no arquivo %s.\nArquivo %s com os dados de saida foi gerado.\n\n",informacoes.nome_arquivo_entrada,informacoes.nome_arquivo_saida);

<<<<<<< HEAD
    /* Abaixo, realizamos as impressões das informações da melhor solução obtida com a meta-heurística, no arquivo de saída. */
=======
    /* Abaixo, realizamos as impressoes das informacoes da melhor solucao obtida com a meta-heuristica, no arquivo de saida. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    fprintf(arq_saida,"Arquivo de entrada:\n%s\n", informacoes.nome_arquivo_entrada);
    fprintf(arq_saida,"\nQuantidade de inicios aleatorios:\n%d\n", informacoes.quantidade_inicios);
    fprintf(arq_saida,"\nQuantidade de construcoes em cada inicio:\n%d\n", informacoes.quantidade_construcoes);
    fprintf(arq_saida,"\nQuantidade de participantes do torneio:\n%d\n", informacoes.quantidade_sorteio);
    fprintf(arq_saida,"\nValor da seed:\n%d\n", seed);
    fprintf(arq_saida,"\nValor da solucao inicial:\n%0.2f\n", solucoes_iniciais[melhor_inicio]);
    fprintf(arq_saida,"\nMaior soma de distancias minimas encontrada:\n%0.2f\n", soma_distancias(melhor_solucao,informacoes));
    fprintf(arq_saida,"\nDescricao completa da melhor solucao encontrada:\n");
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
        fprintf(arq_saida,"Vertice %d conectado com vertice %d, com distancia %0.2f\n", i,melhor_solucao[i].vertice_L,melhor_solucao[i].distancia);
    fprintf(arq_saida,"\nValores individuais de cada distancia minima somada:\n");
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
        fprintf(arq_saida,"%0.2f\n",melhor_solucao[i].distancia);

<<<<<<< HEAD
    /* Libera os espaços alocados pelas soluções gravadas, e fecha o arquivo texto de saída. */
=======
    /* Libera os espacos alocados pelas solucoes gravadas, e fecha o arquivo texto de saida. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    free(solucao_parcial);
    free(melhor_solucao);
    fclose(arq_saida);
}

void leitura_arquivo(FILE *arq_entrada, Instancia informacoes) /* Realiza a leitura de todas as linhas do arquivo de entrada. */
{
<<<<<<< HEAD
    /* Obtém as informações da primeira linha do arquivo de entrada, sobre os conjuntos M, L e a quantidade de vértices selecionados. */
=======
    /* Obtem as informacoes da primeira linha do arquivo de entrada, sobre os conjuntos M, L e a quantidade de vertices selecionados. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    fscanf(arq_entrada,"%d %d %d", &informacoes.cardinalidade_M, &informacoes.cardinalidade_L, &informacoes.constante_l);

    informacoes.conjunto_L = calloc(informacoes.cardinalidade_L,sizeof(int));

<<<<<<< HEAD
    /* Inicializa a matriz de adjacencia, que irá conter as distâncias entre os vértices de M e L. */
    float **matriz_adjacencia;

    /* Aloca espaço de memória para a matriz de adjacência. */
=======
    /* Inicializa a matriz de adjacencia, que ira conter as distancias entre os vertices de M e L. */
    float **matriz_adjacencia;

    /* Aloca espaco de memoria para a matriz de adjacancia. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    matriz_adjacencia = calloc(informacoes.cardinalidade_M,sizeof(float*));
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
        matriz_adjacencia[i] = calloc(informacoes.cardinalidade_L,sizeof(float));

<<<<<<< HEAD
    /* Insere todos os valores de distâncias entre vértices na matriz, lendo do arquivo de entrada. */
=======
    /* Insere todos os valores de distancias entre vertices na matriz, lendo do arquivo de entrada. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
        for (int j = 0; j < informacoes.cardinalidade_L; j++)
            fscanf(arq_entrada,"%f",&matriz_adjacencia[i][j]);

    printf("\nArquivo %s indexado com sucesso.\n", informacoes.nome_arquivo_entrada);

<<<<<<< HEAD
    /* Obtém do usuário os parâmetros de entrada para realizar as buscas. */
=======
    /* Obtem do usuario os parametros de entrada para realizar as buscas. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    printf("\nDigite a quantidade de inicios aleatorios da busca:\n");
    scanf("%d", &informacoes.quantidade_inicios);
    printf("\nDigite a quantidade de construcoes em cada inicio aleatorio:\n");
    scanf("%d", &informacoes.quantidade_construcoes);
    printf("\nDigite quantas das melhores solucoes construidas em cada inicio aleatorio participarao da escolha gulosa-randomizada:\n");
    scanf("%d", &informacoes.quantidade_sorteio);

    printf("\nDigite o valor da seed, para geracao de valores aleatorios:\n");
    scanf("%d",&seed);
    srand(seed);

<<<<<<< HEAD
    /* Controla as informações de entrada que o usuário inseriu, para evitar erros de execução. */
=======
    /* Controla as informacoes de entrada que o usuario inseriu, para evitar erros de execucao. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    if (informacoes.quantidade_inicios <= 0 ||
        informacoes.quantidade_sorteio < 1 ||
        informacoes.quantidade_construcoes < informacoes.quantidade_sorteio)
    {
        printf("\nUm ou mais dados foram mal inseridos. Fim do programa.\n");
        fclose(arq_entrada);
        system("PAUSE");
        exit(1);
    }

<<<<<<< HEAD
    /* Realiza as buscas com a meta-heurística GRASP. */
    grasp(matriz_adjacencia, informacoes);

    /* Libera todos os espaços de memória alocados, representando as informações da instância recebida. */
=======
    /* Realiza as buscas com a meta-heuristica GRASP. */
    grasp(matriz_adjacencia, informacoes);

    /* Libera todos os espacos de memoria alocados, representando as informacoes da instancia recebida. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    free(informacoes.conjunto_L);
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
       free(matriz_adjacencia[i]);
    free(matriz_adjacencia);
}

void abre_arquivo(Instancia informacoes) /* Abre e inicia a leitura do arquivo de entrada. */
{
    FILE *arq_entrada;

<<<<<<< HEAD
    if (!(arq_entrada = fopen(informacoes.nome_arquivo_entrada,"r"))) /* Abertura do arquivo de entrada, com controle dos casos em que nao e possivel abrí-lo. */
=======
    if (!(arq_entrada = fopen(informacoes.nome_arquivo_entrada,"r"))) /* Abertura do arquivo de entrada, com controle dos casos em que nao e possivel abri-lo. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    {
        printf("\nErro na abertura do arquivo texto de entrada. Fim do programa.\n");
        system("PAUSE");
        exit(1);
    }

<<<<<<< HEAD
    leitura_arquivo(arq_entrada, informacoes); /* Realiza a indexação de todos os dados do arquivo de entrada, para depois realizar a busca. */
=======
    leitura_arquivo(arq_entrada, informacoes); /* Realiza a indexacao de todos os dados do arquivo de entrada, para depois realizar a busca. */
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    fclose(arq_entrada); /* Fecha o arquivo de entrada que foi lido. */
}

void inicia_programa()
{
<<<<<<< HEAD
=======
    system("clear");
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    printf("OTIMIZACAO COMBINATORIA - 2022/02\n");
    printf("\nTRABALHO FINAL - GRASP - Selecao de Maior Distancia Minima Total\n");
    printf("\nVersao com vizinhanca deterministica\n");
    printf("\nAndrei Pochmann Koenich");
    printf("\nPedro Company Beck\n");
    printf("\n----------------------------------------\n");

    Instancia informacoes;

<<<<<<< HEAD
    /* Obtém do usuário o nome do arquivo de entrada, contendo as informações da instância. */
    printf("Digite o nome do arquivo de entrada:\n");
    gets(informacoes.nome_arquivo_entrada);

    /* Obtém do usuário o nome do arquivo de saída, que irá conter as informações da melhor solução encontrada na busca. */
    printf("\nDigite o nome do arquivo de saida:\n");
    gets(informacoes.nome_arquivo_saida);
=======
    /* Obtem do usuario o nome do arquivo de entrada, contendo as informacoes da instancia. */
    printf("Digite o nome do arquivo de entrada:\n");
    scanf("%s", informacoes.nome_arquivo_entrada);

    /* Obtem do usuario o nome do arquivo de saida, que ira conter as informacoes da melhor solucao encontrada na busca. */
    printf("\nDigite o nome do arquivo de saida:\n");
    scanf("%s", informacoes.nome_arquivo_saida);
>>>>>>> 8b113cc (Adicionando Makefile, melhorando comentarios, adicionando instancias de teste)
    abre_arquivo(informacoes);
}

int main ()
{
    inicia_programa();
    system("PAUSE");
    return 0;
}
