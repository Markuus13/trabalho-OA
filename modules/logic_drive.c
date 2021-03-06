#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "logic_drive.h"
#include "hard_drive.h"

void write_file(){
  char nome_arquivo[20], block;
  int control, index;
  FILE *file;
  cluster cluster_block;
  /*Inicialization*/
  cluster_block.array_block = NULL;
  /****************/

  printf("Entre com nome do arquivo : ");
  scanf("%s", nome_arquivo);
  file = fopen(nome_arquivo, "r");

  if(file == NULL){
    system("clear");
    printf("Arquivo inexistente!!!\n");
    getchar();
    getchar();
    return /*void*/;
  }else{
    //Split the file into blocks
    do{
      //Get the cluster and write into his blocks
      //while not reach end of file
      cluster_block = get_cluster( &cluster_block, nome_arquivo);
      if( cluster_block.array_block == NULL ){
        //No more space in disk
        printf("Inexpected error,\n");
        printf("No space on disk!!!\n");
        break;
      }else{
        puts("Escrevendo");
        for( index = 0 ; index < TAM_CLUSTER ; index++ ){
          for( control = 0 ; !feof(file) && control < TAM_SETOR ; control++ ){
            fscanf(file, "%c", &cluster_block.array_block[index].bytes_s[control] );
            //printf("%c\n", cluster_block.array_block[index].bytes_s[control] );
          }
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
        printf("index:%d\ncylinder:%d\ttrack:%d\tsector:%d\n", index, index/300, index%300/60, index%300%60);
        fprintf(file, "%s", cylinder[index/300].track[index%300/60].sector[index%300%60].bytes_s);
        //Get index new block
        if( blocks[index].eof != 1 ){
          index = blocks[index].next;
        }else{
          break;
        }
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

      control = index;

      blocks[control].used = 0;
      blocks[control].eof = 0;

      index = blocks[control].next;
      blocks[control].next = 0;
    }while( index != 0 );

    //Erase file name
    for(index = 0 ; index < 100 ; index++)
      archives[hold].file_name[index] = '\0';

    printf("Sucess on delection!!\n");
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
