#include "logic_drive.h"
#include "specs.h"

#ifndef HARD_DRIVE_MOD
#define HARD_DRIVE_MOD

/** HD fisico **/
/* Setor */
typedef struct block {
  unsigned char bytes_s[TAM_SETOR];
} block;
/* Trilha */
typedef struct sector_array {
  block sector[SETOR_TRILHA];
} sector_array;
/* Cilindro */
typedef struct track_array {
  sector_array track[TRILHA_CILINDRO];
} track_array;

typedef struct cluster {
  block* array_block;
} cluster;

extern fatent blocks[TOTAL_SETORES];
extern track_array *cylinder;

cluster get_cluster(cluster *,const char *);

#endif /*HARD_DRIVE_MOD*/
