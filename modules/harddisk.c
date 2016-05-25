#include <stdio.h>
#include <string.h>

/*** ESTRUTURAS ***/

/** HD fisico **/
/* Setor */
typedef struct block {
	unsigned char bytes_s[512];
} Block;
/* Trilha */
typedef struct sector_array {
	Block sector[60];
} Sector_array;
/* Cilindro */
typedef struct track_array {
	Sector_array track[5];
} Track_array;

/** FAT Table **/
typedef struct fatlist_s {
	char file_name[100];
	unsigned int first_sector;
} Fatlist;
typedef struct fatent_s {
	unsigned int used;
	unsigned int eof;
	unsigned int next;
} Fatent;

Fatlist fatlist[TOTAL_SETORES];
Fatent fatent[TOTAL_SETORES];

/*** FUNCOES ***/

/** Utilitarios **/

void conteudoArquivo(FILE *fp, char conteudo[]){
	char ch;
	int i=0;

	while ((ch=fscanf(fp,"%c",&ch))!=EOF){
		conteudo[i] = ch;
		i++;
	}
	conteudo[i]='\0';
}

/** Principais **/

/* (5) Sair */
void exit_menu(){
	printf("\n\nO HD foi desligado...\n");
}

/* (1) Escrever Arquivo */
void escreveNoHD(char *nomeDoArquivo){
	int i, j, k;
	int debug = 0;

	/* Itera pelos cilindros do HD */
		for(i=0; i<TOTAL_CILINDROS; i++) {
			/* Itera pelas trilhas dos cilindros */
			for (j=0; j<TRILHAS_POR_CIL; j++){
				/* Procura pelo primeiro CLUSTER livre */
				for (k=0; k<SETORES_POR_TRI; k+=TAM_CLUSTER){

					if (!fatent[k].used && !debug){	/* Cluster livre */
 						/*** Grava o primeiro cluster do arquivo ***/
						/* A fazer */

						/*** Insere o arquivo na tabela FAT na lista de nomes ***/ /* indice do setor na tabela FAT = k + j*60 + i*300 */
						fatlist[k].first_sector = k + j*60 + i*300;
						strcpy(fatlist[k + j*60 + i*300].file_name, nomeDoArquivo);


						/*** Atualiza a lista de setores utilizados da FAT ***/
						fatent[k + j*60 + i*300].used = 1;

						/*** Quantidade de tempo utilizado para gravar o arquivo ***/
						/* assumir seek medio para achar o primeiro cilindro */

						/* Debug */
						debug = 1;
					}
				}
			}
		}
}

void writeFile(Track_array *cylinder){

	char filename[30];
	FILE *fp;


	printf("Entre com o nome do arquivo: ");
	scanf("%s", filename);

	fp = fopen(filename,"r");

	/* Finaliza a funcao caso o aquivo nao exista */
	if (!fp)
		printf("Arquivo nao encontrado!\n\n");

	/* Executa os seguintes passos se ele existir */
	else
		escreveNoHD(filename);

	fclose(fp);

}


int main(){
	printf("%s\n",fatlist[0].file_name);
	printf("%d\n",fatlist[0].first_sector);
	printf("%d\n",fatent[0].used);

return 0;
}
