#include <stdio.h>
#include <stdlib.h>


void generate_matriz(int n, int ***matriz)
{
    *matriz = (int **)malloc(n * sizeof(int *));
    int valor = n * n;
    for (int i = 0; i < n; i++)
    {
        (*matriz)[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
            {
                (*matriz)[i][j] = -1;
            }
            else
            {
                (*matriz)[i][j] = valor--;
            }
        }
    }
    int zero_i = 5 % (n - 2) + 1;
    int zero_j = 5 % (n - 2) + 1;
    (*matriz)[zero_i][zero_j] = 0;
}

void imprimir_matriz(int **matriz, int n)
{
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < n - 1; j++)
        {
            if (matriz[i][j] != -1)
            {
                printf("%d ", matriz[i][j]);
            }
            else
            {
                printf("X ");
            }
        }
        printf("\n");
    }
}

void free_matriz(int **matriz, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

int esta_proximo_do_zero(int **matriz, int linha, int coluna, int n)
{
    int vizinhos[4][2] = {
        {linha, coluna + 1},
        {linha, coluna - 1},
        {linha - 1, coluna},
        {linha + 1, coluna}};

    for (int i = 0; i < 4; i++)
    {
        int l = vizinhos[i][0];
        int c = vizinhos[i][1];
        if (l >= 0 && l < n && c >= 0 && c < n && matriz[l][c] == 0)
        {
            return 1;
        }
    }

    return 0;
}

void mover_elemento(int **matriz, int linha, int coluna, int n)
{
    int zero_i, zero_j;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matriz[i][j] == 0)
            {
                zero_i = i;
                zero_j = j;
                break;
            }
        }
    }

    if (matriz[linha][coluna] != -1)
    {
        matriz[zero_i][zero_j] = matriz[linha][coluna];
        matriz[linha][coluna] = 0;
    }
}

void encontrar_posicao_zero(int **matriz, int n, int *linha, int *coluna)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matriz[i][j] == 0)
            {
                *linha = i;
                *coluna = j;
                return;
            }
        }
    }
}

int esta_em_ordem_crescente(int **matriz, int n)
{
    int elementos[n * n];
    int k = 0;
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < n - 1; j++)
        {
            if (matriz[i][j] != 0)
            {
                elementos[k++] = matriz[i][j];
            }
        }
    }

    for (int i = 1; i < k; i++)
    {
        if (elementos[i] < elementos[i - 1])
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    // srand(time(NULL));

    int TAMANHO_TABULEIRO;
    printf("Digite o tamanho do tabuleiro: ");
    scanf("%d", &TAMANHO_TABULEIRO);
    TAMANHO_TABULEIRO += 2;

    int **minha_matriz;
    generate_matriz(TAMANHO_TABULEIRO, &minha_matriz);
    imprimir_matriz(minha_matriz, TAMANHO_TABULEIRO);

    while (1)
    {
        char comando;
        printf("Digite 'w' para cima, 'a' para esquerda, 's' para baixo, 'd' para direita ou 'q' para sair: ");
        scanf(" %c", &comando);

        int zero_i, zero_j;
        encontrar_posicao_zero(minha_matriz, TAMANHO_TABULEIRO, &zero_i,
                               &zero_j);

        if (comando == 'w' && zero_i > 1)
        {
            mover_elemento(minha_matriz, zero_i - 1, zero_j,
                           TAMANHO_TABULEIRO);
        }
        else if (comando == 'a' && zero_j > 1)
        {
            mover_elemento(minha_matriz, zero_i, zero_j - 1,
                           TAMANHO_TABULEIRO);
        }
        else if (comando == 's' && zero_i < TAMANHO_TABULEIRO - 2)
        {
            mover_elemento(minha_matriz, zero_i + 1, zero_j,
                           TAMANHO_TABULEIRO);
        }
        else if (comando == 'd' && zero_j < TAMANHO_TABULEIRO - 2)
        {
            mover_elemento(minha_matriz, zero_i, zero_j + 1,
                           TAMANHO_TABULEIRO);
        }
        else if (comando == 'q')
        {
            break;
        }

        imprimir_matriz(minha_matriz, TAMANHO_TABULEIRO);
    }

    if (esta_em_ordem_crescente(minha_matriz, TAMANHO_TABULEIRO))
    {
        printf("Ganhou!\n");
    }
    else
    {
        printf("Perdeu!\n");
    }

    free_matriz(minha_matriz, TAMANHO_TABULEIRO);

    return 0;
}