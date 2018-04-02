/**
 * Verifica se as bibliotecas básicas para o funcionamento
 * estão importadas, se não, para a compilação e exibe um erro.
 */
#ifndef _STDIO_H
    #error Inclua a biblioteca <stdio.h>
#endif
#ifndef _STDLIB_H
    #error Inclua a biblioteca <stdlib.h>
#endif
#ifndef _STRING_H
    #error Inclua a biblioteca <string.h>
#endif
#ifndef _TIME_H
    #error Inclua a biblioteca <time.h>
#endif

/**
 * Verifica se o sistema é windows ou linux.
 * Se for linux exibe um warning avisando para qual sistema está compilando,
 * e importa as bibliotecas necessarias para o sistema em questão.
 */
#ifndef __WIN32__
    #warning "Compilando para linux!"
    #include <termios.h>
    #include <unistd.h>
    #include "getch.c"
#else
    #warning "Compilando para windows!"
    #include <conio.h>
    #include <locale.h>
    #ifndef _MALLOC_H_
        #error Inclua a biblioteca <malloc.h>
    #endif
#endif

/**
 * Importa os arquivos do projeto.
 */
#include "contantes.h"
#include "estruturas.h"
#include "prototipos.h"