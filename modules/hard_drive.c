#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "logic_drive.h"
#include "hard_drive.h"
#include "specs.h"

cluster get_cluster(cluster *clust, const char *nome_arquivo){
  int x, y, z, control;
  cluster new_cluster;

  //Search for a free cluster/sector
  for(z = 0 ; (z < TRILHA_SUPERFICIE) ; z++){ /* Cylinder */
    for(y = 0 ; (y < TRILHA_CILINDRO) ; y++){  /* Tracks */
      for(x = 0 ; (x < SETOR_TRILHA) ; x += TAM_CLUSTER){ /* Clusters (tracks) */
        if( blocks[z*300 + y*60 + x].used == 0 ){
          new_cluster.array_block = cylinder[z].track[y].sector + x;
          break;
        }// if
      }// for
      if( blocks[z*300 + y*60 + x].used == 0 ) break;
    }// for
    if( blocks[z*300 + y*60 + x].used == 0 ) break;
  }//for

  /*If its the first cluster*/
  control = 0;
  if( clust->array_block == NULL ){
    /*Insert the file into FAT Table*/
    /*Search for empty space*/
    while( archives[control].file_name[0] != '\0' && control < QUANT_MAX_ARQ ) control++;

    strcpy(archives[control].file_name, nome_arquivo);
    archives[control].first_sector = (z*300 + y*60 + x);
          
              /* Debug */
              printf("Debug1");
    
  }else{
              /*Positon of new cluster - Position of old cluster*/
    control = (z + y + x) - (clust->array_block - new_cluster.array_block);
    /*Get the index of fourth sector of cluster and change eof*/
    control = archives[control].first_sector + (TAM_CLUSTER - 1);
    blocks[control].eof = 0;
    blocks[control].next = z + y + x;
  }
  /*Mark the next and used sectors*/
  for(control = 0 ; control < TAM_CLUSTER; control++){
    blocks[(z + y + x) + control].used = 1;
    blocks[(z + y + x) + control].next = (z + y + x) + control + 1;
  }
  /*Mark the end of file*/
  blocks[(z + y + x) + control - 1].next = 0;
  blocks[(z + y + x) + control - 1].eof = 1;

  return new_cluster;
}
