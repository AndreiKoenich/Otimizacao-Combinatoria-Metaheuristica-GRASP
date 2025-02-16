/* OTIMIZACAO COMBINATORIA 2022/02 - APLICACAOO DE GRASP NO PROBLEMA DA SELECAO DE MAIOR DISTANCIA MINIMA TOTAL */

/* VERSAO DE BUSCA COM VIZINHANÇA DETERMINISTICA */

/* Andrei Pochmann Koenich - Cartao 00308680 */
/* Pedro Company Beck - Cartao 00324055 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

    char nome_arquivo_entrada[DIMENSAONOME];
    char nome_arquivo_saida[DIMENSAONOME];

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
    int *conjunto_L;

} Instancia;

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
    float distancia;

} Arestas;

/* Obtem o valor minimo entre dois valores inteiros. */
int minimo(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

/* Funcao para posicionar todos os elementos existentes em X nas primeiras posicoes do vetor Y.
Exemplo: para uma entrada X = {4,5,6} e Y = {1,2,3,4,5,6}, com a chamada reordenar_vetores(X,3,Y,6),
teremos como saida X = {4,5,6} e Y = {4,5,6,1,2,3}. */
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

/* Funcao auxiliar do algoritmo quick sort, para realizar uma troca de posicoes entre dois elementos de um vetor. */
void swap(Vizinhos v[], int i, int j)
{
    Vizinhos aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

/* Funcao auxiliar do quicksort para realizar o ordenamento de varias solucoes em ordem decrescente, com particionamento de Hoare. */
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

/* Funcao principal do quicksort para realizar o ordenamento de varias solucoes em ordem decrescente. */
void quickSortStructDecrescente(Vizinhos v[], int p, int r)
{
    if (p < r)
    {
        int posicao = pHoareStructDecrescente(v, p, r);
        quickSortStructDecrescente(v, p, posicao);
        quickSortStructDecrescente(v, posicao+1, r);
    }
}

/* Funcao para percorrer um vetor contendo varias possiveis solucoes, e encontrar o indice da melhor solucao,
ou seja, a solucao que possui o maior valor da soma de distancias minimas. */
int acha_melhor(Vizinhos s[], int quantidade_solucoes)
{
    float melhor_valor = s[0].distancia;
    int indice_melhor = 0;

    /* Percorre todas as solucoes disponiveis, atualizando o melhor valor obtido. */
    for (int i = 1; i < quantidade_solucoes; i++)
        if (melhor_valor < s[i].distancia)
        {
            melhor_valor = s[i].distancia;
            indice_melhor = i;
        }

    return indice_melhor;
}

/* Recebe um conjunto de vertices selecionados de L, e faz a conexao com os vertices de M, gerando uma possivel solucao para o problema. */
void conecta_vertices (Arestas solucao_parcial[], Instancia informacoes, float **matriz_adjacencia, int selecoes[])
{
    float menor_distancia;

    for (int i = 0; i < informacoes.cardinalidade_M; i++)
    {
        /* Inicializa os valores de menor distancia, distancia parcial e do vertice de L selecionado, antes da busca. */
        menor_distancia = matriz_adjacencia[i][selecoes[0]];
        solucao_parcial[i].distancia = menor_distancia;
        solucao_parcial[i].vertice_L = selecoes[0];

        /* Para cada vertice de M, faz a conexao com o vertice de menor distancia, entre os vertices de L selecionados. */
        for (int j = 1; j < informacoes.constante_l; j++)
        {
            /* Atualiza a conexao entre um vertice de M e outro de L, cada vez que uma distancia menor e encontrada. */
            if (matriz_adjacencia[i][selecoes[j]] < menor_distancia)
            {
                menor_distancia = matriz_adjacencia[i][selecoes[j]];
                solucao_parcial[i].distancia = menor_distancia;
                solucao_parcial[i].vertice_L = selecoes[j];
            }
        }
    }
}

/* Recebe um conjunto de vertices selecionados, e retorna a soma das distancias minimas com os vertices de M, para fins de analise. */
float analisa_solucao(int vertices_selecionados[], Instancia informacoes, float **matriz_adjacencia)
{
    float soma_distancias = 0.0;

    for(int i = 0; i < informacoes.cardinalidade_M; i++)
    {
        float menor_distancia = matriz_adjacencia[i][vertices_selecionados[0]];
        for (int j = 1; j < informacoes.constante_l; j++) /* Para cada vertice de M, obtem a menor distancia em relacao a um vertice selecionado em L. */
            if (matriz_adjacencia[i][vertices_selecionados[j]] < menor_distancia)
                menor_distancia = matriz_adjacencia[i][vertices_selecionados[j]];
        soma_distancias += menor_distancia; /* Atualiza a soma das distancias minimas em cada iteracao. */
    }

    return soma_distancias; /* Retorna a soma das distancias minimas. */
}

/* Recebe uma possivel solucao para o problema, e retorna a soma total das distancias minimas entre os vertices de M e os vertices de L selecionados, para fins de analise. */
float soma_distancias(Arestas solucao[], Instancia informacoes)
{
    float somatorio = 0.0;
    for (int i = 0; i < informacoes.cardinalidade_M; i++) /* Faz a soma parcial de cada distancia minima, da possivel solucao. */
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
    for (int i = 0; i < informacoes.quantidade_construcoes; i++)
        free(inicios[i].vertices_selecionados);
    free(inicios);
}

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
    for (int i = 0; i < quantidade_vizinhos; i++)
        for (int j = 0; j < informacoes.constante_l; j++)
            vizinhos[i].vertices_selecionados[j] = informacoes.conjunto_L[j];

    /* Nessa proxima iteracao, ocorrem as permutacoes envolvendo um vertice selecionado e um vertice nao-selecionado,
    para gerar toda a vizinhanca. */
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

/* Funcao para executar a busca local, gerando uma vizinhanca e fazendo uma transicao de forma
gulosa, para a proxima solucao com a maior soma de distancias minimas. */
int examina_vizinhanca (Arestas solucao_parcial[],Instancia informacoes,float **matriz_adjacencia)
{
    int melhorou = 0; /* Variavel para indicar se uma solucao melhor foi obtida. */
    Vizinhos *vizinhos; /* Vetor para conter toda a vizinhanca, durante um passo da busca local. */
    int quantidade_vizinhos = (informacoes.cardinalidade_L-informacoes.constante_l)*(informacoes.constante_l);
    vizinhos = calloc(quantidade_vizinhos,sizeof(Vizinhos));

    gera_vizinhos(vizinhos,informacoes,quantidade_vizinhos); /* Gera e armazena todos os vizinhos. */
    for (int i = 0; i < quantidade_vizinhos; i++) /* Para todos os vizinhos gerados, calcula o valor da soma das distancias minimas. */
        vizinhos[i].distancia = analisa_solucao(vizinhos[i].vertices_selecionados,informacoes,matriz_adjacencia);

    int indice_melhor = acha_melhor(vizinhos,quantidade_vizinhos); /* Obtem o indice do vizinho com a melhor soma de distancias. */

    /* Faz o passo da busca local, atualizando a melhor solucao disponivel, caso ainda nao tenha chegado em um maximo local. */
    if (soma_distancias(solucao_parcial,informacoes) < analisa_solucao(vizinhos[indice_melhor].vertices_selecionados,informacoes,matriz_adjacencia))
    {
        conecta_vertices(solucao_parcial,informacoes,matriz_adjacencia,vizinhos[indice_melhor].vertices_selecionados);
        reordenar_vetores(vizinhos[indice_melhor].vertices_selecionados,informacoes.constante_l,informacoes.conjunto_L,informacoes.cardinalidade_L);
        melhorou = 1; /* Indica que foi obtida uma solucao melhor. */
    }

    /* Libera todo o espaco de memoria que foi ocupado pela vizinhanca. */
    for (int i = 0; i < quantidade_vizinhos; i++)
        free(vizinhos[i].vertices_selecionados);
    free(vizinhos);

    return melhorou; /* Retorna a informacao de que foi obtida uma solucao melhor do que a que foi recebida. */
}

/* Funcao principal para realizar a inicializacao de uma solucao aleatoria, e seguir com a busca local. */
void grasp(float **matriz_adjacencia, Instancia informacoes)
{
    /* Inicializa vetor contendo todas as informacoes de conexao de vertices entre M e L, que sera atualizado nos passos da busca local. */
    Arestas *solucao_parcial;
    solucao_parcial = calloc(informacoes.cardinalidade_M,sizeof(Arestas));
    for(int i = 0; i < informacoes.cardinalidade_L; i++)
        solucao_parcial[i].distancia = 0;

    /* Inicializa vetor contendo todas as informacoes de conexao de vertices entre M e L, que contem a melhor solucao encontrada,
    considerando todos os inicios aleatorios e todas as buscas locais efetuadas. */
    Arestas *melhor_solucao;
    melhor_solucao = calloc(informacoes.cardinalidade_M,sizeof(Arestas));
    for(int i = 0; i < informacoes.cardinalidade_L; i++)
        melhor_solucao[i].distancia = 0;

    int melhorou = 1; /* Variavel para indicar se uma solucao melhor foi obtida. */

    float solucoes_iniciais[informacoes.quantidade_inicios]; /* Vetor para armazenar o valor de cada solucao inicial, usada para iniciar a busca local. */
    int melhor_inicio = 0; /* Valor inteiro utilizado para indicar qual foi o valor inicial que resultou na melhor busca local. */

    FILE *arq_saida;
    if (!(arq_saida = fopen(informacoes.nome_arquivo_saida,"w"))) /* Controle dos casos em que nao e possivel abrir o arquivo de saida. */
    {
        printf("\nErro na abertura do arquivo texto de saida. Fim do programa.\n");
        system("PAUSE");
        exit(1);
    }

    printf("\nExecutando a busca no arquivo %s...\n", informacoes.nome_arquivo_entrada);

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

    /* Abaixo, realizamos as impressoes das informacoes da melhor solucao obtida com a meta-heuristica, no arquivo de saida. */
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

    /* Libera os espacos alocados pelas solucoes gravadas, e fecha o arquivo texto de saida. */
    free(solucao_parcial);
    free(melhor_solucao);
    fclose(arq_saida);
}

void leitura_arquivo(FILE *arq_entrada, Instancia informacoes) /* Realiza a leitura de todas as linhas do arquivo de entrada. */
{
    /* Obtem as informacoes da primeira linha do arquivo de entrada, sobre os conjuntos M, L e a quantidade de vertices selecionados. */
    fscanf(arq_entrada,"%d %d %d", &informacoes.cardinalidade_M, &informacoes.cardinalidade_L, &informacoes.constante_l);

    informacoes.conjunto_L = calloc(informacoes.cardinalidade_L,sizeof(int));

    /* Inicializa a matriz de adjacencia, que ira conter as distancias entre os vertices de M e L. */
    float **matriz_adjacencia;

    /* Aloca espaco de memoria para a matriz de adjacancia. */
    matriz_adjacencia = calloc(informacoes.cardinalidade_M,sizeof(float*));
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
        matriz_adjacencia[i] = calloc(informacoes.cardinalidade_L,sizeof(float));

    /* Insere todos os valores de distancias entre vertices na matriz, lendo do arquivo de entrada. */
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
        for (int j = 0; j < informacoes.cardinalidade_L; j++)
            fscanf(arq_entrada,"%f",&matriz_adjacencia[i][j]);

    printf("\nArquivo %s indexado com sucesso.\n", informacoes.nome_arquivo_entrada);

    /* Obtem do usuario os parametros de entrada para realizar as buscas. */
    printf("\nDigite a quantidade de inicios aleatorios da busca:\n");
    scanf("%d", &informacoes.quantidade_inicios);
    printf("\nDigite a quantidade de construcoes em cada inicio aleatorio:\n");
    scanf("%d", &informacoes.quantidade_construcoes);
    printf("\nDigite quantas das melhores solucoes construidas em cada inicio aleatorio participarao da escolha gulosa-randomizada:\n");
    scanf("%d", &informacoes.quantidade_sorteio);

    printf("\nDigite o valor da seed, para geracao de valores aleatorios:\n");
    scanf("%d",&seed);
    srand(seed);

    /* Controla as informacoes de entrada que o usuario inseriu, para evitar erros de execucao. */
    if (informacoes.quantidade_inicios <= 0 ||
        informacoes.quantidade_sorteio < 1 ||
        informacoes.quantidade_construcoes < informacoes.quantidade_sorteio)
    {
        printf("\nUm ou mais dados foram mal inseridos. Fim do programa.\n");
        fclose(arq_entrada);
        system("PAUSE");
        exit(1);
    }

    /* Realiza as buscas com a meta-heuristica GRASP. */
    grasp(matriz_adjacencia, informacoes);

    /* Libera todos os espacos de memoria alocados, representando as informacoes da instancia recebida. */
    free(informacoes.conjunto_L);
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
       free(matriz_adjacencia[i]);
    free(matriz_adjacencia);
}

void abre_arquivo(Instancia informacoes) /* Abre e inicia a leitura do arquivo de entrada. */
{
    FILE *arq_entrada;

    if (!(arq_entrada = fopen(informacoes.nome_arquivo_entrada,"r"))) /* Abertura do arquivo de entrada, com controle dos casos em que nao e possivel abri-lo. */
    {
        printf("\nErro na abertura do arquivo texto de entrada. Fim do programa.\n");
        system("PAUSE");
        exit(1);
    }

    leitura_arquivo(arq_entrada, informacoes); /* Realiza a indexacao de todos os dados do arquivo de entrada, para depois realizar a busca. */
    fclose(arq_entrada); /* Fecha o arquivo de entrada que foi lido. */
}

void inicia_programa()
{
    system("clear");
    printf("OTIMIZACAO COMBINATORIA - 2022/02\n");
    printf("\nTRABALHO FINAL - GRASP - Selecao de Maior Distancia Minima Total\n");
    printf("\nVersao com vizinhanca deterministica\n");
    printf("\nAndrei Pochmann Koenich");
    printf("\nPedro Company Beck\n");
    printf("\n----------------------------------------\n");

    Instancia informacoes;

    /* Obtem do usuario o nome do arquivo de entrada, contendo as informacoes da instancia. */
    printf("Digite o nome do arquivo de entrada:\n");
    scanf("%s", informacoes.nome_arquivo_entrada);

    /* Obtem do usuario o nome do arquivo de saida, que ira conter as informacoes da melhor solucao encontrada na busca. */
    printf("\nDigite o nome do arquivo de saida:\n");
    scanf("%s", informacoes.nome_arquivo_saida);
    abre_arquivo(informacoes);
}

int main ()
{
    inicia_programa();
    return 0;
}
