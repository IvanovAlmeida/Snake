#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define TAM_MAX_MINHOCA 50

typedef struct { int x, y; } Posicao;

typedef struct { int tamanho; Posicao *posicao; } Minhoca;

typedef struct { int vida; Posicao posicao; } Doce;

typedef struct { char jogador[50]; Doce doce; int tamanho_minhoca; Posicao minhoca[TAM_MAX_MINHOCA]; } Jogo;

int main(){

    FILE *file = fopen("game.txt", "r+");

    Minhoca minhoca;
    Doce doce;

    doce.posicao.x = 5;
    doce.posicao.y = 5;
    doce.vida = 5;

    minhoca.tamanho = 3;
    minhoca.posicao = (Posicao *) malloc(sizeof(Posicao) * 3);

    minhoca.posicao[0].x = 0;
    minhoca.posicao[0].y = 1;
    minhoca.posicao[1].x = 0;
    minhoca.posicao[1].y = 2;
    minhoca.posicao[2].x = 0;
    minhoca.posicao[2].y = 3;

    Jogo *jogo = (Jogo *) malloc(sizeof(Jogo));

//    strcpy(jogo->jogador, "Jogador 3");
//    for(int i = 0; i < minhoca.tamanho; i++){
//        jogo->minhoca[i].x = minhoca.posicao[i].x;
//        jogo->minhoca[i].y = minhoca.posicao[i].y;
//    }
//
//    jogo->doce.vida = doce.vida;
//    jogo->doce.posicao.x = doce.posicao.x;
//    jogo->doce.posicao.y = doce.posicao.y;
//
//    fseek(file, sizeof(Jogo) * 2, SEEK_SET);
//    fwrite(jogo, sizeof(Jogo), 1, file);

    fseek(file, sizeof(Jogo) * 0, SEEK_SET);
    fread(jogo, sizeof(Jogo), 1, file);

    printf("Nome: %s\n", jogo->jogador);
    printf("Vida doce: %d\n", jogo->doce.vida);
    printf("Doce pos X: %d\n", jogo->doce.posicao.x);
    printf("Doce pos Y: %d\n", jogo->doce.posicao.y);

    fseek(file, sizeof(Jogo) * 1, SEEK_SET);
    fread(jogo, sizeof(Jogo), 1, file);

    printf("Nome: %s\n", jogo->jogador);
    printf("Vida doce: %d\n", jogo->doce.vida);
    printf("Doce pos X: %d\n", jogo->doce.posicao.x);
    printf("Doce pos Y: %d\n", jogo->doce.posicao.y);

    fseek(file, sizeof(Jogo) * 2, SEEK_SET);
    fread(jogo, sizeof(Jogo), 1, file);

    printf("Nome: %s\n", jogo->jogador);
    printf("Vida doce: %d\n", jogo->doce.vida);
    printf("Doce pos X: %d\n", jogo->doce.posicao.x);
    printf("Doce pos Y: %d\n", jogo->doce.posicao.y);


    fclose(file);
    free(minhoca.posicao);
    free(jogo);
    jogo = NULL;
    minhoca.posicao = NULL;

    return 1;
}