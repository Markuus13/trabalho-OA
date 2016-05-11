#include <stdio.h>
#include <stdlib.h>

#include "hard_drive.h"

void show_menu(void);

char get_menu_option(void);

int main(void) {
  char option = 0;

  track_array *cylinder;

  do{
    option = get_menu_option();
    switch( option ){
      case '1':
        break;
      case '2':
        break;
      case '3':
        break;
      case '4':
        break;
      case '5':
        //Leave program
        break;
    }
  }while( option != '5' );

  system("clear");
  printf("Hard Disk had turned off...\n");

  return 0;
}

void show_menu(void){
  printf("1 - Escrever Arquivo\n");
  printf("2 - Ler Arquivo\n");
  printf("3 - Apagar Arquivo\n");
  printf("4 - Mostrar tabela FAT\n");
  printf("5 - Sair\n");
}

char get_menu_option(void){
  char option = 0;

  do{
    system("clear");
    show_menu();
    option = getchar();
  }while( option < '1' || option > '5' );

  return option;
}
