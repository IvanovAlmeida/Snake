#include <stdio.h>
#include <malloc.h>

typedef struct posicao{
    int x, y;
} Posicao;

void teste(int x, int y){
    printf("%d %d\n", x, y);
}

int main(){

    Posicao *pos;

    pos = (Posicao *) malloc(sizeof(Posicao));

    pos->y = 20;
    pos->x = 10;

    teste(pos->x, pos->y);

    free(pos);

}

