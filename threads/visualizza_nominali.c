/*********************
		Punto 6
*********************/
#include "mylib.h"
#include <stdlib.h>
#include <unistd.h> /* fork */
#include <stdio.h> /* I/O */
#include <string.h> /* stringhe */

int viewn() {

	char buffer;
	char mese[9]; /* input mese */
	char file[20]; /* file estrapolato dai vari input */
	char file2[20]; /* file estrapolato dai gruppi */
	char tmp[10];
	char index; /* char temporanei */
	int i; /* var temporanea */
	int count=0; /* numero di righe */
	int anno; /* input anno */
	int days; /* set giorni del mese */
	FILE *stream; /* file csv */

	do{
		printf("[6.] Inserisci Mese: ");
		scanf ("%s", mese);
		flush();
		if (strcmp(mese,"Gennaio")==0) {
			days=31;
			break;
		}
		if (strcmp(mese,"Febbraio")==0) {
			days=28;
			break;
		}
		if (strcmp(mese,"Marzo")==0) {
			days=31;
			break;
		}
		if (strcmp(mese,"Aprile")==0) {
			days=30;
			break;
		}
		if (strcmp(mese,"Maggio")==0) {
			days=31;
			break;
		}
		if (strcmp(mese,"Giugno")==0) {
			days=30;
			break;
		}
		if (strcmp(mese,"Luglio")==0) {
			days=31;
			break;
		}
		if (strcmp(mese,"Agosto")==0) {
			days=31;
			break;
		}
		if (strcmp(mese,"Settembre")==0) {
			days=30;
			break;
		}
		if (strcmp(mese,"Ottobre")==0) {
			days=31;
			break;
		}
		if (strcmp(mese,"Novembre")==0) {
			days=30;
			break;
		}
		if (strcmp(mese,"Dicembre")==0) {
			days=31;
			break;
		}
		printf("[6-] Mese non valido\n");
	}while (1);

	if (strcmp(mese,"Febbraio")==0) {
		anno=set_anno(days, 2, 6);
	}
	else {
		anno=set_anno(days, 1, 6);
	}

	sprintf(file, "%s_%d.csv", mese, anno);
	if ((stream = fopen(file, "r"))==NULL) {
		printf("[6.] Errore nella visualizzazione del File\n");exit(1);
	}
	else {
		do{
			printf("[6.] Inserisci Gruppo: ");
			index = getchar();
			flush();
			if (index == 'A') {
				strcpy(file2, ".matrix_A_output.csv");
				break;
			}
			if (index == 'D') {
				strcpy(file2, ".matrix_D_output.csv");
				break;
			}
			if (index == 'M') {
				strcpy(file2, ".matrix_M_output.csv");
				break;
			}
			printf("[5-] Gruppo non valido\n");
		}while (1);

		if ((stream = fopen(file2, "r"))==NULL) {
			printf("[6.] Errore nella visualizzazione del File Matrice\n");exit(1);
		}
		else {
			fscanf(stream, "%s", tmp);
			fscanf(stream, "%c", &index);
			fscanf(stream, "%c", &index);
			while (!feof(stream)) { /* ciclo per definire totale caselle e posizione pointer riga corretta */
				fscanf(stream, "%c", &index);
				if (index=='\n') {
					if (count==0) {
						fscanf(stream, "%s", tmp);
						fscanf(stream, "%c", &index);
						fscanf(stream, "%s", tmp);
						fscanf(stream, "%c", &index);
						fscanf(stream, "%c", &index);
						printf("\n");
					}
					if (count==1) {
						break;
					}
					count++;
				}
				printf("%c",index);
			}
			fclose(stream);
			printf("\n");
		}
	}
	printf("\n");
	exit(0);
}

void view_N() {
	pid_t pro;

	if((pro = fork()) == -1) {
		printf("[6.] Errore nella creazione del Processo\n");exit(1);
		}
	if(pro==0) {
		if (viewn()==0) {
			exit(0);
		}
	}

	wait(0);
	return;
}
