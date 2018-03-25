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

    while(1){

        limparTela();
        mostrarTabuleiro();

        Posicao novaPosicao = minhoca.posicao[0];

        tecla = getch();

        switch(tecla){
            case 'w':
            case 'W':
                novaPosicao.x--;
                movimentar(novaPosicao);
                break;
            case 's':
            case 'S':
                novaPosicao.x++;
                movimentar(novaPosicao);
                break;
            case 'a':
            case 'A':
                novaPosicao.y--;
                movimentar(novaPosicao);
                break;
            case 'd':
            case 'D':
                novaPosicao.y++;
                movimentar(novaPosicao);
                break;
            case 'q':
            case 'Q':
                endGame();
                break;
            default:
                printf(MSG_TECLAS_PERMITIDAS);
                break;
        }

        if(doce.vida == 0)
            gerarDoce();

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
        if(pos.x == minhoca.posicao[i].x && pos.y == minhoca.posicao[i].y)
            endGame();

    if(pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 9 )
        endGame();

    if(pos.x == doce.posicao.x && pos.y == doce.posicao.y){
        minhoca.tamanho += 1;
        gerarDoce();
    }

    doce.vida--;
}

void limparTela(){
    system("@cls|clear");
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

void endGame(){

    free(minhoca.posicao);

    printf("Jogo encerrado!\n");
    exit(1);

}