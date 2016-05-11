typedef struct fatlist_s {
  char file_name[100];
  unsigned int first_sector;
}fatlist;

typedef struct fatent_s{
  unsigned int used;
  unsigned int eof;
  unsigned int next;
}fatent;
