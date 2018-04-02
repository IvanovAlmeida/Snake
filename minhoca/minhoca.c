#include "includes.c"

/**
 * Variaveis globais
 */

Doce doce;                              /** Doce **/
Minhoca minhoca;                        /** Minhoca **/

Jogo *jogo;                             /** Variavel para salvar todos os dados do jogo **/
FILE *saveFile;                         /** Arquivo para salvar o jogo **/
int posicaoSave;                        /** Guarda o valor para posicionar o ponteiro do arquivo **/
char jogador[50];                       /** Nome do jogador **/
char tabuleiro[TAM_MATRIZ][TAM_MATRIZ]; /** Tabuleiro do Jogo **/

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

void showLogo(){
    printf("\n" LIGHT_BLUE);
    printf("=========================================================================================\n");
    printf("=                                                                                       =\n");
    printf("=    ***********  *******      *****    **********    *****     *****  ***************  =\n");
    printf("=   ***********   ********     *****   ************   *****    *****   ***************  =\n");
    printf("=  ******         *********    *****  *****    *****  *****   *****    *****            =\n");
    printf("=  ******         **********   *****  *****    *****  *****  *****     *****            =\n");
    printf("=   **********    ***** *****  *****  **************  ***********      ***********      =\n");
    printf("=    **********   *****  ***** *****  **************  ***********      ***********      =\n");
    printf("=         ******  *****   **********  *****    *****  *****  *****     *****            =\n");
    printf("=         ******  *****    *********  *****    *****  *****   *****    *****            =\n");
    printf("=   ***********   *****     ********  *****    *****  *****    *****   ***************  =\n");
    printf("=  ***********    *****      *******  *****    *****  *****     *****  ***************  =\n");
    printf("=                                                                                       =\n");
    printf("=========================================================================================\n");
    printf("\n" WHITE);
}

void carregarJogo(){

    char tecla;
    int i, menu = 0;

    jogo = (Jogo *) malloc(sizeof(Jogo));

    while(1){
        limparTela();
        showLogo();

        if(menu == 0){

            printf(" Escolha uma das opções: \n");
            printf(" N - Novo jogo \n");
            printf(" C - Continuar \n");
            printf(" Q - Sair \n\n");
            printf("=> ");

            tecla = getchar();
            getchar();
            menu = 1;

        }else if(menu == 1){

            if(tecla == 'N' || tecla == 'n'){

                int jogadorExiste = 0;

                printf("Novo jogo. Para voltar ao menu principal deixe o nome vazio.\n");
                printf("Nome do jogador: ");
                gets(jogador);

                if(strcmp(jogador, "") == 0){
                    menu = 0;
                    continue;
                }

                i = 0;
                fseek(saveFile, sizeof(Jogo) * i, SEEK_SET);
                while( fread(jogo, sizeof(Jogo), 1, saveFile)  ){
                    if( strcmp(jogador, jogo->jogador) == 0 ){
                        jogadorExiste = 1;
                        printf("Esse nome de jogador já existe. Por favor escolha um novo nome.\n");
                        pausar();
                        break;
                    }
                    i++;
                    fseek(saveFile, sizeof(Jogo) * i, SEEK_SET);
                }
                if(jogadorExiste)
                    continue;
                else{
                    posicaoSave = i;
                    salvarJogo();
                    break;
                }

            } else if(tecla == 'C' || tecla == 'c'){

                int jogadorExiste = 0;

                printf("Continuar um jogo. Para voltar ao menu principal deixe o nome vazio.\n");
                printf("Nome do jogador: ");
                gets(jogador);

                if(strcmp(jogador, "") == 0){
                    menu = 0;
                    continue;
                }

                i = 0;
                fseek(saveFile, sizeof(Jogo) * i, SEEK_SET);
                while( fread(jogo, sizeof(Jogo), 1, saveFile) ){

                    if( strcmp(jogador, jogo->jogador) == 0 ){
                        jogadorExiste = 1;

                        doce.vida = jogo->doce.vida;
                        doce.posicao.x = jogo->doce.posicao.x;
                        doce.posicao.y = jogo->doce.posicao.y;

                        minhoca.tamanho = jogo->tamanho_minhoca;
                        minhoca.posicao = (Posicao *) realloc(minhoca.posicao, sizeof(Posicao) * minhoca.tamanho);

                        for(int k = 0; k < minhoca.tamanho; k++){
                            minhoca.posicao[k].x = jogo->minhoca[k].x;
                            minhoca.posicao[k].y = jogo->minhoca[k].y;
                        }
                        posicaoSave = i;

                        break;
                    }


                    i++;
                    fseek(saveFile, sizeof(Jogo) * i, SEEK_SET);
                }

                if(!jogadorExiste){
                    printf("Jogador não encontrado! Tente novamente.\n");
                    pausar();
                }else
                    break;

            } else if(tecla == 'Q' || tecla == 'q'){

                endGame(GAME_EXIT);

            } else {

                printf("Opção inválida! \nDigite aperte qualquer tecla para continuar.\n");
                menu = 0;
                getchar();

            }
        }

    }

    if(jogo != NULL){
        free(jogo);
        jogo = NULL;
    }
}

/**
 * @fn iniciarJogo()
 * @brief Função principal do jogo.
 */
void iniciarJogo(){

    limparTela();

    carregarJogo();

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

        } else if( tecla == SAVE_1 || tecla == SAVE_2 ) {

            salvarJogo();
            printf("Jogo salvo com sucesso!\n");

        } else {
            limparTela();
            mostrarTabuleiro();
            mostrarTeclasPermitidas();
        }

    }
}

void pausar(){
    printf("Aperte qualquer tecla para continuar...\n");
    getchar();
}

void salvarJogo(int novoJogo){
    int i = 0;

    jogo = (Jogo *) malloc(sizeof(Jogo));

    strcpy(jogo->jogador, jogador);

    jogo->doce.vida = doce.vida;
    jogo->doce.posicao.x = doce.posicao.x;
    jogo->doce.posicao.y = doce.posicao.y;
    jogo->tamanho_minhoca = minhoca.tamanho;

    for(i = 0; i < minhoca.tamanho; i++){
        jogo->minhoca[i].x = minhoca.posicao[i].x;
        jogo->minhoca[i].y = minhoca.posicao[i].y;
    }

    fseek(saveFile, sizeof(Jogo) * posicaoSave, SEEK_SET);
    fwrite(jogo, sizeof(Jogo), 1, saveFile);

    if(jogo != NULL){
        free(jogo);
        jogo = NULL;
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

    //printf(LIGHT_GREEN "Faltam " LIGHT_RED "%d" LIGHT_GREEN " doces para ganhar!\n" WHITE, TAM_MAX_MINHOCA - minhoca.tamanho);
    printf(LIGHT_GREEN "\nVoce ainda possui " LIGHT_RED "%d" LIGHT_GREEN " movimentos.\n\n", doce.vida);

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

void mostrarTeclasPermitidas(){

    printf(LIGHT_RED "Teclas permitidas: \n\n");
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Cima \n", CIMA_1, CIMA_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Baixo \n", BAIXO_1, BAIXO_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Esquerda \n", ESQUERDA_1, ESQUERDA_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Direita \n", DIREITA_1, DIREITA_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Salvar jogo\n", SAVE_1, SAVE_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Sair\n\n", SAIR_1, SAIR_2);

}

void endGame(int option){

    if(option == GAME_WIN)
        printf( LIGHT_GREEN "%s" WHITE, GAME_WIN_MSG);
    else if(option == GAME_LOSE_1)
        printf( LIGHT_RED "%s" WHITE, GAME_LOSE_MSG_1);
    else if(option == GAME_LOSE_2)
        printf( LIGHT_RED "%s" WHITE, GAME_LOSE_MSG_2);
    else if(option == GAME_EXIT)
        printf( LIGHT_CYAN "%s" WHITE, GAME_EXIT_MSG);

    free(minhoca.posicao);
    fclose(saveFile);

    minhoca.posicao = NULL;
    saveFile = NULL;

    if(jogo != NULL){
        free(jogo);
        jogo = NULL;
    }

    exit(1);
}