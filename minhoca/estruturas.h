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