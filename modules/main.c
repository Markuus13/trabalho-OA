#include <stdio.h>
#include <stdlib.h>

#include "hard_drive.h"

void menu_options();

int main(int argc, char const *argv[]) {
  char option;

  do{
    menu_options();
  }while( option < '1' && option > '5' );

  return 0;
}

void menu_options(){
  printf("1 - Escrever Arquivo\n");
  printf("2 - Ler Arquivo\n");
  printf("3 - Apagar Arquivo\n");
  printf("4 - Mostrar tabela FAT\n");
  printf("5 - Sair\n");
}
