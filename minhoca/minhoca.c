#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include "contantes.h"
#include "estruturas.h"
#include "prototipos.h"

#ifndef __WIN32__
    #warning "COMPILANDO PARA LINUX"
    #include <termios.h>
    #include <unistd.h>
    #include "getch.c"
#else
    #warning "COMPILANDO PARA WINDOWS"
    #include <conio.h>
#endif


Doce doce;
Minhoca minhoca;
char tabuleiro[TAM_MATRIZ][TAM_MATRIZ];

void inicializarConfiguracoes(){

    srand((unsigned) time(NULL));

    minhoca.tamanho = TAM_INICIAL_MINHOCA;

    minhoca.posicao = (Posicao *) malloc(sizeof(Posicao) * minhoca.tamanho);

    for(int i = 0; i < minhoca.tamanho; i++){
        minhoca.posicao[i].x = minhoca.tamanho - i - 1;
        minhoca.posicao[i].y = 0;
    }

    gerarDoce();

}

void iniciarJogo(){

    char tecla;
    Posicao novaPosicao = minhoca.posicao[0];

    while(1){

        limparTela();
        mostrarTabuleiro();

        tecla = getch();

        switch(tecla){
            case 'w':
            case 'W':
                novaPosicao.x--;
                doce.vida--;
                break;
            case 's':
            case 'S':
                novaPosicao.x++;
                doce.vida--;
                break;
            case 'a':
            case 'A':
                novaPosicao.y--;
                doce.vida--;
                break;
            case 'd':
            case 'D':
                novaPosicao.y++;
                doce.vida--;
                break;
            case 'q':
            case 'Q':
                endGame(GAME_EXIT);
                break;
            default:
                printf(MSG_TECLAS_PERMITIDAS);
                break;
        }

        movimentar(novaPosicao);

        if(doce.vida == 0)
            gerarDoce();

        if(minhoca.tamanho == TAM_MAX_MINHOCA)
            endGame(GAME_WIN);

    }
}

void gerarDoce(){

    int x = rand() % TAM_MATRIZ;
    int y = rand() % TAM_MATRIZ;

    doce.vida = VIDA_DOCE;

    doce.posicao.x = x;
    doce.posicao.y = y;

}

int ponteiroNulo(Posicao *p){
    return (p == NULL)? 1 : 0;
}

void movimentar(Posicao pos){

    int i;

    if(minhoca.posicao[0].x == doce.posicao.x && minhoca.posicao[0].y == doce.posicao.y){
        minhoca.tamanho = minhoca.tamanho+1;
        gerarDoce();
    }

    minhoca.posicao = (Posicao *) realloc(minhoca.posicao, sizeof(Posicao) * minhoca.tamanho);

    for(i = minhoca.tamanho - 1; i >= 0 ; i--) {
        if( i == 0 ){
            minhoca.posicao[i].x = pos.x;
            minhoca.posicao[i].y = pos.y;
        } else {
            minhoca.posicao[i].x = minhoca.posicao[i-1].x;
            minhoca.posicao[i].y = minhoca.posicao[i-1].y;
        }
    }

    for(i = 1; i < minhoca.tamanho; i++)
        if(minhoca.posicao[0].x == minhoca.posicao[i].x && minhoca.posicao[0].y == minhoca.posicao[i].y)
            endGame(GAME_LOSE_1);

    if( minhoca.posicao[0].x < 0 || minhoca.posicao[0].x > 9 ||
        minhoca.posicao[0].y < 0 || minhoca.posicao[0].y > 9 )
        endGame(GAME_LOSE_2);

}

void limparTela(){
#ifndef __WIN32__
    system("clear");
#else
    system("@cls");
#endif
}

void mostrarTabuleiro(){

    int i, j, k;

    limpaTabuleiro();
    setDoceTabuleiro(doce.posicao);
    setMinhocaTabuleiro(minhoca.posicao, minhoca.tamanho);

    for (i = 0; i < TAM_MATRIZ; i++) {
        for (int j = 0; j < TAM_MATRIZ; j++) {

            if(j == 0)
                printf("|");
            if(tabuleiro[i][j] == 'd')
                printf(" %c ", DOCE);
            else if(tabuleiro[i][j] == 'm')
                printf(" %c ", MINHOCA);
            else
                printf("   ");
            if(j == TAM_MATRIZ-1)
                printf("|\n");
        }
    }
    printf("\n");
}

void limpaTabuleiro(){
    for(int i = 0; i < TAM_MATRIZ; i++)
        for(int j = 0; j < TAM_MATRIZ; j++)
            tabuleiro[i][j] = 't';
}

void setDoceTabuleiro(Posicao posicao){
    tabuleiro[posicao.x][posicao.y] = COD_DOCE;
}

void setMinhocaTabuleiro(Posicao *posicao, int tamanho){
    for(int i = 0; i < tamanho; i++)
        tabuleiro[posicao[i].x][posicao[i].y] = COD_MINHOCA;
}

void endGame(int option){

    if(option == GAME_WIN)
        printf("%s", GAME_WIN_MSG);
    else if(option == GAME_LOSE_1)
        printf("%s", GAME_LOSE_MSG_1);
    else if(option == GAME_LOSE_2)
        printf("%s", GAME_LOSE_MSG_2);
    else if(option == GAME_EXIT)
        printf("%s", GAME_EXIT_MSG);

    free(minhoca.posicao);

    exit(1);
}