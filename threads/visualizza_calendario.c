#include "mylib.h"
#include <stdio.h> /* I/O */
#include <string.h> /* stringhe */

void view_C() {

	char buffer;
	char mese[9]; /* input mese */
	char file[18]; /* file estrapolato dai vari input */
	char index; /* char temporanei */
	int i; /* var temporanea */
	int count=0; /* numero di righe */
	int anno; /* input anno */
	int days; /* set giorni del mese */
	long pointer; /* posizione ftell */
	FILE *stream; /* file csv */

	do{
		printf("[3.] Inserisci Mese: ");
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
		printf("[3-] Mese non valido\n");
	}while (1);

	if (strcmp(mese,"Febbraio")==0) {
		anno=set_anno(days, 2, 3);
	}
	else {
		anno=set_anno(days, 1, 3);
	}

	sprintf(file, "%s_%d.csv", mese, anno);
	if ((stream = fopen(file, "r"))==NULL) {
		printf("[3.] Errore nella visualizzazione del File\n");
	}
	else {
		while (!feof(stream)) { /* ciclo per definire totale caselle e posizione pointer riga corretta */
			fscanf(stream, "%c", &index);
			if (index=='\n') {
				count++;
				if (count==1) {
				pointer=ftell(stream);
				}
			}
		}

	fseek(stream, pointer, SEEK_SET);
		while (!feof(stream)) {
			fscanf(stream, "%c", &buffer);
			printf("%c",buffer);
		}

		/*for (i=0; i<strlen(buffer); i++) {
			if (buffer[i]==';') {
				buffer[i]=';';
			}
		}*/

	fclose(stream);
	}

	return;
}
