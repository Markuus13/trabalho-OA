#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "logic_drive.h"
#include "hard_drive.h"

void write_file(){
  char name[20], block;
  int control;
  FILE *file;
  cluster cluster_block;

  printf("Entre com nome do arquivo : ");
  scanf("%s", name);
  file = fopen(name, "r");

  if(file == NULL){
    system("clear");
    printf("Arquivo inexistente!!!\n");
    getchar();
    getchar();
    return /*void*/;
  }else{
    //Split the file into blocks
    do{
      cluster_block = get_cluster();
      if( cluster_block.array_block == NULL ){
        //No more space in disk
        printf("Erro inesperado,\n");
        printf("Sem espaço no disco\n");
        break;
      }else{
        //Get the cluster and write into his blocks
        //while not reach end of file
        puts("Escrevendo");
        for(control = 0 ; control < TAM_SETOR && !feof(file) ; control++ ){
          fscanf(file, "%c", &block);
          printf("%c\n", block);
        }
      }
    }while( !feof(file) );

    getchar();
    getchar();

    fclose(file);
  }
}

void read_file(){
  char name[20];
  unsigned short int index;
  printf("Entre com nome do arquivo : ");
  scanf("%s", name);

  //Search for the name in Fat table
  for(index = 0 ; index < 100 ; index++)
    if( !strcmp(name, archives[index].file_name) )
      break;

      if( index != 100){
        FILE *file = fopen("saida.txt","w");
        if( file == NULL ){
          printf("Não foi possivel montar arquivo de saida\n");
          return /*void*/;
        }else{
          //Write the archive into a file
          fprintf(file, "%s", archives[index].file_name);
          fclose(file);
        }
      }

  printf("nada? nome:%s index:%d", archives[index].file_name, index);

  getchar();
  getchar();
}

void erase_file(){
  char name[20];
  unsigned short int index;

  printf("Entre com nome do arquivo : ");
  scanf("%s", name);

  //Search for the name in Fat table
  for(index = 0 ; index < 100 ; index++)
    if( !strcmp(name, archives[0].file_name) )
      break;

  if( index == 100){
    printf("Arquivo não encontrado!!!\n");
  }

  getchar();
  getchar();
}

void show_fat_table(){
  printf("***********************\n");
  printf("*       FAT TABLE     *\n");
  printf("***********************\n");
  printf("NOME:\t\tTAMANHO EM DISCO\t\tLOCALIZAÇÂO\t\n");

  getchar();
  getchar();
}
