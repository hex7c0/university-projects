/*********************
		Punto 3
*********************/
#include "mylib.h"
#include <stdio.h> /* I/O */
#include <string.h> /* stringhe */

void make_C() {
	char mese[9]; /* input mese */
	char giorno[9]; /* input giorno inizio */
	char file[18]; /* file estrapolato dai vari input */
	int festivo[31]; /* input festività */
	int i, tmp; /* var temporanea */
	int anno; /* input anno */
	int days; /* set giorni del mese */
	int day; /* set 1 giorno */
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
		printf("[1-] Mese non valido\n");
	}while (1);

	if (strcmp(mese,"Febbraio")==0) {
		anno=set_anno(days, 2, 1);
	}
	else {
		anno=set_anno(days, 1, 1);
	}

	do{
		printf("[3.] Inserisci 1° Giorno: ");
		scanf ("%s", giorno);
		flush();
		if (strcmp(giorno,"Lunedì")==0) {
			day=1;
			break;
		}
		if (strcmp(giorno,"Martedì")==0) {
			day=2;
			break;
		}
		if (strcmp(giorno,"Mercoledì")==0) {
			day=3;
			break;
		}
		if (strcmp(giorno,"Giovedì")==0) {
			day=4;
			break;
		}
		if (strcmp(giorno,"Venerdì")==0) {
			day=5;
			break;
		}
		if (strcmp(giorno,"Sabato")==0) {
			day=6;
			break;
		}
		if (strcmp(giorno,"Domenica")==0) {
			day=7;
			break;
		}
		printf("[1-] Giorno non valido\n");
	}while (1);

	for (i=1; i<=days; i++){ /* inizializzo tutto array a 0 */
		festivo[i]=0;
	}
	for (i=1; i<=days; i++) {
		printf("[3.] Inserisci Festività (0 uscire): ");
		do {
			tmp = days+1; /* per evitare che cicli l'input vecchio */
			scanf("%d", &tmp);
			flush();
		} while (tmp > days);
		if (tmp == 0) {
			break;
		}
		festivo[tmp] = 1;
	}

	sprintf(file, "%s_%d.csv", mese, anno);
	if ((stream = fopen(file, "w"))==NULL) {
		printf("[3.] Errore nella creazione del File");
	}
	else {
		fprintf(stream, "Gruppo;Utente;"); /* spazio per Gruppo; Nome*/
		tmp=day; /* tengo traccia dell'inizio del mese */
		for (i=1; i<=days; i++) {
			switch (day) {
				case 1:
					if (festivo[i]==1) {
						fprintf(stream, "Lunedì-mattina;Lunedì-pomeriggio;Lunedì-notte;");
					}
					else {
						fprintf(stream, "Lunedì;");
					}
					day++;
					break;
				case 2:
					if (festivo[i]==1) {
						fprintf(stream, "Martedì-mattina;Martedì-pomeriggio;Martedì-notte;");
					}
					else {
						fprintf(stream, "Martedì;");
					}
					day++;
					break;
				case 3:
					if (festivo[i]==1) {
						fprintf(stream, "Mercoledì-mattina;Mercoledì-pomeriggio;Mercoledì-notte;");
					}
					else {
						fprintf(stream, "Mercoledì;");
					}
					day++;
					break;
				case 4:
					if (festivo[i]==1) {
						fprintf(stream, "Giovedì-mattina;Giovedì-pomeriggio;Giovedì-notte;");
					}
					else {
						fprintf(stream, "Giovedì;");
					}
					day++;
					break;
				case 5:
					if (festivo[i]==1) {
						fprintf(stream, "Venerdì-mattina;Venerdì-pomeriggio;Venerdì-notte;");
					}
					else {
						fprintf(stream, "Venerdì;");
					}
					day++;
					break;
				case 6:
					fprintf(stream, "Sabato-mattina;Sabato-pomeriggio;Sabato-notte;");
					day++;
					break;
				case 7:
					fprintf(stream, "Domenica-mattina;Domenica-pomeriggio;Domenica-notte;");
					day=1;
					break;
			}
		}

		fprintf(stream, "\n;;"); /* spazio per Gruppo; Nome*/
		day=tmp;

		for (i=1; i<=days; i++) {
			switch (day) {
				case 6:
					fprintf(stream, "%dM;%dP;%dN;", i,i,i);
					day++;
					break;
				case 7:
					fprintf(stream, "%dM;%dP;%dN;", i,i,i);
					day=1;
					break;
				default:
					if (festivo[i]==1) {
						fprintf(stream, "%dM;%dP;%dN;", i,i,i);
					}
					else {
						fprintf(stream, "%d;", i);
					}
					day++;
					break;
			}
		}
		fprintf(stream, "\n");
		fflush(stream);
		fclose(stream);
	}
	return;
}
