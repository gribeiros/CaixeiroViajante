#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct matriz
{
    int **elementos;
} Matriz;

void cria_matriz(Matriz *m, int mat[5][5])
{
    m->elementos = (int **)malloc(5 * sizeof(int *));

    for (int i = 0; i < 5; i++)
    {
        m->elementos[i] = (int *)calloc(5, sizeof(int));
        for (int j = 0; j < 5; j++)
        {
            m->elementos[i][j] = mat[i][j];
        }
    }
}

void imprimir_matriz(Matriz *m)
{
    printf("\nMatriz:\n\n");

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", m->elementos[i][j]);
        }

        printf("\n");
    }
}

void linha()
{
    printf("\n");
    for (int a = 0; a < 50; a++)
    {
        printf("-");
    }
    printf("\n");
}

void construir_caminho(Matriz *m, int *caminho)
{
    int *inseridos = malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        inseridos[i] = FALSE;
    }

    caminho[0] = 0;
    inseridos[0] = TRUE;

    for (int i = 0; i < 5; i++)
    {
        int valor_referencia = __INT_MAX__;
        int vizinho_selecionado = 0;

        for (int j = 0; j < 5; j++)
        {
            if (!inseridos[j] && valor_referencia > m->elementos[i][j])
            {
                vizinho_selecionado = j;
                valor_referencia = m->elementos[i][j];
            }
        }

        caminho[i + 1] = vizinho_selecionado;
        inseridos[vizinho_selecionado] = TRUE;
    }

    caminho[5] = 0;

    free(inseridos);
}

void imprimir_caminho(int n, int *caminho)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%d ", caminho[i]);
    }
    printf("\n");
}

int calcular_custo(Matriz *m, int *caminho)
{
    int custo = 0;

    for (int i = 0; i < 5; i++)
    {
        custo = custo + m->elementos[caminho[i]][caminho[i + 1]];
    }

    return custo;
}

int main()
{
    Matriz m;
    int mat[5][5] = {{0, 185, 119, 152, 133},
                     {185, 0, 121, 150, 200},
                     {199, 121, 0, 174, 120},
                     {152, 150, 174, 0, 199},
                     {133, 200, 120, 199, 0}};

    cria_matriz(&m, mat);
    imprimir_matriz(&m);
    linha();
    int *solucao_inicial = malloc((5 + 1) * sizeof(int));
    construir_caminho(&m, solucao_inicial);
    imprimir_caminho(5 + 1, solucao_inicial);

    int custo_solucao_inicial = calcular_custo(&m, solucao_inicial);
    printf("Custo solução inicial: %d", custo_solucao_inicial);
    return 0;
}