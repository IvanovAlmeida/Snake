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
 * @fn pausar()
 * @brief Função para pausar a execução do programa
 * @return void
 */
void pausar(){
    printf("Aperte qualquer tecla para continuar...\n");
    getchar();
}

/**
 * @fn mostrarLogo()
 * @brief Mostra o logo do jogo
 * @return void
 */
void mostrarLogo(){
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

/**
 * @fn mostrarTeclasPermitidas()
 * @brief Mostra as teclas permitidas para o funcionamento do jogo. Podem ser alteradas em constantes.h
 * @return void
 */
void mostrarTeclasPermitidas(){

    printf(LIGHT_RED "Teclas permitidas: \n\n");
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Cima \n", CIMA_1, CIMA_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Baixo \n", BAIXO_1, BAIXO_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Esquerda \n", ESQUERDA_1, ESQUERDA_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Direita \n", DIREITA_1, DIREITA_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Salvar jogo\n", SAVE_1, SAVE_2);
    printf(LIGHT_RED "[ %c | %c ] "LIGHT_CYAN" Sair\n\n", SAIR_1, SAIR_2);

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
 * @fn inicializarConfiguracoes()
 * @brief Inicializa as configurações do jogo
 * @return void
 */
void inicializarConfiguracoes(){

    printf(LIGHT_MAGENTA "\nInicializando configurações...\n");

    srand((unsigned) time(NULL));

    /** Se o arquivo não existir é chamado uma função para cria-lo. **/
    if( !abrirArquivo() ) {
        if( !criarArquivo() ) {
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

/**
 * @fn abrirArquivo()
 * @brief Abre o arquivo para salvar o jogo.
 * @return int 0|1
 */
int abrirArquivo(){

    /** Verifica se o arquivo já não está aberto, se estiver ele fecha. **/
    if(saveFile != NULL){
        fclose(saveFile);
        saveFile = NULL;
    }
    /** Se houver sucesso em abrir o arquivo, retorna 1 caso contrario retorna 0 **/
    if( !( saveFile = fopen(FILENAME, "r+") ) )
        return 0;
    return 1;

}

/**
 * @fn criarArquivo()
 * @brief Cria o arquivo para salvar o jogo.
 * @return 0|1
 **/
int criarArquivo(){
    /** Se houver sucesso em criar/abrir o arquivo ele fecha e retorna 1 caso contrario retorna 0 **/
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
 * @fn menuInicial()
 * @brief Menu onde será dicido se irá criar um novo jogo ou continuar.
 * @return void
 */
void menuInicial(){

    char tecla;
    int i, menu = 0;

    jogo = (Jogo *) malloc(sizeof(Jogo)); /** Alocação da variavel jogo **/

    while(1){
        limparTela();
        mostrarLogo();

        if(menu == 0){ /** Primeiro menu **/

            printf( CYAN " Escolha uma das opções: \n");
            printf( MAGENTA " N " CYAN "- Novo jogo \n");
            printf( MAGENTA " C " CYAN "- Continuar \n");
            printf( MAGENTA " Q " CYAN "- Sair \n\n");
            printf( CYAN " => " MAGENTA);

            tecla = getchar();
            getchar();
            menu = 1;

        }else if(menu == 1){ /** Segundo menu **/

            if(tecla == 'N' || tecla == 'n'){                           /** Parte do segundo menu responsavel por criar o novo jogo                 **/

                int jogadorExiste = 0;                                  /** Flag para saber se o jogador já existe                                  **/

                printf( CYAN "Informe o nome para o jogador. Para voltar ao menu principal deixe o nome vazio.\n");
                printf("Nome do jogador: " MAGENTA );
                gets(jogador);

                if(strcmp(jogador, "") == 0){                           /** Verifica se o nome está vazio. Se sim volta ao primeiro menu            **/
                    menu = 0;
                    continue;
                }
                                                                        /** Se não segue com a criação do novo jogo                                 **/
                i = 0;                                                  /** Variavel usada para posicionar o ponteiro em cada indice do arquivo     **/
                fseek(saveFile, sizeof(Jogo) * i, SEEK_SET);            /** Posiciona o ponteiro do arquivo no indice indicado por i                **/
                while( fread(jogo, sizeof(Jogo), 1, saveFile)  ){       /** Le o arquivo                                                            **/
                    if( strcmp(jogador, jogo->jogador) == 0 ){          /** Verifica se o nome que o usuário entrou é igual com algum já existente  **/
                        jogadorExiste = 1;                              /** Se sim salva a flag com valor 1 exibe uma mensagem, pausa o jogo e para o laço de leitura **/
                        printf( LIGHT_RED "Esse nome de jogador já existe. Por favor escolha um novo nome.\n");
                        pausar();
                        break;
                    }
                    i++;
                    fseek(saveFile, sizeof(Jogo) * i, SEEK_SET);
                }
                if(jogadorExiste)                                       /** Verifica a flag, se jogadorExiste = 1 volta ao inicio do menu de criação do novo jogo  **/
                    continue;
                else{
                    posicaoSave = i;                                    /** Se não, salva a posição do indice em posicaoSave - indicado por i -, salva o jogo inicialmente e sai do while **/
                    salvarJogo();
                    break;
                }

            } else if(tecla == 'C' || tecla == 'c'){                    /** Parte do segundo menu responsavel por carregar o jogo existente         **/
                int op;                                                 /** Variavel que salva o indice a ser carregado                             **/
                printf( CYAN " Jogadores salvos: \n");
                i = 0;                                                  /** Variavel usada para posicionar o ponteiro em cada indice do arquivo     **/
                fseek(saveFile, sizeof(Jogo) * i, SEEK_SET);            /** Posiciona o ponteiro do arquivo no indice indicado por i                **/
                while( fread(jogo, sizeof(Jogo), 1, saveFile) ){        /** Le o arquivo                                                            **/
                    printf( CYAN " [ " MAGENTA " %d " CYAN " ] %s\n", (i+1), jogo->jogador);        /** Printa o nome do jogador e um indice                                    **/

                    i++;                                                /** Incrementa i                                                            **/
                    fseek(saveFile, sizeof(Jogo) * i, SEEK_SET);        /** Reposiciona o ponteiro                                                  **/
                }

                printf( CYAN "\n Selecione um indice. Para voltar digite " RED "0" CYAN ".\n");
                printf( CYAN " => " MAGENTA);
                scanf(" %d", &op);
                getchar();

                if(op == 0){                                            /** Se op for igual a 0 volta ao primeiro menu                              **/
                    menu = 0;
                    continue;
                }
                op--;

                if(op >= 0 && op <= i){                                 /** Se op for maior e igual a zero e menor igual a i(que contem o último indice) a opção escolhida é válida**/

                    posicaoSave = op;                                   /** Guarda a posicao                                                        **/
                    carregarJogo();                                     /** Carrega o jogo                                                          **/
                    break;                                              /** Sai do while                                                            **/

                } else {
                    printf("Indice inválido. Tente novamente.\n");
                    pausar();
                }

            } else if(tecla == 'Q' || tecla == 'q'){                    /** Se selecionado Q encerra o jogo                                         **/

                endGame(GAME_EXIT);

            } else {
                printf("Opção inválida!\n");
                pausar();
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
 * @brief Carrega os dados do arquivo para o jogo.
 * @return void
 */
void carregarJogo(){

    fseek(saveFile, sizeof(Jogo) * posicaoSave, SEEK_SET);                              /** Posiciona o ponteiro do arquivo para o indice do jogo   **/
    fread(jogo, sizeof(Jogo), 1, saveFile);                                             /** Le o jogo                                               **/

    strcpy(jogador, jogo->jogador);                                                     /** Copia o nome do jogador para uma variavel global        **/

    doce.vida = jogo->doce.vida;                                                        /** Copia os dados do jogo para as variaveis globais        **/
    doce.posicao.x = jogo->doce.posicao.x;
    doce.posicao.y = jogo->doce.posicao.y;

    minhoca.tamanho = jogo->tamanho_minhoca;
    minhoca.posicao = (Posicao *) realloc(minhoca.posicao, sizeof(Posicao) * minhoca.tamanho);

    for(int k = 0; k < minhoca.tamanho; k++){
        minhoca.posicao[k].x = jogo->minhoca[k].x;
        minhoca.posicao[k].y = jogo->minhoca[k].y;
    }
}

/**
 * @fn salvarJogo()
 * @brief Salva os dados do jogo no arquivo de save
 * @return void
 */
void salvarJogo(){
    int i = 0;

    jogo = (Jogo *) malloc(sizeof(Jogo));                           /** Aloca a variavel jogo                                           **/

    strcpy(jogo->jogador, jogador);                                 /** Copia o nome do jogador da variavel global a variavel jogo      **/

    jogo->doce.vida = doce.vida;                                    /** Copia os dados do jogo para a variavel jogo                     **/
    jogo->doce.posicao.x = doce.posicao.x;
    jogo->doce.posicao.y = doce.posicao.y;
    jogo->tamanho_minhoca = minhoca.tamanho;

    for(i = 0; i < minhoca.tamanho; i++){
        jogo->minhoca[i].x = minhoca.posicao[i].x;
        jogo->minhoca[i].y = minhoca.posicao[i].y;
    }

    fseek(saveFile, sizeof(Jogo) * posicaoSave, SEEK_SET);          /** Posiciona o ponteiro do arquivo no indice do jogo               **/
    fwrite(jogo, sizeof(Jogo), 1, saveFile);                        /** Grava as informações no arquivo                                 **/

    if(jogo != NULL){
        free(jogo);                                                 /** Desaloca memoria da variavel jogo                               **/
        jogo = NULL;
    }
}

/**
 * @fn iniciarJogo()
 * @brief Função responsavel por mostrar o tabuleiro e controlar os movimentos.
 * @return void
 */
void iniciarJogo(){

    limparTela();                                               /** Limpar tela                                             **/

    menuInicial();                                              /** Chama o menu inicial para carregamento/criação do jogo  **/

    char tecla;                                                 /** Variavel que armazena a tecla inserida pelo usuário     **/
    Posicao novaPosicao = minhoca.posicao[0];                   /** Posição atual da "cabeça" da minhoca                    **/

    limparTela();                                               /** Limpa novamente a tela                                  **/
    mostrarTabuleiro();                                         /** Mostra o tabuleiro                                      **/

    while(1){

        tecla = getch();                                        /** Le a entrada do usuário                                 **/

        if( tecla == CIMA_1     || tecla == CIMA_2      ||      /** Verifica se a tecla inserida é válida                   **/
            tecla == BAIXO_1    || tecla == BAIXO_2     ||
            tecla == ESQUERDA_1 || tecla == ESQUERDA_2  ||
            tecla == DIREITA_1  || tecla == DIREITA_2   ||
            tecla == SAIR_1     || tecla == SAIR_2 ) {

            switch (tecla) {                                    /** Se sim, chama uma função correspondente                 **/
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

            if(novaPosicao.x == doce.posicao.x && novaPosicao.y == doce.posicao.y){     /** Verifica se a posicao atual da "cabeça" da minhoca é a mesma da do doce **/
                minhoca.tamanho++;                                                      /** Se for aumenta o tamanho da minhoca e gera outro doce                   **/
                gerarDoce();
            }

            movimentar(novaPosicao);                                                    /** Movimenta a minhoca para nova posição                                   **/

            if(doce.vida == 0)                                                          /** Se a vida do doce chegar a 0, gera um novo doce                         **/
                gerarDoce();

            if(minhoca.tamanho == TAM_MAX_MINHOCA)                                      /** Se a minhoca chegar ao tamanho maximo, encerra o jogo                   **/
                endGame(GAME_WIN);

            limparTela();                                                               /** Limpa tela e mostra o tabuleiro                                         **/
            mostrarTabuleiro();

        } else if( tecla == SAVE_1 || tecla == SAVE_2 ) {                               /** Se a opção chamada for para salvar, salva o jogo                        **/

            salvarJogo();
            printf( LIGHT_GREEN "Jogo salvo com sucesso!\n" WHITE);

        } else {
            limparTela();                                                               /** Se a tecla inserida não for uma das permitidas, mostra o tabuleiro e    **/
            mostrarTabuleiro();                                                         /** uma mensagem com as teclas permitidas                                   **/
            mostrarTeclasPermitidas();
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

    int x = rand() % TAM_MATRIZ;                                     /** Gera números aleatorios de 0 a 10                                       **/
    int y = rand() % TAM_MATRIZ;

    for(int i = 0; i < minhoca.tamanho; i++){                       /** verifica se os numero não coincidem com alguma posição da minhoca       **/
        if(x == minhoca.posicao[i].x && y == minhoca.posicao[i].y){ /** Se sim, gera novos números e começa a verificar de novo                 **/
            x = rand() % TAM_MATRIZ;
            y = rand() % TAM_MATRIZ;
            i = -1;
        }
    }

    doce.posicao.x = x;                                             /** Depois que verifica salva a posição no doce                             **/
    doce.posicao.y = y;

    doce.vida = vida_doce(doce.posicao, minhoca.posicao[0]);        /** Gera a vida do doce de acordo com a posição do doce com a da minhoca    **/
    //doce.vida =  abs(doce.posicao.x - minhoca.posicao[0].x) + abs(doce.posicao.y - minhoca.posicao[0].y)+1;

}

/**
 * @fn mostrarTabuleiro()
 * @brief Função para mostrar o tabuleiro
 * @return void
 */
void mostrarTabuleiro(){

    int i, j, k;

    limpaTabuleiro();                                       /** Limpa o tabuleiro               **/
    setDoceTabuleiro(doce.posicao);                         /** Coloca o doce no tabuleiro      **/
    setMinhocaTabuleiro(minhoca.posicao, minhoca.tamanho);  /** Coloca a minhoca no tabuleiro   **/

    //printf(LIGHT_GREEN "Faltam " LIGHT_RED "%d" LIGHT_GREEN " doces para ganhar!\n" WHITE, TAM_MAX_MINHOCA - minhoca.tamanho);
    printf(LIGHT_GREEN "\nVoce ainda possui " LIGHT_RED "%d" LIGHT_GREEN " movimentos.\n\n", doce.vida); /** Mostra a quantidade de movimentos que ainda restam **/

    for (i = 0; i < TAM_MATRIZ; i++) {                          /**  **/
        for (int j = 0; j < TAM_MATRIZ; j++) {

            if(j == 0)                                          /** Se J for 0 imprime uma parede                                   **/
                printf(COR_PAREDES "|" WHITE);
            if(tabuleiro[i][j] == 'd')                          /** Verifica se é um doce se for imprime o doce no tabuleiro        **/
                printf(COR_DOCE " %c " WHITE, DOCE);
            else if(tabuleiro[i][j] == 'm')                     /** Verifica se é uma parta de minhoca, se for imprime no tabuleiro **/
                printf(COR_MINHOCA " %c " WHITE, MINHOCA);
            else
                printf("   ");                                  /** Se não for nenhuma das opções, imprime espaço em branco         **/
            if(j == TAM_MATRIZ-1)
                printf(COR_PAREDES "|\n" WHITE);                /** Se estiver no fim do tabuleiro imprime uma parede               **/
        }
    }
    printf("\n");
}

/**
 * @fn limpaTabuleiro()
 * @brief Preenche o tabuleiro com t
 * @return void
 */
void limpaTabuleiro(){
    for(int i = 0; i < TAM_MATRIZ; i++)
        for(int j = 0; j < TAM_MATRIZ; j++)
            tabuleiro[i][j] = 't';
}

/**
 * @fn movimentar(Posicao pos)
 * @brief Movimenta a minhoca
 * @param Posicao pos
 * @return void
 */
void movimentar(Posicao pos){

    int i;

    /** Realoca a posição da minhoca **/
    minhoca.posicao = (Posicao *) realloc(minhoca.posicao, sizeof(Posicao) * minhoca.tamanho);

    for(i = minhoca.tamanho - 1; i >= 0 ; i--) {                    /** Laço para percorrer a minhoca de tras para frente   **/
        if( i == 0 ){
            minhoca.posicao[i].x = pos.x;                           /** Se estiver na "cabeça", salva a nova posição nela   **/
            minhoca.posicao[i].y = pos.y;
        } else {
            minhoca.posicao[i].x = minhoca.posicao[i-1].x;          /** Salva a posicao anterior na posição atual           **/
            minhoca.posicao[i].y = minhoca.posicao[i-1].y;
        }
    }

    for(i = 1; i < minhoca.tamanho; i++)                            /** Verifica se a minhoca bateu em si mesma             **/
        if(minhoca.posicao[0].x == minhoca.posicao[i].x &&
           minhoca.posicao[0].y == minhoca.posicao[i].y)
            endGame(GAME_LOSE_1);

    if( minhoca.posicao[0].x < 0 || minhoca.posicao[0].x > 9 ||    /** Verifica se a minhoca não bateu em nenhuma parede   **/
        minhoca.posicao[0].y < 0 || minhoca.posicao[0].y > 9 )
        endGame(GAME_LOSE_2);

}

/**
 * @fn setDoce Tabuleiro
 * @brief  Coloca o código do doce no tabuleiro
 * @param Posicao posicao
 * @return void
 */
void setDoceTabuleiro(Posicao posicao){
    tabuleiro[posicao.x][posicao.y] = COD_DOCE;
}

/**
 * @fn setMinhocaTabuleiro
 * @brief Coloca o código da minhoca no tabuleiro
 * @param Posicao *posicao
 * @param int tamanho
 * @return void
 */
void setMinhocaTabuleiro(Posicao *posicao, int tamanho){
    for(int i = 0; i < tamanho; i++)
        tabuleiro[posicao[i].x][posicao[i].y] = COD_MINHOCA;
}

/**
 * @fn endGame
 * @brief Encerra o jogo, mostrando uma mensagem de acordo com o tipo de encerramento e desaloca a memoria
 * @param int option
 * @return void
 */
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