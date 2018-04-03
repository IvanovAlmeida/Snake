/**
 * Constantes para configuração do jogo,
 * facilitando alterações a gosto do usuário.
 */

#define TAM_MATRIZ          10             /** Tamanho da matrix será 10x10 **/
#define TAM_INICIAL_MINHOCA 3              /** Tamanho inicial da minhoca **/
#define TAM_MAX_MINHOCA     50             /** Tamanho maximo da minhoca será 100 **/
#define vida_doce(doce, minhoca) abs(doce.x - minhoca.x) + abs(doce.y - minhoca.y) + 1 /** Vida do doce **/
#define FILENAME            "minhoca.save" /** Arquivo onde será salvo o progresso do jogo **/

/**
 * Cores
 **/
#define BLACK           "\033[22;30m"
#define RED             "\033[22;31m"
#define GREEN           "\033[22;32m"
#define BROWN           "\033[22;33m"
#define BLUE            "\033[22;34m"
#define MAGENTA         "\033[22;35m"
#define CYAN            "\033[22;36m"
#define GRAY            "\033[22;37m"
#define DARK_GRAY       "\033[01;30m"
#define LIGHT_RED       "\033[01;31m"
#define LIGHT_GREEN     "\033[01;32m"
#define YELLOW          "\033[01;33m"
#define LIGHT_BLUE      "\033[01;34m"
#define LIGHT_MAGENTA   "\033[01;35m"
#define LIGHT_CYAN      "\033[01;36m"
#define WHITE           "\033[01;37m"

/**
 * Teclas Permitidas
 **/
#define DIREITA_1     'd'
#define DIREITA_2     'D'
#define ESQUERDA_1    'a'
#define ESQUERDA_2    'A'
#define CIMA_1        'w'
#define CIMA_2        'W'
#define BAIXO_1       's'
#define BAIXO_2       'S'
#define SAVE_1        'r'
#define SAVE_2        'R'
#define SAIR_1        'q'
#define SAIR_2        'Q'

#define DOCE 'o'             /** Simbolo para o doce no jogo **/
#define COD_DOCE 'd'         /** Código que representa o doce na matriz **/
#define COR_DOCE LIGHT_RED         /** Cor do doce no tabuleiro **/

#define MINHOCA 'o'         /** Simbolo para a minhoca no jogo **/
#define COD_MINHOCA 'm'     /** Código que representa a minhoca na matriz **/
#define COR_MINHOCA LIGHT_CYAN    /** Cor da minhoca no tabuleiro **/

#define COR_PAREDES LIGHT_BLUE /** Cor das paredes no tabuleiro **/

/**
 * Códigos e mensagens para cada
 * tipo de finalização do jogo.
 **/
#define GAME_WIN 0
#define GAME_WIN_MSG        "\nParabêns, você venceu!\n\n"
#define GAME_LOSE_1 1
#define GAME_LOSE_MSG_1     "\nFim de jogo! Você perdeu!\nNa próxima tente não bater em si mesmo ;-)\n\n"
#define GAME_LOSE_2 2
#define GAME_LOSE_MSG_2     "\nFim de jogo! Você perdeu!\nNa próxima tente não bater nas paredes ;-)\n\n"
#define GAME_EXIT 3
#define GAME_EXIT_MSG       "\nEncerrando jogo.\n\n"