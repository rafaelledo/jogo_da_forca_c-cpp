#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"

int chutesDados = 0;
char palavraSecreta[TAMANHO_PALAVRA], chutes[26];

void abertura()
{
    printf("\n");
    printf("***************************************\n");
    printf("*           Jogo de Forca             *\n");
    printf("***************************************\n");
    printf("\n");
}

void chuta()
{
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    if(letraExiste(chute))
    {
        printf("\nA palavra tem a letra %c\n\n", chute);
    }
    else
    {
        printf("\nA palavra não tem a letra %c\n\n", chute);
    }

    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou(char letra)
{
    int achou = 0;

    for (int j = 0; j < chutesDados; j++)
    {
        if (chutes[j] == letra)
        {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaForca()
{
    int erros = chutesErrados();
    
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
    
    
    
    for (int i = 0; i < strlen(palavraSecreta); i++)
    {
        int achou = jaChutou(palavraSecreta[i]);

        if (achou)
        {
            printf("%c ", palavraSecreta[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void adicionaPalavra()
{
    char opt;

    printf("Você deseja deseja adicionar uma palavra no jogo? (S/N) : ");
    scanf(" %c", &opt);

    if (opt == 'S')
    {
        char novaPalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra?: ");
        scanf("%s", novaPalavra);

        FILE* f = fopen("palavras.txt", "r+");
        if (f == NULL)
        {
            printf("Recurso não disponível\n");
            exit(1);
        }

        int qtdPalavras;
        fscanf(f, "%d", &qtdPalavras);
        qtdPalavras++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtdPalavras);


        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novaPalavra);
        
        fclose(f);
    }
}

void escolhePalavra()
{
    FILE* f = fopen("palavras.txt", "r");
    if (f == NULL)
    {
        printf("Recurso não disponível");
        exit(1);
    }

    int qtdPalavras;
    fscanf(f, "%d", &qtdPalavras);

    srand(time(0));
    int random = rand() % qtdPalavras;

    for (int i = 0; i <= random; i++)
    {
        fscanf(f, "%s", palavraSecreta);
    }


    fclose(f);
}

int letraExiste(char letra)
{
    for (int j = 0; j < strlen(palavraSecreta); j++)
    {
        if(letra == palavraSecreta[j])
        {
            return 1;
        }
    }
    return 0;
}

int chutesErrados()
{
    int erros = 0;

    for (int i = 0; i < chutesDados; i++)
    {
        if (!letraExiste(chutes[i]))
        {
            erros++;
        }
    }
    
    return erros;
}

int enforcou()
{
    return chutesErrados() >= 5;
}

int acertou()
{
    for (int i = 0; i < strlen(palavraSecreta); ++i)
    {
        if (!jaChutou(palavraSecreta[i]))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    system("chcp 65001");
    escolhePalavra();
    abertura();

    do
    {
        desenhaForca();
        chuta();
    } 
    while (!acertou() && !enforcou());
    
    if (acertou())
    {
        printf("\nParabéns, você ganhou!\n\n");
        
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

    }
    else
    {
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavraSecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionaPalavra();
}
