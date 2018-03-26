/** Tamanho da matrix será 10x10 **/
#define TAM_MATRIZ 10

/** Tamanho inicial da minhoca **/
#define TAM_INICIAL_MINHOCA 3

/** Tamanho maximo da minhoca será 100 **/
#define TAM_MAX_MINHOCA 5

/** Vida do doce **/
#define vida_doce(doce, minhoca) abs(doce.x - minhoca.x) + abs(doce.y - minhoca.y) + 1
//#define VIDA_DOCE 10

/** Símbolo a ser colocado no tabuleiro para representar a minha e o doce **/
#define SIMBOLO '#'

/** Mensagem de teclas **/
#define MSG_TECLAS_PERMITIDAS   "\nTeclas permitidas: \n\
w | W - Cima \n\
s | S - Baixo \n\
a | A - Esquerda \n\
d | D - Direita \n\
q | Q - Sair\n\n"

/** Teclas Permitidas **/
#define DIREITA_1     'd'
#define DIREITA_2     'D'
#define ESQUERDA_1    'a'
#define ESQUERDA_2    'A'
#define CIMA_1        'w'
#define CIMA_2        'W'
#define BAIXO_1       's'
#define BAIXO_2       'S'
#define SAIR_1        'q'
#define SAIR_2        'Q'

/** CORES **/
#define CL_RED     "\x1b[31m"
#define CL_GREEN   "\x1b[32m"
#define CL_YELLOW  "\x1b[33m"
#define CL_BLUE    "\x1b[34m"
#define CL_MAGENTA "\x1b[35m"
#define CL_CYAN    "\x1b[36m"
#define CL_RESET   "\x1b[0m"

/****/

#define DOCE '*'
#define COD_DOCE 'd'
#define COR_DOCE CL_RED

#define MINHOCA 'o'
#define COD_MINHOCA 'm'
#define COR_MINHOCA CL_CYAN

#define COR_PAREDES CL_BLUE

/** END GAME **/
#define GAME_WIN 0
#define GAME_WIN_MSG "\nParabêns, você venceu!\n\n"
#define GAME_LOSE_1 1
#define GAME_LOSE_MSG_1 "\nFim de jogo! Você perdeu!\nNa próxima tente não bater em si mesmo ;-)\n\n"
#define GAME_LOSE_2 2
#define GAME_LOSE_MSG_2 "\nFim de jogo! Você perdeu!\nNa próxima tente não bater nas paredes ;-)\n\n"
#define GAME_EXIT 3
#define GAME_EXIT_MSG "\nEncerrando jogo.\n\n"