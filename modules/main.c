/*
*	Disciplina: Organização de Arquivos
*	Semestre: 1/2016
*	Professor: André Drummond
*	Título: Simulação de Disco Magnético Rígido
* Alunos: Danilo Santos     140135910
          Marcus Vinicius   130032891
*/

#include <stdio.h>
#include <stdlib.h>

#include "hard_drive.h"
#include "logic_drive.h"

/*Hard Disk*/
track_array c[TRILHA_SUPERFICIE];
track_array *cylinder = c;
//Table of used sectors
fatent blocks[TOTAL_SETORES];
//Table with file name and first sector
fatlist archives[TOTAL_SETORES];

void show_menu(void);

char get_menu_option(void);

int main(void) {
  char option = 0;

  do{
    option = get_menu_option();
    switch( option ){
      case '1':
        system("clear");
        write_file();
        break;
      case '2':
        system("clear");
        read_file();
        break;
      case '3':
        system("clear");
        erase_file();
        break;
      case '4':
        system("clear");
        show_fat_table();
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
  printf("***********************\n");
  printf("*       HARD DISK     *\n");
  printf("***********************\n");

  printf("1 - Escrever Arquivo\n");
  printf("2 - Ler Arquivo\n");
  printf("3 - Apagar Arquivo\n");
  printf("4 - Mostrar tabela FAT\n");
  printf("5 - Sair\n");
}

char get_menu_option(void){
  char option = '0';
  do{
    system("clear");
    show_menu();
    printf("--> ");
    scanf("%c", &option);
  }while( option < '1' || option > '5' );
  return option;
}
