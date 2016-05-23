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
  for(index = 0 ; index < QUANT_MAX_ARQ ; index++)
    if( !strcmp(name, archives[index].file_name) )
      break;

  if( index != 100){
    FILE *file = fopen("saida.txt","w");
    if( file == NULL ){
      printf("Não foi possivel montar arquivo de saida\n");
      return /*void*/;
    }else{
      //Write the archive into a file
      index = archives[index].first_sector;

      do{
        //Calculte postion on hard disk
        fprintf(file, "%s", cylinder[index/300].track[index%300/60].sector[index%300%60].bytes_s);
        //fprintf(file, "%s", cylinder[z].track[y].sector[x]);
        //Get index new block
        if( blocks[index].eof != 1 ){
          index = blocks[index].next;
        }else{
          break;
        }
        break;
      }while(1);

      fclose(file);
      puts("Sucesso em extracao");
    }
  }

  //printf("nada? nome:%s index:%d", archives[index].file_name, index);

  getchar();
  getchar();
}

void erase_file(){
  char name[20];
  unsigned short int index, hold, control;

  printf("Entre com nome do arquivo : ");
  scanf("%s", name);

  //Search for the name in Fat table
  for(index = 0 ; index < QUANT_MAX_ARQ ; index++)
    if( !strcmp(name, archives[index].file_name) )
      break;

  if( index == QUANT_MAX_ARQ){
    printf("Arquivo não encontrado!!!\n");
  }else{
    hold = index;
    index = archives[index].first_sector;
    do{
      //printf("index:%d\n", index);
      control = index;
      //printf("used:%d\teof:%d\tnext:%d\n",blocks[control].used, blocks[control].eof, blocks[control].next);

      blocks[control].used = 0;
      blocks[control].eof = 0;

      index = blocks[control].next;
      blocks[control].next = 0;
      //printf("used:%d\teof:%d\tnext:%d\n\n",blocks[control].used, blocks[control].eof, blocks[control].next);
    }while( index != 0 );

    //Erase file name
    for(index = 0 ; index < 100 ; index++)
      archives[hold].file_name[index] = '\0';

    printf("Sucesso na deleção!!\n");
  }

  getchar();
  getchar();
}

void show_fat_table(){
  unsigned short int index, index_sector;
  printf("***********************\n");
  printf("*       FAT TABLE     *\n");
  printf("***********************\n");
  printf("NOME:\t\tTAMANHO EM DISCO\t\tLOCALIZAÇÂO\t\n");

  for(index = 0 ; index < QUANT_MAX_ARQ ; index++ ){
    if( archives[index].file_name[0] != '\0' ){
      printf("%s\t", archives[index].file_name);
      index_sector = archives[index].first_sector;
      do{
        printf("%d ", index_sector);
        index_sector = blocks[index_sector].next;
      }while( index_sector != 0 );
      printf("\n");
    }
  }

  getchar();
  getchar();
}
