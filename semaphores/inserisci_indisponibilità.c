/*********************
		Punto 2
/********************/
#include "mylib.h"
#include <stdio.h> /* I/O */
#include <stdlib.h>
#include <string.h> /* stringhe */

void festivo(int *list, int count) {
	char index, tmp; /* char temporanei */

	printf("giorno festivo (M,P,N)\n");
	do{
		printf("[2.] Inserisci Fascia: ");
		tmp = getchar();
		flush();
		if (tmp == 'M') {
			list[count]=1;
			return;
		}
		if (tmp == 'P') {
			list[count+1]=1;
			return;
		}
		if (tmp == 'N') {
			list[count+2]=1;
			return;
		}
		printf("[2-] Fascia non valida\n");
	}while (1);
}

int repeat_unita(FILE *ptr, int target) {
	char index;
	char str[2];
	int count=0;

	while (!feof(ptr)) {
		fscanf(ptr, "%c", &index);
		if (isdigit(index)) {
			count++;
			str[0]=index;
			str[1]='\0';
			if (target == atoi(str)) {
				while (!feof(ptr)) { /* cicla per portare il pointer su prox casella */
					fscanf(ptr, "%c", &index);
					if (index == ';') {
						break;
					}
				}
				break;
			}
		}
	}
	return (count-1);
}

int repeat_decine(FILE *ptr, int target) {
	char index, tmp;
	char str[3];
	int count=0;

	while (!feof(ptr)) {
		fscanf(ptr, "%c", &index);
		if (isdigit(index)) {
			count++;
			tmp = index; /* decine passate al temporaneo */
			fscanf(ptr, "%c", &index); /* cicla carattere successivo */
			if (isdigit(index)) {
				str[0]=tmp; /* costruisce il numero da convertire */
				str[1]=index;
				str[2]='\0';
				if (target == atoi(str)) {
					while (!feof(ptr)) { /* cicla per portare il pointer su prox casella */
						fscanf(ptr, "%c", &index);
						if (index == ';') {
							break;
						}
					}
					break;
				}
			}
		}
	}
	return (count-1);
}

void insert_I() {
	char nome[20]; /* input nome */
	char cognome[40]; /* input cognome */
	char mese[9]; /* input mese */
	char str[3]; /* stringa conversione */
	char file[18]; /* file estrapolato dai vari input */
	char gruppo; /* input gruppo */
	char index, tmp; /* char temporanei */
	int anno; /* input anno */
	int days; /* set giorni del mese */
	int target; /* giorno di input */
	int size; /* dimensione array stampa */
	int i; /* for for */
	int count=0; /* counter + temporaneo */
	long pointer; /* posizione ftell */
	FILE *stream; /* file csv */

		printf("[2.] Inserisci Nome: ");
		scanf ("%s", nome);
		flush();
		printf("[2.] Inserisci Cognome: ");
		scanf ("%s", cognome);
		flush();

	do{
		printf("[2.] Inserisci Gruppo: ");
		gruppo = getchar();
		flush();
		if (gruppo == 'A') {
			break;
		}
		if (gruppo == 'D') {
			break;
		}
		if (gruppo == 'M') {
			break;
		}
		printf("[2-] Gruppo non valido\n");
	}while (1);

	do{
		printf("[2.] Inserisci Mese: ");
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
		printf("[2-] Mese non valido\n");
	}while (1);

	if (strcmp(mese,"Febbraio")==0) {
		anno=set_anno(days, 2, 2);
	}
	else {
		anno=set_anno(days, 1, 2);
	}

	sprintf(file, "%s_%d.csv", mese, anno);
	strcat(nome, " ");
	strcat(nome, cognome);
	if ((stream = fopen(file, "r"))==NULL) {
		printf("[2.] Errore nella visualizzazione del File\n");
		exit(1);
	}

	while (!feof(stream)) { /* ciclo per definire totale caselle e posizione pointer riga corretta */
		fscanf(stream, "%c", &index);
		if (index==';')
			count++;
		if (index=='\n')
			break;
	}
	size=count-2;
	int list[size]; /* tolto gruppo + nome */
	for (i=0; i<=size; i++) { /* inizializzo array stampa risultati */
		list[i]=0;
	}
	fscanf(stream, "%c", &index); /* casella gruppo */
	fscanf(stream, "%c", &index); /* casella nome */
	pointer=ftell(stream);

	for (i=1; i<=days; i++) {
			printf("[2.] Inserisci Indisponibilità (0 uscire): ");
			do {
				target = days+1; /* per evitare che cicli l'input vecchio */
				scanf("%d", &target);
				flush();
			} while (target > days);
			if (target == 0) {
				break;
			}
			if (target >= 10) {
				count= repeat_decine(stream, target); /* cerca posizione */
			}
			else {
				count= repeat_unita(stream, target); /* cerca posizione */
			}

			fscanf(stream, "%c", &index); /* cerca successivi, per vedere se festivo */
			if (isdigit(index)) {
				if (target < 10) {
					str[0]=index;
					str[1]='\0';
					if (target == atoi(str)) {
						festivo(list, count);
					}
					else {
						list[count]=1;
					}
				}
				else {
					tmp = index; /* decine passate al temporaneo */
					fscanf(stream, "%c", &index); /* cicla carattere successivo */
					if (isdigit(index)) {
						str[0]=tmp; /* costruisce il numero da convertire */
						str[1]=index;
						str[2]='\0';
						if (target == atoi(str)) {
							festivo(list, count);
						}
						else {
							list[count]=1;
						}
					}
					else {
						list[count]=1;
					}
				}
			}
			else {
				list[count]=1;
			}
			fseek(stream, pointer, SEEK_SET);
		}

	fclose(stream); /* parte stampa finale */

	if ((stream = fopen(file, "a"))==NULL) { /* apro in coda, cosi aggiungo direttamente */
		printf("[2.] Errore nella visualizzazione del File\n");
	}
	else {
		fprintf(stream, "%c ;", gruppo);

		/*for (i=0; i<count-3;i++) { // bug dello scanf. copia anche valori errati
			//fprintf(stream,"%s\n", utente[i].nome); // mostrabile in stampata
			if (!isalpha(nome[0])) { // data link escape o del
				nome[0]='y';
			}
		}*/

		fprintf(stream, "%s ;", nome);

		for (i=0; i<size; i++) {
			if (list[i] == 1) {
				fprintf(stream, "X;");
			}
			else {
				fprintf(stream, ";");
			}
		}

		fprintf(stream, "\n");
		fflush(stream);
		fclose(stream);
	}
	return;
}
