/*********************
		Punto 4
/********************/
#include "mylib.h" /* definizione mylib */
#include <string.h> /* stringhe */
#include <stdlib.h> /* exit */
#include <stdio.h> /* I/O */
#include <unistd.h> /* fork */
#include <sys/types.h> /* libreria processi */
#include <sys/stat.h> /* FIFO */

int f1(char file[18]) {
	char turni[1500]; /* stringa di turni */
	char tmp[20];
	char str[40];
	char index;
	int count=0; /* contatore utenti */
	int bf=0; /* contatore buffer */
	int i, ii; /* tmp for */
	int not=0; /* contatore indisponibilità */
	int tot=0; /* contatore disponibilità */
	long pointer; /* posizione ftell */
	FILE *stream; /* file csv */

	if ((stream = fopen(file, "r"))==NULL) {
		printf("[4.] Errore nella visualizzazione del File\n");
		exit(1);
	}
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			count++;
			if (count==1) {
				fscanf(stream, "%c", &index);
				//fscanf(stream, "%c", &index);
				fscanf(stream, "%s", turni);
			}
			if (count==2) {
				pointer=ftell(stream);
			}
		}
	}
	fseek(stream, pointer, SEEK_SET);
	ut utente[count-3];
	for (i=0; i<count-3;i++) {
		not=tot=bf=0;
		fscanf(stream, "%c", &index);
		utente[i].gruppo=index;
		fscanf(stream, "%c", &index); /* salto " " */
		fscanf(stream, "%c", &index); /* salto ";" */
		fscanf(stream, "%s", str); /* nome */
		strcat(str, " ");
		fscanf(stream, "%c", &index);  /* salto " " */
		fscanf(stream, "%s", tmp); /* cognome */
		strcat(str, tmp);
		strcat(utente[i].nome, str);
		strcat(utente[i].nome, " ");
		strcat(utente[i].nome, "\0");
		fscanf(stream, "%c", &index); /* salto " " */
		fscanf(stream, "%c", &index); /* salto ";" */
		while (!feof(stream)) {
			fscanf(stream, "%c", &index);
			if (index==';') {
				utente[i].buffer[bf++]=index;
				tot++;
			}
			if (index=='X') {
				utente[i].buffer[bf++]=index;
				not++;
			}
			if (index=='\n') {
				break;
			}
		}
		if (not>=tot){
			utente[i].tot_disponibilita=0;
		}
		else {
			utente[i].tot_disponibilita=(tot-not);
		}
	}
	fclose(stream);

	for (i=0; i<count-3;i++) { /* bug dello scanf. copia anche valori errati */
		//fprintf(stream,"%s\n", utente[i].nome); /* mostrabile in stampata */
		if (!isalpha(utente[i].nome[0])) { /* data link escape o del */
			for (ii=0;ii<strlen(utente[i].nome)-1;ii++) {
				utente[i].nome[ii]=utente[i].nome[ii+1];
			}
			utente[i].nome[ii]='\0';
		}
	}
	qsort(utente, count-3, sizeof(*utente), compare); /* ordino per minore */

	if(mknod("utenza",S_IFIFO|0777,0)==-1) {
		printf("[4.] F1 Errore nella comunicazione tra Processi 1\n");unlink("utenza");exit(1);
	}
	if ((stream = fopen("utenza", "w"))==NULL) {
		printf("[4.] F1 Errore nella comunicazione tra Processi 2\n");unlink("utenza");exit(1);
	}
	else {
		//printf("1: %d\n", count);
		//printf("1: %s\n", turni);
		fprintf(stream, "%d", count); /* invia contatore utenti */
		fprintf(stream, "%s", turni); /* invia turni lavorativi */
		fflush(stream);fclose(stream);

		char file[18];
		for (i=0; i<count-3;i++) {
			sprintf(file, "utente%d.(%d)", i, 0);
			if(mknod(file,S_IFIFO|0777,0)==-1) {
				printf("[4.] F1 Errore nella comunicazione tra Processi 3\n");unlink(file);exit(1);
			}
			if ((stream = fopen(file, "w"))==NULL) {
				printf("[4.] F1 Errore nella comunicazione tra Processi 4\n");unlink(file);exit(1);
			}
			else {
				fprintf(stream, "%d", utente[i].tot_disponibilita);
				fprintf(stream, "%s", utente[i].buffer);
				fflush(stream);fclose(stream);
			}
			sprintf(file, "utente%d.(%d)", i, 1);
			if(mknod(file,S_IFIFO|0777,0)==-1) {
				printf("[4.] F1 Errore nella comunicazione tra Processi 5\n");unlink(file);exit(1);
			}
			if ((stream = fopen(file, "w"))==NULL) {
				printf("[4.] F1 Errore nella comunicazione tra Processi 6\n");unlink(file);exit(1);
			}
			else {
				fprintf(stream, "%c", utente[i].gruppo);
				fprintf(stream, "%s", utente[i].nome);
				fflush(stream);fclose(stream);
			}
			//printf("1: %d\n", utente[i].tot_disponibilita);
			//printf("1: %s\n", utente[i].buffer);
			//printf("1: %c\n", utente[i].gruppo);
			//printf("1: %s\n", utente[i].nome);
		}
	}
	exit(0);
}

int f2() {
	char turni[1500]; /* stringa di turni */
	char tmp[20];
	int cA=0; int cD=0; int cM=0; /* contatori matrici */
	int count=0; /* contatore utenti */
	int i, ii, t=0; /* tmp for */
	int x=0; /* contatore turni dentro for */
	long pointer; /* posizione ftell */
	FILE *stream; /* file csv */
	char buffer[200];
	char file[18];

	sleep(2);

	if((stream = fopen("utenza", "r"))==NULL){
		printf("[4.] F2 Errore nella comunicazione tra Processi 1\n");unlink("utenza");exit(1);
	}
	else {
		fscanf(stream, "%d", &count); /* riceve contatore utenti */
		fscanf(stream, "%s", turni); /* invia turni lavorativi */
		unlink("utenza"),fclose(stream);
		gr matrix_A[strlen(turni)];/* struttture gruppi */
		gr matrix_D[strlen(turni)];
		gr matrix_M[strlen(turni)];
		for (i=0; i<strlen(turni); i++) {
			if (turni[i]!=';' && turni[i+1]!=';' && turni[i+2]!=';') { //2 cifre + 1 orario
				matrix_A[t].turno[0]=turni[i];matrix_A[t].turno[1]=turni[i+1];matrix_A[t].turno[2]=turni[i+2];t++;
				matrix_D[t].turno[0]=turni[i];matrix_D[t].turno[1]=turni[i+1];matrix_D[t].turno[2]=turni[i+2];
				matrix_M[t].turno[0]=turni[i];matrix_M[t].turno[1]=turni[i+1];matrix_M[t].turno[2]=turni[i+2];
				i+=2;
			}
			else if (turni[i]!=';' && turni[i+1]!=';') { //2 cifre o 1 cifra+orario
				matrix_A[t].turno[0]=turni[i];matrix_A[t].turno[1]=turni[i+1];t++;
				matrix_D[t].turno[0]=turni[i];matrix_D[t].turno[1]=turni[i+1];
				matrix_M[t].turno[0]=turni[i];matrix_M[t].turno[1]=turni[i+1];
				i+=1;
			}
			else if (turni[i]!=';') { //1 cifra
				matrix_A[t].turno[0]=turni[i];t++;
				matrix_D[t].turno[0]=turni[i];
				matrix_M[t].turno[0]=turni[i];
			}
			matrix_A[i].tot_utenti=0; /* inizializzo tutto a zero */
			matrix_D[i].tot_utenti=0;
			matrix_M[i].tot_utenti=0;
		}
		//printf("2: %d\n", count);
		//printf("2: %s\n", turni);
		ut utente[count-3];

		for (i=0; i<count-3;i++) {
			x=0;
			sprintf(file, "utente%d.(%d)", i, 0);
			if((stream = fopen(file, "r"))==NULL){
				printf("[4.] F2 Errore nella comunicazione tra Processi 2\n");unlink(file);exit(1);
			}
			else {
				fscanf(stream, "%d", &utente[i].tot_disponibilita);
				fscanf(stream, "%s", utente[i].buffer);
				unlink(file),fclose(stream);
			}
			sprintf(file, "utente%d.(%d)", i, 1);
			if((stream = fopen(file, "r"))==NULL){
				printf("[4.] F2 Errore nella comunicazione tra Processi 3\n");unlink(file);exit(1);
			}
			else {
				fscanf(stream, "%c", &utente[i].gruppo);
				fscanf(stream, "%s", tmp);
				strcat(utente[i].nome, tmp);
				//strcat(utente[i].nome, " "); /* aggiunge lo spazio per nome */
				fscanf(stream, "%s", tmp);
				strcat(utente[i].nome, tmp);
				strcat(utente[i].nome, "\0");
				unlink(file),fclose(stream);
			}
			//printf("2: %d\n", utente[i].tot_disponibilita);
			//printf("2: %s\n", utente[i].buffer);
			//printf("2: %c\n", utente[i].gruppo);
			//printf("2: %s\n", utente[i].nome);
			if (utente[i].gruppo=='A') {
				for (ii=0; ii<strlen(utente[i].buffer); ii++) {
					if (utente[i].buffer[ii]==';'){
						if (matrix_A[x].tot_utenti>0) {
							strcat(matrix_A[x].utenti, " - ");
							strcat(matrix_A[x].utenti, utente[i].nome);
						}
						else {
							strcat(matrix_A[x].utenti, utente[i].nome);
						}
						matrix_A[x].tot_utenti++;x++;
					}
					if (utente[i].buffer[ii]=='X'){
						ii++;x++;
					}
				}
				cA++;
			}
			if (utente[i].gruppo=='D') {
				for (ii=0; ii<strlen(utente[i].buffer); ii++) {
					if (utente[i].buffer[ii]==';'){
						if (matrix_D[x].tot_utenti>0) {
							strcat(matrix_D[x].utenti, " - ");
							strcat(matrix_D[x].utenti, utente[i].nome);
						}
						else {
							strcat(matrix_D[x].utenti, utente[i].nome);
						}
						matrix_D[x].tot_utenti++;x++;
					}
					if (utente[i].buffer[ii]=='X'){
						ii++;x++;
					}
				}
				cD++;
			}
			if (utente[i].gruppo=='M') {
				for (ii=0; ii<strlen(utente[i].buffer); ii++) {
					if (utente[i].buffer[ii]==';'){
						if (matrix_M[x].tot_utenti>0) {
							strcat(matrix_M[x].utenti, " - ");
							strcat(matrix_M[x].utenti, utente[i].nome);
						}
						else {
							strcat(matrix_M[x].utenti, utente[i].nome);
						}
						matrix_M[x].tot_utenti++;x++;
					}
					if (utente[i].buffer[ii]=='X'){
						ii++;x++;
					}
				}
				cM++;
			}
		}

		if((stream = fopen("matrice_turni.csv", "w"))==NULL){
			printf("[4.] Errore nella creazione output M\n");unlink("matrice_turni");exit(1);
		}
		else {
			fprintf(stream, "Turno ;");
			for (i=0; i<t; i++) {
				fprintf(stream, "%s;", matrix_A[i].turno);
			}
			//fprintf(stream, "\nUtente Gruppo A ;"); /* mette il primo utente disponibile */
			/*for (i=0; i<t; i++) {
				for (ii=0; ii<strlen(matrix_A[i].utenti); ii++) {
					if (matrix_A[i].utenti[ii]=='-') {
							break;
						}
					if (isalpha(matrix_A[i].utenti[ii]) || matrix_A[i].utenti[ii]==' ') {
						fprintf(stream, "%c", matrix_A[i].utenti[ii]);
					}
				}
				fprintf(stream, ";");
			}*/
			//fprintf(stream, "\nUtente Gruppo D ;"); /* mette il primo utente disponibile */
			/*for (i=0; i<t; i++) {
				for (ii=0; ii<strlen(matrix_D[i].utenti); ii++) {
					if (matrix_D[i].utenti[ii]=='-') {
							break;
						}
					if (isalpha(matrix_D[i].utenti[ii]) || matrix_D[i].utenti[ii]==' ') {
						fprintf(stream, "%c", matrix_D[i].utenti[ii]);
					}
				}
				fprintf(stream, ";");
			}*/
			//fprintf(stream, "\nUtente Gruppo M ;"); /* mette il primo utente disponibile */
			/*for (i=0; i<t; i++) {
				for (ii=0; ii<strlen(matrix_M[i].utenti); ii++) {
					if (matrix_M[i].utenti[ii]=='-') {
							break;
						}
					if (isalpha(matrix_M[i].utenti[ii]) || matrix_M[i].utenti[ii]==' ') {
						fprintf(stream, "%c", matrix_M[i].utenti[ii]);
					}
				}
				fprintf(stream, ";");
			}*/
			//fprintf(stream, "\n");
			fflush(stream);fclose(stream);
		}

		qsort(matrix_A, t, sizeof(*matrix_A), compare); /* ordino per minore */
		qsort(matrix_M, t, sizeof(*matrix_M), compare); /* ordino per minore */
		qsort(matrix_D, t, sizeof(*matrix_D), compare); /* ordino per minore */

		if (cA>0) {
			if((stream = fopen(".matrix_A_output.csv", "w"))==NULL){
				printf("[4.] Errore nella creazione output A\n");unlink(".matrix_A_output.csv");exit(1);
			}
			else {
				fprintf(stream, "Turno ;");
				for (i=0; i<t; i++) {
					fprintf(stream, "%s;", matrix_A[i].turno);
				}
				fprintf(stream, "\nUtenti Disponibili ;");
				for (i=0; i<t; i++) {
					fprintf(stream, "%s ;", matrix_A[i].utenti);
				}
				fprintf(stream, "\nTotale ;");
				for (i=0; i<t; i++) {
					fprintf(stream, "%d;", matrix_A[i].tot_utenti);
				}
				fflush(stream);fclose(stream);
			}
		}

		if (cD>0) {
			if((stream = fopen(".matrix_D_output.csv", "w"))==NULL){
				printf("[4.] Errore nella creazione output D\n");unlink(".matrix_D_output.csv");exit(1);
			}
			else {
				fprintf(stream, "Turno ;");
				for (i=0; i<t; i++) {
					fprintf(stream, "%s;", matrix_D[i].turno);
				}
				fprintf(stream, "\nUtenti Disponibili ;");
				for (i=0; i<t; i++) {
					fprintf(stream, "%s ;", matrix_D[i].utenti);
				}
				fprintf(stream, "\nTotale ;");
				for (i=0; i<t; i++) {
					fprintf(stream, "%d;", matrix_D[i].tot_utenti);
				}
				fflush(stream);fclose(stream);
			}
		}

		if (cM>0) {
			if((stream = fopen(".matrix_M_output.csv", "w"))==NULL){
				printf("[4.] Errore nella creazione output M\n");unlink(".matrix_M_output.csv");exit(1);
			}
			else {
				fprintf(stream, "Turno ;");
				for (i=0; i<t; i++) {
					fprintf(stream, "%s;", matrix_M[i].turno);
				}
				fprintf(stream, "\nUtenti Disponibili ;");
				for (i=0; i<t; i++) {
					fprintf(stream, "%s ;", matrix_M[i].utenti);
				}
				fprintf(stream, "\nTotale ;");
				for (i=0; i<t; i++) {
					fprintf(stream, "%d;", matrix_M[i].tot_utenti);
				}
				fflush(stream);fclose(stream);
			}
		}

	}
	exit(0);
}

void disp_A() {
	char mese[9]; /* input mese */
	char file[18]; /* file estrapolato dai vari input */
	pid_t pro[2]; /* array pid processi */
	int i; /* var temporanea */
	int anno; /* input anno */
	int days; /* set giorni del mese */

	do{
		printf("[4.] Inserisci Mese: ");
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
		printf("[4-] Mese non valido\n");
	}while (1);

	if (strcmp(mese,"Febbraio")==0) {
		anno=set_anno(days, 2, 4);
	}
	else {
		anno=set_anno(days, 1, 4);
	}
	sprintf(file, "%s_%d.csv", mese, anno);

	for(i=0; i<2; i++) {
		if((pro[i] = fork()) == -1) {
			printf("[4.] Errore nella creazione di Processi\n");
		}
		if(pro[i]==0 && i==0) {
			if (f1(file)==0) {
				exit(0);
			}
		}
		if(pro[i]==0 && i==1) {
			if (f2()==0) {
				exit(0);
			}
		}
	}
	wait(0);wait(0);
	printf("[4.] Concluso\n\n");
	return;
}
