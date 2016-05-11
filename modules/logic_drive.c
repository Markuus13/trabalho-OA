#include <stdlib.h>
#include <stdio.h>

void write_file(){
  char name[20];
  FILE *file;

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
    //operation over the file
    fclose(file);
  }
}

void read_file(){
  char name[20];

  printf("Entre com nome do arquivo : ");
  scanf("%s", name);
}

void erase_file(){

}

void show_fat_table(){
  printf("***********************\n");
  printf("*       FAT TABLE     *\n");
  printf("***********************\n");
  printf("NOME:\t\tTAMANHO EM DISCO\t\tLOCALIZAÇÂO\t\n");

  getchar();
  getchar();
}
