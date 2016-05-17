#include "logic_drive.h"

#ifndef HARD_DRIVE_MOD
#define HARD_DRIVE_MOD

/******************************/
/*Especificações HD           */
/******************************/
#define TRILHA_CILINDRO 5
#define SETOR_TRILHA 60
#define TRILHA_SUPERFICIE 10
#define TAM_SETOR 512//bytes
#define TAM_CLUSTER 4//setores
/******************************/
#define TEMPO_MEDIO_SEEK 4//ms
#define TEMPO_MIN_SEEK 1//ms
#define TEMPO_MEDIO_LATENCIA 6//ms
#define TEMPO_TRANSFERENCIA 12//ms/trilha
/******************************/

typedef struct block{
  unsigned char bytes_s[TAM_SETOR];
}block;

typedef struct sector_array{
  block sector[SETOR_TRILHA];
}sector_array;

typedef struct track_array{
  sector_array track[TRILHA_CILINDRO];
} track_array;

typedef struct cluster{
  block* array_block;
}cluster;

extern fatent blocks[SETOR_TRILHA];
extern track_array *cylinder;

cluster get_cluster();

#endif //HARD_DRIVE_MOD
