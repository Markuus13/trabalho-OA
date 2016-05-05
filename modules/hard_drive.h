/******************************/
/*Especificações HD           */
/******************************/
#define TRILHA_CILINDRO 5
#define SETOR_TRILHA 60
#define TRILHA_SUPERFICIE 10
#define TAM_SETOR 512
#define TAM_CLUSTER 4
/******************************/
#define CILINDROS (TRILHA_SUPERFICIE/2)
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
