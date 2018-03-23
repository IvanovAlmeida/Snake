#include <time.h>
#include <malloc.h>
#include "contantes.h"
#include "estruturas.h"
#include "prototipos.h"

#ifndef  __WIN32__
    #include <ncurses.h>
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

    for(int i = 0; i < minhoca->tamanho; i++)
        setPosicao(minhoca->posicao + i, 0, i);

    doce = (Doce *) malloc(sizeof(Doce));
    doce->posicao = (Posicao *) malloc(sizeof(Posicao));
    gerarDoce();

}

void iniciarJogo(){

    char tecla;
    int continuar = 1;

    while(!kbhit()){

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
                continuar = 0;
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
    printf("%d %d\n", doce->posicao->x, doce->posicao->y);
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
            break;
        case ESQUERDA:
            break;
        case DIREITA:
            break;
    }
    doce->vida--;
}

void limparTela(){
    system("@clear|cls");
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