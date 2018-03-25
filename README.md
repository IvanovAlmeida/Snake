Inclua a lib minhoca.c

````objectivec
#include "minhoca/minhoca.c"
````

Inicialize as configurações na função main

````objectivec
void main(void){
    inicializarConfiguracoes();
    
    iniciarJogo();
}
````


Compilar:

````commandline
gcc main.c -o main
````