#include <stdlib.h>
#include <stdio.h>
  
#include "logic_drive.h"
#include "hard_drive.h"

cluster get_cluster(){
  int x, y, z, control;
  cluster new_cluster;
  puts("get a cluster");
  //Search for a free block
  for(z = 0 ; (z < TRILHA_CILINDRO) ; z++)
    for(y = 0 ; (y < TRILHA_SUPERFICIE) ; y++)
      for(x = 0 ; (x < SETOR_TRILHA) ; x++)
        if( blocks[ z + y + x].used != 1 ){
          new_cluster.array_block = cylinder[z].track[y].sector + x;
          break;
        }

  for(control = 0 ; control < TAM_CLUSTER; control++)
    blocks[ z + y + x + control].used = 1;

  new_cluster.array_block = NULL;

  return new_cluster;
}
/*
//Calculo acesso blocos
(SETOR_TRILHA*x)+(TRILHA_SUPERFICIE*y)+(TRILHA_CILINDRO*z)
(x < SETOR_TRILHA) + (y < TRILHA_SUPERFICIE) + (z < TRILHA_CILINDRO)
*/
