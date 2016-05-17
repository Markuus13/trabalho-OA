#include <stdlib.h>
#include <stdio.h>

#include "hard_drive.h"

cluster get_cluster(){
  cluster new_cluster;
  new_cluster.array_block = NULL;

  return new_cluster;
}
