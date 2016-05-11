#include "hard_drive.h"

//QUANT_CLUSTERS ( (SETOR_TRILHA/TAM_CLUSTER)*TRILHA_SUPERFICIE*TRILHA_CILINDRO )
#ifndef LOGIC_DRIVE_MOD
#define LOGIC_DRIVE_MOD

typedef struct fatlist_s {
  char file_name[100];
  unsigned int first_sector;
}fatlist;

typedef struct fatent_s{
  unsigned int used;
  unsigned int eof;
  unsigned int next;
}fatent;

void write_file();

void read_file();

void erase_file();

void show_fat_table();

#endif //LOGIC_DRIVE_MOD
