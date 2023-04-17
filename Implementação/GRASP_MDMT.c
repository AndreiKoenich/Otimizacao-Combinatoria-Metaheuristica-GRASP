/* OTIMIZA��O COMBINAT�RIA 2022/02 - APLICA��O DE GRASP NO PROBLEMA DA SELE��O DE MAIOR DIST�NCIA M�NIMA TOTAL */

/* VERS�O DE BUSCA COM VIZINHAN�A DETERMIN�STICA */

/* Andrei Pochmann Koenich - Cart�o 00308680 */
/* Pedro Company Beck - Cart�o 00324055 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Valor que representa a quantidade m�xima de caracteres para o nome do arquivo de entrada e o nome do arquivo de sa�da. */
#define DIMENSAONOME 100

/* Vari�vel global inteira representando a seed para gera��o de valores aleat�rios, a ser escolhida pelo usu�rio. */
int seed = 0;

/* Estrutura para armazenar as informa��es da inst�ncia do problema recebida como entrada, al�m dos valores
necess�rios para realizar a busca, escolhidos pelo usu�rio. */
typedef struct
{
    /* Os cinco componentes abaixo s�o par�metros de execu��o escolhidos pelo usu�rio. */

    char nome_arquivo_entrada[DIMENSAONOME];
    char nome_arquivo_saida[DIMENSAONOME];

    /* Representa a quantidade de in�cios gulosos-randomizados que ocorrer�o no processo de busca. */
    int quantidade_inicios;

    /* Representa quantas das melhores solu��es randomizadas de cada constru��o participar�o do sorteio para escolher a
    solu��o inicial do processo de busca local, que ocorrer� ap�s o sorteio. */
    int quantidade_sorteio;

    /* Representa o n�mero total de solu��es randomizadas que ocorrer�o em cada in�cio. Ap�s a gera��o de todas essas
    constru��es, ocorre o sorteio (feito com alguns dos melhores indiv�duos gerados),  para decidir qual das solu��es
    randomizadas que foram geradas ser� considerada para iniciar o processo de busca local. */
    int quantidade_construcoes;

    /* Os quatro componentes abaixo s�o obtidos a partir da leitura do arquivo de entrada .ins */

    /* Representa a quantidade de v�rtices do subgrafo M. */
    int cardinalidade_M;

    /* Representa a quantidade de v�rtices do subgrafo L. */
    int cardinalidade_L;

    /* Representa a quantidade de v�rtices do subgrafo L que ser�o selecionados. */
    int constante_l;

    /* Vetor contendo todos os v�rtices (representados por valores inteiros) do subgrafo L. */
    int *conjunto_L;

} Instancia;

/* Estrutura para representar uma poss�vel solu��o do problema de forma mais simplificada. Essa
estrutura ser� utilizada durante a busca local, para representa��o dos vizinhos. */
typedef struct
{
    int *vertices_selecionados; /* Vetor contendo todos os v�rtices do subgrafo L que foram selecionados. */
    float distancia; /* Valor da soma de todas as dist�ncias m�nimas, representando um valor da fun��o objetivo. */

} Vizinhos;

/* Estrutura para representar, de forma mais completa, uma poss�vel solu��o do problema.
Ao longo do c�digo, ser�o definidos vetores a partir dessa estrutura, com cada �ndice
do vetor representando o v�rtice M, que estar� conectado com um v�rtice L e ter� uma
certa dist�ncia de liga��o. */
typedef struct
{
    /* Representa um v�rtice do subgrafo L que foi selecionado, para estar ligado a um v�rtice do subgrafo M. */
    int vertice_L;

    /* Representa a dist�ncia entre um v�rtice do subgrafo M e um v�rtice do subgrafo L. */
    float distancia;

} Arestas;

/* Obt�m o valor m�nimo entre dois valores inteiros. */
int minimo(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

/* Fun��o para posicionar todos os elementos existentes em X nas primeiras posi��es do vetor Y.
Exemplo: para uma entrada X = {4,5,6} e Y = {1,2,3,4,5,6}, com a chamada reordenar_vetores(X,3,Y,6),
teremos como sa�da X = {4,5,6} e Y = {4,5,6,1,2,3}. */
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

/* Fun��o auxiliar do algoritmo quick sort, para realizar uma troca de posi��es entre dois elementos de um vetor. */
void swap(Vizinhos v[], int i, int j)
{
    Vizinhos aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

/* Fun��o auxiliar do quicksort para realizar o ordenamento de v�rias solu��es em ordem decrescente, com particionamento de Hoare. */
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

/* Fun��o principal do quicksort para realizar o ordenamento de v�rias solu��es em ordem decrescente. */
void quickSortStructDecrescente(Vizinhos v[], int p, int r)
{
    if (p < r)
    {
        int posicao = pHoareStructDecrescente(v, p, r);
        quickSortStructDecrescente(v, p, posicao);
        quickSortStructDecrescente(v, posicao+1, r);
    }
}

/* Fun��o para percorrer um vetor contendo v�rias poss�veis solu��es, e encontrar o �ndice da melhor solu��o,
ou seja, a solu��o que possui o maior valor da soma de dist�ncias m�nimas. */
int acha_melhor(Vizinhos s[], int quantidade_solucoes)
{
    float melhor_valor = s[0].distancia;
    int indice_melhor = 0;

    /* Percorre todas as solu��es dispon�veis, atualizando o melhor valor obtido. */
    for (int i = 1; i < quantidade_solucoes; i++)
        if (melhor_valor < s[i].distancia)
        {
            melhor_valor = s[i].distancia;
            indice_melhor = i;
        }

    return indice_melhor;
}

/* Recebe um conjunto de v�rtices selecionados de L, e faz a conexao com os vertices de M, gerando uma possivel solucao para o problema. */
void conecta_vertices (Arestas solucao_parcial[], Instancia informacoes, float **matriz_adjacencia, int selecoes[])
{
    float menor_distancia;

    for (int i = 0; i < informacoes.cardinalidade_M; i++)
    {
        /* Inicializa os valores de menor dist�ncia, dist�ncia parcial e do v�rtice de L selecionado, antes da busca. */
        menor_distancia = matriz_adjacencia[i][selecoes[0]];
        solucao_parcial[i].distancia = menor_distancia;
        solucao_parcial[i].vertice_L = selecoes[0];

        /* Para cada v�rtice de M, faz a conex�o com o v�rtice de menor distancia, entre os v�rtices de L selecionados. */
        for (int j = 1; j < informacoes.constante_l; j++)
        {
            /* Atualiza a conexao entre um v�rtice de M e outro de L, cada vez que uma distancia menor � encontrada. */
            if (matriz_adjacencia[i][selecoes[j]] < menor_distancia)
            {
                menor_distancia = matriz_adjacencia[i][selecoes[j]];
                solucao_parcial[i].distancia = menor_distancia;
                solucao_parcial[i].vertice_L = selecoes[j];
            }
        }
    }
}

/* Recebe um conjunto de v�rtices selecionados, e retorna a soma das dist�ncias m�nimas com os v�rtices de M, para fins de an�lise. */
float analisa_solucao(int vertices_selecionados[], Instancia informacoes, float **matriz_adjacencia)
{
    float soma_distancias = 0.0;

    for(int i = 0; i < informacoes.cardinalidade_M; i++)
    {
        float menor_distancia = matriz_adjacencia[i][vertices_selecionados[0]];
        for (int j = 1; j < informacoes.constante_l; j++) /* Para cada v�rtice de M, obtem a menor distancia em relacao a um v�rtice selecionado em L. */
            if (matriz_adjacencia[i][vertices_selecionados[j]] < menor_distancia)
                menor_distancia = matriz_adjacencia[i][vertices_selecionados[j]];
        soma_distancias += menor_distancia; /* Atualiza a soma das distancias minimas em cada iteracao. */
    }

    return soma_distancias; /* Retorna a soma das distancias minimas. */
}

/* Recebe uma poss�vel solu��o para o problema, e retorna a soma total das dist�ncias m�nimas entre os v�rtices de M e os v�rtices de L selecionados, para fins de an�lise. */
float soma_distancias(Arestas solucao[], Instancia informacoes)
{
    float somatorio = 0.0;
    for (int i = 0; i < informacoes.cardinalidade_M; i++) /* Faz a soma parcial de cada dist�ncia m�nima, da poss�vel solu��o. */
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

/* Gera uma solu��o inicial do problema, a partir da qual ser� executada uma busca local
at� que seja atingido um m�ximo local. */
void inicializa_solucao (Arestas solucao_inicial[], Instancia informacoes, float **matriz_adjacencia)
{
    /* Preenche todos os v�rtices do conjunto L, sequencialmente. */
    for(int i = 0; i < informacoes.cardinalidade_L; i++)
        informacoes.conjunto_L[i] = i;

    /* Inicializa um vetor com descri��es de v�rias poss�veis solu��es iniciais.
    O n�mero de constru��es iniciais foi definido pelo usu�rio. */
    Vizinhos *inicios;
    inicios = calloc(informacoes.quantidade_construcoes,sizeof(Vizinhos));

    /* Embaralha os v�rtices do conjunto L v�rias vezes, a fim de gerar v�rias sele��es
    randomizadas de "l" v�rtices do conjunto L. */
    for(int i = 0; i < informacoes.quantidade_construcoes; i++)
    {
        inicios[i].vertices_selecionados = calloc(informacoes.constante_l,sizeof(int)); /* Aloca espa�o de mem�ria referente a cada uma das solu��es iniciais. */
        embaralha_vertices(informacoes.conjunto_L,informacoes.cardinalidade_L); /* Embaralha os v�rtices do conjunto L em cada itera��o, para gerar uma nova sele��o de v�rtices. */
        for(int j = 0; j < informacoes.constante_l; j++) /* Obt�m os v�rtices selecionados do conjunto L, ap�s cada embaralhamento. */
            inicios[i].vertices_selecionados[j] = informacoes.conjunto_L[j];
        inicios[i].distancia = analisa_solucao(inicios[i].vertices_selecionados,informacoes,matriz_adjacencia); /* Para cada solu��o gerada, calcula a soma das dist�ncias m�nimas. */
    }

    /* Ordena todas as solu��es iniciais geradas em ordem decrescente com base nas somas das dist�ncias m�nimas totais,
    utilizando o algoritmo quicksort. */
    quickSortStructDecrescente(inicios,0,informacoes.quantidade_construcoes-1);

    /* Ap�s a ordena��o, obt�m de forma aleat�ria qual das melhores solu��es geradas ser� considerada para iniciar a busca local. */
    int indice_vencedor = rand() % informacoes.quantidade_sorteio;

    /* Ap�s obter a solu��o inicial que ser� considerada, realiza as conex�es de v�rtices. */
    conecta_vertices(solucao_inicial,informacoes,matriz_adjacencia,inicios[indice_vencedor].vertices_selecionados);

    /* Ap�s realizar uma sele��o dentro do conjunto L de v�rtices, traz os "l" v�rtices selecionados para as primeiras "l" posi��es
    do vetor contido em informacoes.conjunto_L. Isso � usado posteriormente para gerar as vizinhan�as, na busca local. */
    reordenar_vetores(inicios[indice_vencedor].vertices_selecionados,informacoes.constante_l,informacoes.conjunto_L,informacoes.cardinalidade_L);

    /* Libera todo o espa�o de mem�ria que foi utilizado para a constru��o das solu��es aleat�rias, no in�cio da busca. */
    for (int i = 0; i < informacoes.quantidade_construcoes; i++)
        free(inicios[i].vertices_selecionados);
    free(inicios);
}

/* Fun��o para gerar toda a vizinhan�a, a partir de uma certa solu��o.
A gera��o da vizinhan�a ocorre permutando cada v�rtice que est� selecionado
por um v�rtice que n�o est� selecionado.

Exemplo: se o conjunto L � dado por {1,2,3,4} e, em um determinado ponto da busca
selecionamos os v�rtices {1,2}, ent�o os quatro vizinhos ser�o:

{3, 2} - trocamos o v�rtice 1 (que foi selecionado) pelo v�rtice 3 (que n�o estava selecionado)
{4, 2} - trocamos o v�rtice 1 (que foi selecionado) pelo v�rtice 4 (que n�o estava selecionado)
{1, 3) - trocamos o v�rtice 2 (que foi selecionado) pelo v�rtice 3 (que n�o estava selecionado)
{1, 4} - trocamos o v�rtice 2 (que foi selecionado) pelo v�rtice 4 (que n�o estava selecionado) */
void gera_vizinhos(Vizinhos vizinhos[], Instancia informacoes, int quantidade_vizinhos)
{
    for (int i = 0; i < quantidade_vizinhos; i++) /* Aloca espa�o de mem�ria suficiente para cada vizinho. */
        vizinhos[i].vertices_selecionados = calloc(informacoes.constante_l,sizeof(int));

    /* Transfere o conjunto atual de "l" v�rtices selecionados para o vetor correspondente a cada vizinho,
    para depois permutar os v�rtices, gerando toda a vizinhan�a. */
    for (int i = 0; i < quantidade_vizinhos; i++)
        for (int j = 0; j < informacoes.constante_l; j++)
            vizinhos[i].vertices_selecionados[j] = informacoes.conjunto_L[j];

    /* Nessa pr�xima itera��o, ocorrem as permuta��es envolvendo um v�rtice selecionado e um v�rtice n�o-selecionado,
    para gerar toda a vizinhan�a. */
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

/* Fun��o para executar a busca local, gerando uma vizinhan�a e fazendo uma transi��o de forma
gulosa, para a pr�xima solu��o com a maior soma de dist�ncias m�nimas. */
int examina_vizinhanca (Arestas solucao_parcial[],Instancia informacoes,float **matriz_adjacencia)
{
    int melhorou = 0; /* Vari�vel para indicar se uma solu��o melhor foi obtida. */
    Vizinhos *vizinhos; /* Vetor para conter toda a vizinhan�a, durante um passo da busca local. */
    int quantidade_vizinhos = (informacoes.cardinalidade_L-informacoes.constante_l)*(informacoes.constante_l);
    vizinhos = calloc(quantidade_vizinhos,sizeof(Vizinhos));

    gera_vizinhos(vizinhos,informacoes,quantidade_vizinhos); /* Gera e armazena todos os vizinhos. */
    for (int i = 0; i < quantidade_vizinhos; i++) /* Para todos os vizinhos gerados, calcula o valor da soma das dist�ncias m�nimas. */
        vizinhos[i].distancia = analisa_solucao(vizinhos[i].vertices_selecionados,informacoes,matriz_adjacencia);

    int indice_melhor = acha_melhor(vizinhos,quantidade_vizinhos); /* Obt�m o �ndice do vizinho com a melhor soma de dist�ncias. */

    /* Faz o passo da busca local, atualizando a melhor solu��o dispon�vel, caso ainda n�o tenha chegado em um m�ximo local. */
    if (soma_distancias(solucao_parcial,informacoes) < analisa_solucao(vizinhos[indice_melhor].vertices_selecionados,informacoes,matriz_adjacencia))
    {
        conecta_vertices(solucao_parcial,informacoes,matriz_adjacencia,vizinhos[indice_melhor].vertices_selecionados);
        reordenar_vetores(vizinhos[indice_melhor].vertices_selecionados,informacoes.constante_l,informacoes.conjunto_L,informacoes.cardinalidade_L);
        melhorou = 1; /* Indica que foi obtida uma solu��o melhor. */
    }

    /* Libera todo o espa�o de mem�ria que foi ocupado pela vizinhan�a. */
    for (int i = 0; i < quantidade_vizinhos; i++)
        free(vizinhos[i].vertices_selecionados);
    free(vizinhos);

    return melhorou; /* Retorna a informa��o de que foi obtida uma solu��o melhor do que a que foi recebida. */
}

/* Fun��o principal para realizar a inicializa��o de uma solu��o aleat�ria, e seguir com a busca local. */
void grasp(float **matriz_adjacencia, Instancia informacoes)
{
    /* Inicializa vetor contendo todas as informa��es de conex�o de v�rtices entre M e L, que ser� atualizado nos passos da busca local. */
    Arestas *solucao_parcial;
    solucao_parcial = calloc(informacoes.cardinalidade_M,sizeof(Arestas));
    for(int i = 0; i < informacoes.cardinalidade_L; i++)
        solucao_parcial[i].distancia = 0;

    /* Inicializa vetor contendo todas as informa��es de conex�o de v�rtices entre M e L, que cont�m a melhor solu��o encontrada,
    considerando todos os in�cios aleat�rios e todas as buscas locais efetuadas. */
    Arestas *melhor_solucao;
    melhor_solucao = calloc(informacoes.cardinalidade_M,sizeof(Arestas));
    for(int i = 0; i < informacoes.cardinalidade_L; i++)
        melhor_solucao[i].distancia = 0;

    int melhorou = 1; /* Vari�vel para indicar se uma solu��o melhor foi obtida. */

    float solucoes_iniciais[informacoes.quantidade_inicios]; /* Vetor para armazenar o valor de cada solucao inicial, usada para iniciar a busca local. */
    int melhor_inicio = 0; /* Valor inteiro utilizado para indicar qual foi o valor inicial que resultou na melhor busca local. */

    FILE *arq_saida;
    if (!(arq_saida = fopen(informacoes.nome_arquivo_saida,"w"))) /* Controle dos casos em que n�o e possivel abrir o arquivo de sa�da. */
    {
        printf("\nErro na abertura do arquivo texto de saida. Fim do programa.\n");
        system("PAUSE");
        exit(1);
    }

    printf("\nExecutando a busca no arquivo %s...\n", informacoes.nome_arquivo_entrada);

    /* Realiza a quantidade de in�cios aleat�rios que foi escolhida pelo usu�rio, selecionando a solu��o inicial
    de acordo com a meta-heur�stica GRASP. Ap�s a inicializa��o, � executada uma busca local, at� que um m�ximo
    local seja atingido. Durante todos os processos, o valor da melhor solu��o obtida � sempre atualizado e armazenado. */
    for (int i = 0; i < informacoes.quantidade_inicios; i++)
    {
        inicializa_solucao(solucao_parcial,informacoes, matriz_adjacencia); /* Inicializa uma solu��o de forma gulosa-randomizada, segundo a meta-heur�stica GRASP. */
        solucoes_iniciais[i] = soma_distancias(solucao_parcial,informacoes); /* Armazena cada uma das solu��es, ap�s cada in�cio guloso-randomizado. */
        melhorou = 1; /* Reinicia o valor da vari�vel que indica se a busca deve continuar. */
        while (melhorou == 1) /* Executa a busca local, at� atingir um m�ximo local. */
        {
            melhorou = examina_vizinhanca(solucao_parcial,informacoes,matriz_adjacencia);
            printf("\nDeu um passo, com solucao atual igual a %0.2f\n", soma_distancias(solucao_parcial,informacoes)); /* DESCOMENTAR PARA VER A SOLU��O OBTIDA EM CADA PASSO DE EXECU��O. */
        }

        /* Cada vez que uma solu��o melhor � obtida, as suas caracter�sticas s�o armazenadas no vetor destinado para isso. */
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

    /* Abaixo, realizamos as impress�es das informa��es da melhor solu��o obtida com a meta-heur�stica, no arquivo de sa�da. */
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

    /* Libera os espa�os alocados pelas solu��es gravadas, e fecha o arquivo texto de sa�da. */
    free(solucao_parcial);
    free(melhor_solucao);
    fclose(arq_saida);
}

void leitura_arquivo(FILE *arq_entrada, Instancia informacoes) /* Realiza a leitura de todas as linhas do arquivo de entrada. */
{
    /* Obt�m as informa��es da primeira linha do arquivo de entrada, sobre os conjuntos M, L e a quantidade de v�rtices selecionados. */
    fscanf(arq_entrada,"%d %d %d", &informacoes.cardinalidade_M, &informacoes.cardinalidade_L, &informacoes.constante_l);

    informacoes.conjunto_L = calloc(informacoes.cardinalidade_L,sizeof(int));

    /* Inicializa a matriz de adjacencia, que ir� conter as dist�ncias entre os v�rtices de M e L. */
    float **matriz_adjacencia;

    /* Aloca espa�o de mem�ria para a matriz de adjac�ncia. */
    matriz_adjacencia = calloc(informacoes.cardinalidade_M,sizeof(float*));
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
        matriz_adjacencia[i] = calloc(informacoes.cardinalidade_L,sizeof(float));

    /* Insere todos os valores de dist�ncias entre v�rtices na matriz, lendo do arquivo de entrada. */
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
        for (int j = 0; j < informacoes.cardinalidade_L; j++)
            fscanf(arq_entrada,"%f",&matriz_adjacencia[i][j]);

    printf("\nArquivo %s indexado com sucesso.\n", informacoes.nome_arquivo_entrada);

    /* Obt�m do usu�rio os par�metros de entrada para realizar as buscas. */
    printf("\nDigite a quantidade de inicios aleatorios da busca:\n");
    scanf("%d", &informacoes.quantidade_inicios);
    printf("\nDigite a quantidade de construcoes em cada inicio aleatorio:\n");
    scanf("%d", &informacoes.quantidade_construcoes);
    printf("\nDigite quantas das melhores solucoes construidas em cada inicio aleatorio participarao da escolha gulosa-randomizada:\n");
    scanf("%d", &informacoes.quantidade_sorteio);

    printf("\nDigite o valor da seed, para geracao de valores aleatorios:\n");
    scanf("%d",&seed);
    srand(seed);

    /* Controla as informa��es de entrada que o usu�rio inseriu, para evitar erros de execu��o. */
    if (informacoes.quantidade_inicios <= 0 ||
        informacoes.quantidade_sorteio < 1 ||
        informacoes.quantidade_construcoes < informacoes.quantidade_sorteio)
    {
        printf("\nUm ou mais dados foram mal inseridos. Fim do programa.\n");
        fclose(arq_entrada);
        system("PAUSE");
        exit(1);
    }

    /* Realiza as buscas com a meta-heur�stica GRASP. */
    grasp(matriz_adjacencia, informacoes);

    /* Libera todos os espa�os de mem�ria alocados, representando as informa��es da inst�ncia recebida. */
    free(informacoes.conjunto_L);
    for (int i = 0; i < informacoes.cardinalidade_M; i++)
       free(matriz_adjacencia[i]);
    free(matriz_adjacencia);
}

void abre_arquivo(Instancia informacoes) /* Abre e inicia a leitura do arquivo de entrada. */
{
    FILE *arq_entrada;

    if (!(arq_entrada = fopen(informacoes.nome_arquivo_entrada,"r"))) /* Abertura do arquivo de entrada, com controle dos casos em que nao e possivel abr�-lo. */
    {
        printf("\nErro na abertura do arquivo texto de entrada. Fim do programa.\n");
        system("PAUSE");
        exit(1);
    }

    leitura_arquivo(arq_entrada, informacoes); /* Realiza a indexa��o de todos os dados do arquivo de entrada, para depois realizar a busca. */
    fclose(arq_entrada); /* Fecha o arquivo de entrada que foi lido. */
}

void inicia_programa()
{
    printf("OTIMIZACAO COMBINATORIA - 2022/02\n");
    printf("\nTRABALHO FINAL - GRASP - Selecao de Maior Distancia Minima Total\n");
    printf("\nVersao com vizinhanca deterministica\n");
    printf("\nAndrei Pochmann Koenich");
    printf("\nPedro Company Beck\n");
    printf("\n----------------------------------------\n");

    Instancia informacoes;

    /* Obt�m do usu�rio o nome do arquivo de entrada, contendo as informa��es da inst�ncia. */
    printf("Digite o nome do arquivo de entrada:\n");
    gets(informacoes.nome_arquivo_entrada);

    /* Obt�m do usu�rio o nome do arquivo de sa�da, que ir� conter as informa��es da melhor solu��o encontrada na busca. */
    printf("\nDigite o nome do arquivo de saida:\n");
    gets(informacoes.nome_arquivo_saida);
    abre_arquivo(informacoes);
}

int main ()
{
    inicia_programa();
    system("PAUSE");
    return 0;
}
