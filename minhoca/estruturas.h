typedef struct {
    int x, y;
} Posicao;

typedef struct {
    int tamanho;
    Posicao *posicao;
} Minhoca;

typedef struct {
    int vida;
    Posicao posicao;
} Doce;

typedef struct {
    char jogador[50];
    Doce doce;
    int tamanho_minhoca;
    Posicao minhoca[TAM_MAX_MINHOCA];
} Jogo;