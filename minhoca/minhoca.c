/**
 * Verifica se as bibliotecas básicas para o funcionamento
 * estão importadas, se não, para a compilação e exibe um erro.
 */
#ifndef _STDIO_H
    #error Inclua a biblioteca <stdio.h>
#endif
#ifndef _STDLIB_H
    #error Inclua a biblioteca <stdlib.h>
#endif
#ifndef _TIME_H
    #error Inclua a biblioteca <time.h>
#endif
#ifndef _MALLOC_H_
#ifdef __WIN32__
    #error Inclua a biblioteca <malloc.h>
#endif
#endif

/**
 * Verifica se o sistema é windows ou linux.
 * Se for linux exibe um warning avisando para qual sistema está compilando,
 * e importa as bibliotecas necessarias para o sistema em questão.
 */
#ifndef __WIN32__
    #warning "Compilando para linux!"
    #include <termios.h>
    #include <unistd.h>
    #include "getch.c"
#else
    #warning "Compilando para windows!"
    #include <conio.h>
#endif

/**
 * Importa os arquivos do projeto.
 */
#include "contantes.h"
#include "estruturas.h"
#include "prototipos.h"

/**
 * Variaveis globais
 */
Doce doce;
Minhoca minhoca;
char tabuleiro[TAM_MATRIZ][TAM_MATRIZ];
FILE *saveFile;

/**
 * @fn inicializarConfiguracoes()
 * @brief Inicializa as configurações do jogo
 */
void inicializarConfiguracoes(){

    printf(LIGHT_MAGENTA "\nInicializando configurações...\n");

    srand((unsigned) time(NULL));

    /** Se o arquivo não existir é chamado uma função para cria-lo. **/
    if( !abrirArquivo() ) {
        if( !criaArquivo() ) {
            printf( RED "Não foi possivel criar o arquivo. Encerrando execução.\n");
            exit(1);
        } else if( !abrirArquivo() ){
            printf( RED "Não foi possivel abrir o arquivo. Encerrando execução.\n");
            exit(1);
        }
    }

    minhoca.tamanho = TAM_INICIAL_MINHOCA;

    while(ponteiroNulo(minhoca.posicao))
        minhoca.posicao = (Posicao *) malloc(sizeof(Posicao) * minhoca.tamanho);

    for(int i = 0; i < minhoca.tamanho; i++){
        minhoca.posicao[i].x = minhoca.tamanho - i - 1;
        minhoca.posicao[i].y = 0;
    }

    gerarDoce();

}

int abrirArquivo(){
    if( !( saveFile = fopen(FILENAME, "r+") ) )
        return 0;
    return 1;
}

int criaArquivo(){
    if(! (saveFile = fopen(FILENAME, "a") )){
        fclose(saveFile);
        saveFile = NULL;
        return 0;
    }
    fclose(saveFile);
    saveFile = NULL;
    return 1;
}

/**
 * @fn iniciarJogo()
 * @brief Função principal do jogo.
 */
void iniciarJogo(){

    char tecla;
    Posicao novaPosicao = minhoca.posicao[0];

    limparTela();
    mostrarTabuleiro();

    while(1){

        tecla = getch();

        if( tecla == CIMA_1     || tecla == CIMA_2      ||
            tecla == BAIXO_1    || tecla == BAIXO_2     ||
            tecla == ESQUERDA_1 || tecla == ESQUERDA_2  ||
            tecla == DIREITA_1  || tecla == DIREITA_2   ||
            tecla == SAIR_1     || tecla == SAIR_2 ) {

            switch (tecla) {
                case CIMA_1:
                case CIMA_2:
                    novaPosicao.x--;
                    doce.vida--;
                    break;
                case BAIXO_1:
                case BAIXO_2:
                    novaPosicao.x++;
                    doce.vida--;
                    break;
                case ESQUERDA_1:
                case ESQUERDA_2:
                    novaPosicao.y--;
                    doce.vida--;
                    break;
                case DIREITA_1:
                case DIREITA_2:
                    novaPosicao.y++;
                    doce.vida--;
                    break;
                case SAIR_1:
                case SAIR_2:
                    endGame(GAME_EXIT);
                    break;
            }

            if(novaPosicao.x == doce.posicao.x && novaPosicao.y == doce.posicao.y){
                minhoca.tamanho++;
                gerarDoce();
            }

            movimentar(novaPosicao);

            if(doce.vida == 0)
                gerarDoce();

            if(minhoca.tamanho == TAM_MAX_MINHOCA)
                endGame(GAME_WIN);

            limparTela();
            mostrarTabuleiro();

        }else{
            limparTela();
            mostrarTabuleiro();
            printf(MSG_TECLAS_PERMITIDAS);
        }

    }
}

/**
 * @fn gerarDoce()
 * @brief gera um novo doce, verificando se não irá aparecer na
 * mesma posição que alguma parte da minhoca
 * @return void
 */
void gerarDoce(){
    int x = rand() % TAM_MATRIZ;
    int y = rand() % TAM_MATRIZ;

    for(int i = 0; i < minhoca.tamanho; i++){
        if(x == minhoca.posicao[i].x && y == minhoca.posicao[i].y){
            x = rand() % TAM_MATRIZ;
            y = rand() % TAM_MATRIZ;
            i = -1;
        }
    }

    doce.posicao.x = x;
    doce.posicao.y = y;

    doce.vida = vida_doce(doce.posicao, minhoca.posicao[0]);
    //doce.vida =  abs(doce.posicao.x - minhoca.posicao[0].x) + abs(doce.posicao.y - minhoca.posicao[0].y)+1;

}

/**
 * @fn ponteiroNule(Posicao *p)
 * @brief Verifica se o ponteiro é nulo, retorna 1 se verdadeiro e 0 se falso.
 * @param Posicao *p
 * @return int 0|1
 */
int ponteiroNulo(Posicao *p){
    return (p == NULL)? 1 : 0;
}

/**
 * @fn movimentar(Posicao pos)
 * @brief Movimenta a minhoca
 * @param Posicao pos
 * @return void
 */
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
        if(minhoca.posicao[0].x == minhoca.posicao[i].x &&
           minhoca.posicao[0].y == minhoca.posicao[i].y)
            endGame(GAME_LOSE_1);

    if( minhoca.posicao[0].x < 0 || minhoca.posicao[0].x > 9 ||
        minhoca.posicao[0].y < 0 || minhoca.posicao[0].y > 9 )
        endGame(GAME_LOSE_2);

}

/**
 * @fn limparTela()
 * @brief Função para limpar a tela
 * @return void
 */
void limparTela(){
#ifndef __WIN32__
    system("clear");
#else
    system("@cls");
#endif
}

/**
 * @fn mostrarTabuleiro()
 * @brief Função para mostrar o tabuleiro
 * @return void
 */
void mostrarTabuleiro(){

    int i, j, k;

    limpaTabuleiro();
    setDoceTabuleiro(doce.posicao);
    setMinhocaTabuleiro(minhoca.posicao, minhoca.tamanho);

    printf(GREEN "Faltam " RED "%d" GREEN " doces para ganhar!\n" WHITE, TAM_MAX_MINHOCA - minhoca.tamanho);
    printf(GREEN "Voce tem " RED "%d" GREEN " movimentos.\n\n", doce.vida);

    for (i = 0; i < TAM_MATRIZ; i++) {
        for (int j = 0; j < TAM_MATRIZ; j++) {

            if(j == 0)
                printf(COR_PAREDES "|" WHITE);
            if(tabuleiro[i][j] == 'd')
                printf(COR_DOCE " %c " WHITE, DOCE);
            else if(tabuleiro[i][j] == 'm')
                printf(COR_MINHOCA " %c " WHITE, MINHOCA);
            else
                printf("   ");
            if(j == TAM_MATRIZ-1)
                printf(COR_PAREDES "|\n" WHITE);
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
        printf( GREEN "%s" WHITE, GAME_WIN_MSG);
    else if(option == GAME_LOSE_1)
        printf( RED "%s" WHITE, GAME_LOSE_MSG_1);
    else if(option == GAME_LOSE_2)
        printf( RED "%s" WHITE, GAME_LOSE_MSG_2);
    else if(option == GAME_EXIT)
        printf( CYAN "%s" WHITE, GAME_EXIT_MSG);

    free(minhoca.posicao);
    fclose(saveFile);

    minhoca.posicao = NULL;
    saveFile = NULL;

    exit(1);
}