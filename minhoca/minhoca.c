#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include "contantes.h"
#include "estruturas.h"
#include "prototipos.h"

#ifndef __WIN32__
    #include <termios.h>
    #include <unistd.h>
    #include "getch.c"
#else
    #include <conio.h>
#endif

Doce *doce;
Minhoca *minhoca;
char *tabuleiro;

void inicializarConfiguracoes(){

    srand((unsigned) time(NULL));

    tabuleiro = (char *) malloc(sizeof(char) * TAM_MATRIZ * TAM_MATRIZ);

    for(int i = 0; i < TAM_MATRIZ * TAM_MATRIZ; i++)
        *(tabuleiro + i) = '-';

    minhoca = (Minhoca *) malloc(sizeof(Minhoca));
    minhoca->tamanho = TAM_INICIAL_MINHOCA;
    minhoca->posicao = (Posicao *) malloc(sizeof(Posicao) * minhoca->tamanho);

    for(int i = minhoca->tamanho-1; i >= 0; i--)
        setPosicao(minhoca->posicao + i, 0, i);

    doce = (Doce *) malloc(sizeof(Doce));
    doce->posicao = (Posicao *) malloc(sizeof(Posicao));
    gerarDoce();

}

void iniciarJogo(){
    char tecla;

    while(1){

        limparTela();
        mostrarTabuleiro();

        tecla = getch();

        switch(tecla){
            case 'w':
            case 'W':
                movimentar(CIMA);
                break;
            case 's':
            case 'S':
                movimentar(BAIXO);
                break;
            case 'a':
            case 'A':
                movimentar(ESQUERDA);
                break;
            case 'd':
            case 'D':
                movimentar(DIREITA);
                break;
            case 'q':
            case 'Q':
                endGame();
                break;
            default:
                printf(MSG_TECLAS_PERMITIDAS);
                break;
        }

        if(doce->vida == 0)
            gerarDoce();

    }
}

void setPosicao(Posicao *posicao, int posX, int posY){
    *(tabuleiro + ( posX * TAM_MATRIZ ) + posY) = SIMBOLO;
    posicao->x = posX;
    posicao->y = posY;
}

void unsetPosicao(Posicao *posicao){

    int posX = posicao->x;
    int posY = posicao->y;

    if(posX >= 0 && posX <= TAM_MATRIZ && posY >=0 && posY <= TAM_MATRIZ)
        *(tabuleiro + (posX * TAM_MATRIZ) + posY) = '-';

}

void gerarDoce(){

    int x = rand() % TAM_MATRIZ;
    int y = rand() % TAM_MATRIZ;

    doce->vida = VIDA_DOCE;

    unsetPosicao(doce->posicao);

    setPosicao(doce->posicao, x, y);

}

void ponteiroNulo(){}

void movimentar(char direcao){
    switch (direcao){
        case CIMA:
            break;
        case BAIXO:
            baixo();
            break;
        case ESQUERDA:
            esquerda();
            break;
        case DIREITA:
            direita();
            break;
    }
    doce->vida--;
}

void baixo(){

    int x, y, a, b;
    int tamanho = minhoca->tamanho;
    //Posicao *aux = (Posicao *) malloc(sizeof(Posicao));

    unsetMinhocaTabuleiro();

    x = ( minhoca->posicao+tamanho-1 )->x;
    y = ( minhoca->posicao+tamanho-1 )->y;

    if( (x+1) < TAM_MATRIZ )
        (minhoca->posicao+tamanho-1)->x += 1;
    else
        return;

    for(int i = 0; i < tamanho-1; i++){

        a = (minhoca->posicao+i)->x;
        b = (minhoca->posicao+i)->y;

        if( i == 0){
            a = x;
            b = y;
        }

        (minhoca->posicao+i)->x = a;
        (minhoca->posicao+i)->y = b;


    }

    setMinhocaTabuleiro();

    //free(aux);
}

void direita(){

    int y, i;
    int tamanho = minhoca->tamanho;

    unsetMinhocaTabuleiro();

    y = ( minhoca->posicao+tamanho-1 )->y;

    for(i = 0; i < tamanho; i++){
        if( !( y+1 < TAM_MATRIZ ) ) break;

        (minhoca->posicao+i)->y += 1;
    }

    setMinhocaTabuleiro();
}

void esquerda(){

    int y, i;
    int tamanho = minhoca->tamanho;

    unsetMinhocaTabuleiro();

    y = ( minhoca->posicao+0 )->y;

    for(i = 0; i < tamanho; i++){
        if( !( y-1 >= 0 ) ) break;

        (minhoca->posicao+i)->y -= 1;
    }

    setMinhocaTabuleiro();
}

void limparTela(){
    system("@cls|clear");
}

void unsetMinhocaTabuleiro(){
    int x, y;
    for(int i = 0; i < minhoca->tamanho; i++){
        x = (minhoca->posicao+i)->x;
        y = (minhoca->posicao+i)->y;
        *(tabuleiro + (x * TAM_MATRIZ) + y) = '-';
    }
}

void setMinhocaTabuleiro(){
    for(int i = 0; i < minhoca->tamanho; i++){
        int x = (minhoca->posicao+i)->x;
        int y = (minhoca->posicao+i)->y;
        setPosicao(minhoca->posicao + i, x, y);
    }
}

void mostrarTabuleiro(){

    setMinhocaTabuleiro();

    for(int i = 0; i < TAM_MATRIZ * TAM_MATRIZ; i++){
        ((i+1) % TAM_MATRIZ == 1) ? printf("|") : 0;
        printf("%c", *(tabuleiro+i));
        ((i+1) % TAM_MATRIZ == 0) ? printf("|\n") : 0;
    }
}

void endGame(){

    free(minhoca->posicao);
    free(minhoca);
    free(doce->posicao);
    free(doce);
    free(tabuleiro);

    printf("Jogo encerrado!\n");
    exit(1);

}