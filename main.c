#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include "game.h"

#define LINHA 12
#define COLUNA 10
#define TAM 120

int main()
{
    system("mode con: cols=80 lines=32");

    setlocale(LC_ALL, "Portuguese");
    int opcaoMenu = 0;
    struct poltrona sala[TAM];

    iniciarPrograma(sala);

    while(opcaoMenu!=4){

        menu();

        opcaoMenu = escolherOpcao();

        switch(opcaoMenu){
          case 1:
              reservarPoltrona(sala);
              break;
          case 2:
              comprarIngresso(sala);
              break;
          case 3:
              cancelarReserva(sala);
              break;
          case 4:
              limparConsole();
              break;
          default:
              break;
          }
    }

    finalizarPrograma(sala);

    return 0;
}



