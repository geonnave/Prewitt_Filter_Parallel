#include <stdio.h>
#include <stdlib.h>
#define TAM 25

void preenche(int m[TAM][TAM]);                             // preenche a matriz (imagem)
void imprimeI(int m[TAM][TAM]);                             // exibe a matriz (imagem)
void imprimeM(int M[3][3]);                                 // exibe uma máscara, H ou V
void convolucao(int m[TAM][TAM], const int MH[3][3]);    // aplica a máscara, H ou V
void convolucaoV(int m[TAM][TAM]);
void convolucaoH(int m[TAM][TAM]);
void soma();                                                // soma as duas matrizes parciais
void modulo();
void copia(char hv);

int mi[TAM][TAM];                                           // matriz imagem inicial
int mh[TAM][TAM], mv[TAM][TAM];                             // matrizes da imagem aplicado o filtro horizontal e vertical;
int mfprewitt[TAM][TAM];                                    // matriz final com a soma das matrizes mh e mv parciais;
int maux[TAM][TAM];
const int MH[3][3] = {1,1,1, 0,0,0, -1,-1,-1}, MV[3][3] = {-1,0,1, -1,0,1, -1,0,1};    //máscaras horizontais e verticais do Prewitt

int main()
{
    preenche(mi);                                           // gera uma matriz (imagem)

    imprimeI(mi);                                           // imprime a matriz (imagem)

    convolucaoV(mi);                                  // aplica a convolução com a máscara MH

    convolucaoH(mi);                                  // aplica a convolução com a máscara MV

    soma();                                                 // soma as duas matrizes parciais

    printf("\n\033[07;34mCONVOLUÇÃO \033[07;31mFILTRO PREWITT\033[07;34m :                                                \e[m\n\n");

    imprimeI(mfprewitt);                                // imprime a matriz final com o filtro aplicado

    return 0;
}

void convolucaoV(int m[TAM][TAM])
{
    convolucao(m, MV);
    copia('v');
}

void convolucaoH(int m[TAM][TAM])
{
    convolucao(m, MH);
    copia('h');
}

void convolucao(int m[TAM][TAM], const int M[3][3])
{
    int i, j;

    for (i=1; i<TAM-1; i++)
    {
        for (j=1; j<TAM-1; j++)
        {
            //maux[i][j] = m[i][j]*M[1][1] + m[i][j-1]*M[1][0] + m[i+1][j-1]*M[2][0] + m[i+1][j]*M[2][1] + m[i+1][j+1]*M[2][2] + m[i][j+1]*M[1][2] + m[i-1][j+1]*M[0][2] + m[i-1][j]*M[0][1] + m[i-1][j-1]*M[0][0];
            maux[i][j] = m[i][j]*M[1][1];
            maux[i][j] += m[i][j-1]*M[1][0];
            maux[i][j] += m[i+1][j-1]*M[2][0];
            maux[i][j] += m[i+1][j]*M[2][1];
            maux[i][j] += m[i+1][j+1]*M[2][2];
            maux[i][j] += m[i][j+1]*M[1][2];
            maux[i][j] += m[i-1][j+1]*M[0][2];
            maux[i][j] += m[i-1][j]*M[0][1];
            maux[i][j] += m[i-1][j-1]*M[0][0];
        }
    }
}

void copia(char hv)
{
    int i, j;
    if (hv == 'h')
    {
        for (i=1; i<TAM-1; i++)
        {
            for (j=1; j<TAM-1; j++)
            {
                mh[i][j] = maux[i][j];
            }
        }
    }
    else
    {
        for (i=1; i<TAM-1; i++)
        {
            for (j=1; j<TAM-1; j++)
            {
                mv[i][j] = maux[i][j];
            }
        }
    }
}


void preenche(int m[TAM][TAM])
{
    int i, j;
    for (i=1; i<TAM-1; i++)
    {
        for (j=1; j<TAM-1; j++)
        {
            if (i > 4 && i < 14 && j > 4 && j < 14)         // criação de 'objetos' na matriz (imagem)
                m[i][j] = 128;
            else if (i > 10 && i < 20 && j > 10 && j < 22)         // criação de 'objetos' na matriz (imagem)
                m[i][j] = 0;
            else
                m[i][j] = 32;
        }
    }
    return;
}

void soma()
{
    int i, j;
    for (i=0; i<TAM; i++)
    {
        for (j=0; j<TAM; j++)
        {
            mfprewitt[i][j] = mh[i][j] + mv[i][j];
        }
    }
    modulo();
    return;
}

void modulo()
{
    int i, j;
    for (i=1; i<TAM-1; i++)
    {
        for (j=1; j<TAM-1; j++)
        {
            //if (mfprewitt[i][j] < 0 ) mfprewitt[i][j] *= -1;

            //ou

            if (mfprewitt[i][j] < 0 || mfprewitt[i][j] > 255 ) mfprewitt[i][j] = 255;
        }
    }
}

void imprimeI(int m[TAM][TAM])
{
    int i, j;
    printf("\n");
    for (i=1; i<TAM-1; i++)
    {
        for (j=1; j<TAM-1; j++)
        {
            /*if (m[i][j] == 1 || m[i][j] == 2)               // cores adicionadas para facilitar a vizualização
                printf("\033[02;40m  \e[m", m[i][j]);
            else if (m[i][j] != 1 && m[i][j] != 2)
                printf("\033[22;41m  \e[m", m[i][j]);*/
            printf("%3d", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void imprimeM(int M[3][3])
{
    int i, j;
    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            printf("%3d\t", M[i][j]);
        }
        printf("\n\n\n");
    }
    return;
}
