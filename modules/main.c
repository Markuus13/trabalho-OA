/*
*	Disciplina: Organização de Arquivos
*	Semestre: 1/2016
*	Prof: André Drummond
*	Título: Simulação de Disco Magnético Rígido
*
*/

#include <stdio.h>
#include <stdlib.h>

#include "hard_drive.h"
#include "logic_drive.h"

/*Hard Disk*/
track_array c[TRILHA_SUPERFICIE];
track_array *cylinder = c;
//Table of used sectors
fatent blocks[SETOR_TRILHA];
//Table with file name and first sector
fatlist archives[QUANT_MAX_ARQ];

void show_menu(void);

char get_menu_option(void);

int main(void) {
  char option = 0;

  /*
  archives[12].file_name[0] = 'D';
  archives[12].first_sector = 0;
  blocks[0].used = 1; blocks[0].eof = 1; blocks[0].next = 1;
  blocks[1].used = 1; blocks[1].eof = 1; blocks[1].next = 0;

  archives[11].file_name[0] = 'B';
  archives[11].first_sector = 5;
  cylinder[5/300].track[5%300/60].sector[5%300%60].bytes_s[0] = 'B';
  cylinder[5/300].track[5%300/60].sector[5%300%60].bytes_s[1] = 'O';
  cylinder[6/300].track[6%300/60].sector[6%300%60].bytes_s[0] = 'B';
  cylinder[6/300].track[6%300/60].sector[6%300%60].bytes_s[1] = 'O';
  blocks[5].used = 1; blocks[5].eof = 0; blocks[5].next = 6;
  blocks[6].used = 1; blocks[6].eof = 0; blocks[6].next = 7;
  blocks[7].used = 1; blocks[7].eof = 1; blocks[7].next = 0;
  */

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
