typedef struct posicao{
    int x, y;
} Posicao;

typedef struct minhoca{
    int tamanho;
    Posicao *posicao;
} Minhoca;

typedef struct doce{
    int vida;
    Posicao *posicao;
} Doce;