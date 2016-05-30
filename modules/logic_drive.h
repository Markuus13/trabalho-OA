#include "specs.h"
#ifndef LOGIC_DRIVE_MOD
#define LOGIC_DRIVE_MOD

/** FAT Table **/
typedef struct fatlist_s {
  char file_name[100];
  unsigned int first_sector;
}fatlist;

typedef struct fatent_s{
  unsigned int used;
  unsigned int eof;
  unsigned int next;
}fatent;

extern fatlist archives[TOTAL_SETORES];

void write_file();

void read_file();

void erase_file();

void show_fat_table();

#endif /*LOGIC_DRIVE_MOD*/
