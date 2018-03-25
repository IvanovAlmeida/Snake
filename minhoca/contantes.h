/** Tamanho da matrix será 10x10 **/
#define TAM_MATRIZ 10

/** Tamanho inicial da minhoca **/
#define TAM_INICIAL_MINHOCA 3

/** Tamanho maximo da minhoca será 100 **/
#define TAM_MAX_MINHOCA 100

/** Vida do doce **/
//#define VIDA_DOCE abs(doce.posicao.X - minhoca.posicao[0].X) + abs(doce.posicao.Y - minhoca.posicao[0].Y)
#define VIDA_DOCE 10

/** Símbolo a ser colocado no tabuleiro para representar a minha e o doce **/
#define SIMBOLO '#'

/** Mensagem de teclas **/
#define MSG_TECLAS_PERMITIDAS "Teclas permitidas: Para cima (tecla w|W), para baixo (tecla s|S), esquerda (tecla a|A) e direita (tecla d|D)\n"

/****/

#define DOCE 'o'
#define COD_DOCE 'd'
#define MINHOCA '@'
#define COD_MINHOCA 'm'

/** Teclas **/
#define DIREITA     'd'
#define ESQUERDA    'a'
#define CIMA        'w'
#define BAIXO       's'

/** END GAME **/
#define GAME_WIN 0
#define GAME_WIN_MSG "Parabêns, você venceu.!\n"
#define GAME_LOSE_1 1
#define GAME_LOSE_MSG_1 "Fim de jogo! Você perdeu!\nNa próxima tente não bater em si mesmo ;-)\n"
#define GAME_LOSE_2 2
#define GAME_LOSE_MSG_2 "Fim de jogo! Você perdeu!\nNa próxima tente não bater nas paredes ;-)\n"
#define GAME_EXIT 3
#define GAME_EXIT_MSG "Encerrando jogo.\n"