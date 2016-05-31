#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "logic_drive.h"
#include "hard_drive.h"
#include "specs.h"

cluster get_cluster(cluster *clust,char *nome_arquivo){
  int x, y, z, control;
  cluster new_cluster;

  /*Search for a free cluster/sector*/
  for(z = 0 ; (z < TRILHA_SUPERFICIE) ; z++){ /* Cylinder */
    for(y = 0 ; (y < TRILHA_CILINDRO) ; y++){  /* Tracks */
      for(x = 0 ; (x < SETOR_TRILHA) ; x += TAM_CLUSTER){ /* Clusters (tracks) */
        if( blocks[z*300 + y*60 + x].used == 0 ){
          new_cluster.array_block = cylinder[z].track[y].sector + x;
          break;
        }/* if */
      }/* for */
      if( blocks[z*300 + y*60 + x].used == 0 ) break;
    }/* for */
    if( blocks[z*300 + y*60 + x].used == 0 ) break;
  }/* for */

  /*Time of seek*/
  if( ((new_cluster.array_block - clust->array_block)/TAM_CLUSTER) == 1 ){
    operation_time += TEMPO_MIN_SEEK;
  }else{
    operation_time += TEMPO_MEDIO_SEEK;
  }

  /*Mark the next and used sectors*/
  for(control = 0 ; control < TAM_CLUSTER; control++){
    blocks[(z*300 + y*60 + x) + control].used = 1;
    blocks[(z*300 + y*60 + x) + control].next = (z*300 + y*60 + x) + control + 1;
  }
  /*Mark the end of file*/
  blocks[(z*300 + y*60 + x) + control - 1].next = 0;
  blocks[(z*300 + y*60 + x) + control - 1].eof = 1;

  /*If its the first cluster*/
  if( clust->array_block == NULL ){
    /*Insert the file into FAT Table*/
    /*Search for empty space*/
    control = 0;
    while( archives[control].file_name[0] != '\0' && control < QUANT_MAX_ARQ ) control++;

    strcpy(archives[control].file_name,(const char *) nome_arquivo);
    archives[control].first_sector = (z*300 + y*60 + x);
  }else{
              /*Positon of new cluster - Position of old cluster*/
    control = (z*300 + y*60 + x) - (new_cluster.array_block - clust->array_block);
    control += TAM_CLUSTER;
    if( control > 0 )
      control -= 1;

    /*printf("cluster\nactual:%d\tpast:%d\n", (z*300 + y*60 + x), control);*/
    /*Get the index of fourth sector of cluster and change eof*/
    blocks[control].eof = 0;
    blocks[control].next = (z*300 + y*60 + x);

  }

  return new_cluster;
}

int get_file_size(int index_sector){

  int cont = 0;

  do{
      index_sector = blocks[index_sector].next;
      cont++;
    }while( index_sector != 0 );

  return cont * 512;
}
