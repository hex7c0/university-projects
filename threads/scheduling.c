/*********************
		Punto 7
/********************/
#include "mylib.h" /* definizione mylib */
#include <string.h> /* stringhe */
#include <stdlib.h> /* exit */
#include <sys/types.h>
#include <stdio.h> /* I/O */
#include <unistd.h> /* fork */
#include <string.h>
#include <pthread.h>
pthread_mutex_t mu[5];

void *pa(void *file) {
	char turni[1500]; /* stringa di turni */
	char orig[1500]; /* stringa di turni originale */
	char tmp[100]; /* stringa totalità */
	char nome[40];
	char index;
	long pointer; /* posizione ftell */
	int i, ii=0, t=0, x=0; /* tmp for */
	int count=0; /* contatore utenti */
	FILE *stream; /* file csv */

	pthread_mutex_lock(&mu[0]);
	if ((stream = fopen(file, "r"))==NULL) {
		printf("[7.] Errore nella visualizzazione del File\n");exit(1);
	}
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			count++;
			if (count==1) {
				fscanf(stream, "%c", &index);
				//fscanf(stream, "%c", &index);
				fscanf(stream, "%s", orig);
			}
			if (count==2) {
				pointer=ftell(stream);
			}
		}
	}

	fseek(stream, pointer, SEEK_SET);
	ut utente[count-3];
	i=0;
	for (i=0; i<count-3;i++) {
		fscanf(stream, "%c", &index);
		if (index!='A') {
			count--;
			if (i==0) {
				i=0;
			}
			else {
				i--;
			}
		}
		else {
			utente[i].gruppo=index;
			fscanf(stream, "%c", &index); /* salto " " */
			fscanf(stream, "%c", &index); /* salto ";" */
			fscanf(stream, "%s", nome); /* nome */
			fscanf(stream, "%c", &index);  /* salto " " */
			fscanf(stream, "%s", tmp); /* cognome */
			strcat(nome, tmp);
			strcat(utente[i].nome, nome);
			strcat(utente[i].nome, "\0");
			utente[i].tot_disponibilita=0;
		}
		while (!feof(stream)) {
			fscanf(stream, "%c", &index);
			if (index=='\n') {
				break;
			}
		}
	}
	fclose(stream);
	pthread_mutex_unlock(&mu[0]);

	for (i=0; i<count-3;i++) { /* bug dello scanf. copia anche valori errati */
		//fprintf(stream,"%s\n", utente[i].nome); /* mostrabile in stampata */
		if (!isalpha(utente[i].nome[0])) { /* data link escape o del */
			for (ii=0;ii<strlen(utente[i].nome)-1;ii++) {
				utente[i].nome[ii]=utente[i].nome[ii+1];
			}
			utente[i].nome[ii]='\0';
		}
	}

	if((stream = fopen(".matrix_A_output.csv", "r"))==NULL){
		printf("[7.] Errore nella apertura File. Esegui prima punto 4\n");unlink(".matrix_A_output.csv");exit(1);
	}
	fscanf(stream, "%s", tmp); /* colonna info */
	fscanf(stream, "%c", &index); /* salto " " */
	fscanf(stream, "%c", &index); /* salto " " */
	fscanf(stream, "%s", turni);

	t=0;
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n' && t==1) {
			break;
		}
		if (index=='\n' && t==0) {
			fscanf(stream, "%s", tmp);
			fscanf(stream, "%s", tmp);
			fscanf(stream, "%c", &index);
			pointer=ftell(stream);t++;
		}
	}
	fscanf(stream, "%s", tmp); /* colonna info */
	fscanf(stream, "%s", tmp); /* colonna info */
	fscanf(stream, "%s", tmp);

	gr matrix_A[strlen(turni)];/* strutture gruppi */
	t=0;
	for (i=0; i<strlen(turni); i++) {
		if (turni[i]!=';' && turni[i+1]!=';' && turni[i+2]!=';') { //2 cifre + 1 orario
			matrix_A[t].turno[0]=turni[i];matrix_A[t].turno[1]=turni[i+1];matrix_A[t].turno[2]=turni[i+2];t++;
			i+=2;
		}
		else if (turni[i]!=';' && turni[i+1]!=';') { //2 cifre o 1 cifra+orario
			matrix_A[t].turno[0]=turni[i];matrix_A[t].turno[1]=turni[i+1];t++;
			i+=1;
		}
		else if (turni[i]!=';') { //1 cifra
			matrix_A[t].turno[0]=turni[i];t++;
		}
		matrix_A[i].coperto=0;
	}
	ii=0;
	for (i=0; i<strlen(tmp); i++) {
		if (isdigit(tmp[i])) {
			matrix_A[ii].tot_utenti=tmp[i]-'0';
			ii++;
		}
	}

	gr matrix[strlen(turni)];/* strutture gruppi originale */
	x=0;
	for (i=0; i<strlen(orig); i++) {
		if (orig[i]!=';' && orig[i+1]!=';' && orig[i+2]!=';') { //2 cifre + 1 orario
			matrix[x].turno[0]=orig[i];matrix[x].turno[1]=orig[i+1];matrix[x].turno[2]=orig[i+2];x++;
			i+=2;
		}
		else if (orig[i]!=';' && orig[i+1]!=';') { //2 cifre o 1 cifra+orario
			matrix[x].turno[0]=orig[i];matrix[x].turno[1]=orig[i+1];x++;
			i+=1;
		}
		else if (orig[i]!=';') { //1 cifra
			matrix[x].turno[0]=orig[i];x++;
		}
	}

	ut utenti[t-1]; /* array utenti, massimale, numero turni totali */
	fseek(stream, pointer, SEEK_SET);
	fscanf(stream, "%c", &index);//fscanf(stream, "%c", &index);
	ii=0; /* contatore ascendente per trovare occorrenza utente */
	x=0; /* contatore posizione */
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			x--; /* tolgo parte finale */
			break;
		}
		if (index==';') {
			x++;ii=0;
		}
		else if (index=='-') {
			//printf("%s\n", nome);
		}
		else if(isalpha(index) && ii==0) {
			fseek(stream, -1, SEEK_CUR); /* posizione a -1 per prendere carattere iniziale */
			fscanf(stream, "%s", tmp);
			strcat(tmp, "\0");
			for (i=0;i<count;i++) { /* ciclo controlla utenti */
				if (strncmp(tmp,utente[i].nome,strlen(tmp))==0) { /* confronta le stringhe per corrispondenza */
					if (utente[i].tot_disponibilita<2) {
						utente[i].tot_disponibilita++;
						if(matrix_A[x].coperto==0) {
							strcat(matrix_A[x].utenti,utente[i].nome);
							matrix_A[x].coperto++;
							ii=1; /* cicla altro utente del turno */
							//printf("%s >turno %d :%s ! ", utente[i].nome, x, matrix_A[x].turno);
						}
						//printf("OK\n");
						break;
					}
				}
			}
		}
	}
	fclose(stream);

	for (i=0; i<t; i++) {
		if (matrix_A[i].tot_utenti==0) {
			printf("[7.] Warning A: nessun utente disponibile per il turno %s\n", matrix_A[i].turno);
		}
		if (matrix_A[i].coperto==0) {
			printf("[7.] Warning A: turno %s non assegnato\n", matrix_A[i].turno);
		}
	}

	//printf("1\n");
	if((stream = fopen("matrice_turni.csv", "a+"))==NULL){
		printf("[7.] A: Errore nella apertura File. Esegui prima punto 4\n");unlink("matrice_turni.csv");exit(1);
	}
	else {
		fprintf(stream, "\nUtente Gruppo A ;"); /* mette il primo utente disponibile */
		for (i=0;i<t;i++){
			for (ii=0;ii<t;ii++){
				if (strcmp(matrix[i].turno,matrix_A[ii].turno)==0) { /* confronta le stringhe per corrispondenza */
					//printf("%s \t %s\n", matrix[i].turno,matrix_A[ii].utenti);
					fprintf(stream, "%s;", matrix_A[ii].utenti);
					break;
				}
			}
		}
		fflush(stream);fclose(stream);
	}
	pthread_mutex_unlock(&mu[1]);
	pthread_exit(NULL);
	exit(0); /* inutile, toglie warning eclipse */
}

void *pd(void *file) {
	char turni[1500]; /* stringa di turni */
	char orig[1500]; /* stringa di turni originale */
	char tmp[100]; /* stringa totalità */
	char nome[40];
	char index;
	long pointer; /* posizione ftell */
	int i, ii=0, t=0, x=0; /* tmp for */
	int count=0; /* contatore utenti */
	FILE *stream; /* file csv */

	pthread_mutex_lock(&mu[0]);
	if ((stream = fopen(file, "r"))==NULL) {
		printf("[7.] Errore nella visualizzazione del File\n");exit(1);
	}
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			count++;
			if (count==1) {
				fscanf(stream, "%c", &index);
				//fscanf(stream, "%c", &index);
				fscanf(stream, "%s", orig);
			}
			if (count==3) {
				pointer=ftell(stream);
			}
		}
	}

	fseek(stream, pointer, SEEK_SET);
	ut utente[count-3];
	for (i=0; i<count-3;i++) {
		fscanf(stream, "%c", &index);
		if (index!='D' && index!='M') {
			count--;
			if (i==0) {
				i=0;
			}
			else {
				i--;
			}
		}
		else if (index=='D' || index=='M') {
			utente[i].gruppo=index;
			fscanf(stream, "%c", &index); /* salto " " */
			fscanf(stream, "%c", &index); /* salto ";" */
			fscanf(stream, "%s", nome); /* nome */
			fscanf(stream, "%c", &index);  /* salto " " */
			fscanf(stream, "%s", tmp); /* cognome */
			strcat(nome, tmp);
			strcat(utente[i].nome, nome);
			strcat(utente[i].nome, "\0");
			utente[i].tot_disponibilita=0;
		}
		while (!feof(stream)) {
			fscanf(stream, "%c", &index);
			if (index=='\n') {
				break;
			}
		}
	}
	fclose(stream);
	pthread_mutex_unlock(&mu[0]);

	for (i=1; i<count-3;i++) { /* bug dello scanf. copia anche valori errati */
		//fprintf(stream,"%s\n", utente[i].nome); /* mostrabile in stampata */
		if (!isalpha(utente[i].nome[0])) { /* data link escape o del */
			for (ii=0;ii<strlen(utente[i].nome)-1;ii++) {
				utente[i].nome[ii]=utente[i].nome[ii+1];
			}
			utente[i].nome[ii]='\0';
		}
	}

	pthread_mutex_lock(&mu[3]);
	if((stream = fopen(".matrix_D_output.csv", "r"))==NULL){
		printf("[7.] Errore nella apertura File. Esegui prima punto 4\n");unlink(".matrix_D_output.csv");exit(1);
	}
	fscanf(stream, "%s", tmp); /* colonna info */
	fscanf(stream, "%c", &index); /* salto " " */
	fscanf(stream, "%c", &index); /* salto " " */
	fscanf(stream, "%s", turni);
	t=0;
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n' && t==1) {
			break;
		}
		if (index=='\n' && t==0) {
			fscanf(stream, "%s", tmp);
			fscanf(stream, "%s", tmp);
			fscanf(stream, "%c", &index);
			pointer=ftell(stream);t++;
		}
	}

	fscanf(stream, "%s", tmp); /* colonna info */
	fscanf(stream, "%s", tmp); /* colonna info */
	fscanf(stream, "%s", tmp);

	gr matrix_D[strlen(turni)];/* strutture gruppi */
	t=0;
	for (i=0; i<strlen(turni); i++) {
		if (turni[i]!=';' && turni[i+1]!=';' && turni[i+2]!=';') { //2 cifre + 1 orario
			matrix_D[t].turno[0]=turni[i];matrix_D[t].turno[1]=turni[i+1];matrix_D[t].turno[2]=turni[i+2];t++;
			i+=2;
		}
		else if (turni[i]!=';' && turni[i+1]!=';') { //2 cifre o 1 cifra+orario
			matrix_D[t].turno[0]=turni[i];matrix_D[t].turno[1]=turni[i+1];t++;
			i+=1;
		}
		else if (turni[i]!=';') { //1 cifra
			matrix_D[t].turno[0]=turni[i];t++;
		}
		matrix_D[i].coperto=0;
	}
	ii=0;
	for (i=0; i<strlen(tmp); i++) {
		if (isdigit(tmp[i])) {
			matrix_D[ii].tot_utenti=tmp[i]-'0';
			ii++;
		}
	}

	gr matrix[strlen(turni)];/* strutture gruppi originale */
	x=0;
	for (i=0; i<strlen(orig); i++) {
		if (orig[i]!=';' && orig[i+1]!=';' && orig[i+2]!=';') { //2 cifre + 1 orario
			matrix[x].turno[0]=orig[i];matrix[x].turno[1]=orig[i+1];matrix[x].turno[2]=orig[i+2];x++;
			i+=2;
		}
		else if (orig[i]!=';' && orig[i+1]!=';') { //2 cifre o 1 cifra+orario
			matrix[x].turno[0]=orig[i];matrix[x].turno[1]=orig[i+1];x++;
			i+=1;
		}
		else if (orig[i]!=';') { //1 cifra
			matrix[x].turno[0]=orig[i];x++;
		}
	}

	ut utenti[t-1]; /* array utenti, massimale, numero turni totali */
	fseek(stream, pointer, SEEK_SET);
	fscanf(stream, "%c", &index);//fscanf(stream, "%c", &index);
	ii=0; /* contatore ascendente per trovare occorrenza utente */
	x=0; /* contatore posizione */
	int v=0;
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			x--; /* tolgo parte finale */
			break;
		}
		if (index==';') {
			x++;ii=0;
		}
		else if (index=='-') {
			//printf("%s\n", nome);
		}
		else if(isalpha(index) && ii==0) {
			fseek(stream, -1, SEEK_CUR); /* posizione a -1 per prendere carattere iniziale */
			fscanf(stream, "%s", tmp);
			strcat(tmp, "\0");
			for (i=0;i<count;i++) { /* ciclo controlla utenti */
				if (strncmp(tmp,utente[i].nome,strlen(tmp))==0) { /* confronta le stringhe per corrispondenza */
					if (utente[i].tot_disponibilita<2) {
						utente[i].tot_disponibilita++;
						if(matrix_D[x].coperto==0) {
							strcat(matrix_D[x].utenti,utente[i].nome);
							matrix_D[x].coperto++;
							ii=1; /* cicla altro utente del turno */
							//printf("%s >turno %d :%s ! ", utente[i].nome, x, matrix_D[x].turno);
						}
						//printf("OK\n");
						v=x;
						break;
					}
				}
			}
		}
	}
	fclose(stream);
	pthread_mutex_unlock(&mu[3]);

	pthread_mutex_lock(&mu[4]);
	if((stream = fopen(".matrix_M_output.csv", "r"))==NULL){
		printf("[7.] Errore nella apertura File. Esegui prima punto 4\n");unlink(".matrix_M_output.csv");exit(1);
	}
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			fscanf(stream,"%s", tmp); /* utenti */
			fscanf(stream,"%c", &index);
			fscanf(stream,"%s", tmp); /* disponibili */
			fscanf(stream,"%c", &index);
			break;
		}
	}

	x=v;
	ii=0; /* contatore ascendente per trovare occorrenza utente */
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			x--; /* tolgo parte finale */
			break;
		}
		if (index==';') {
			x++;ii=0;
		}
		else if (index=='-') {
			//printf("%s\n", nome);
		}
		else if(isalpha(index) && ii==0) {
			fseek(stream, -1, SEEK_CUR); /* posizione a -1 per prendere carattere iniziale */
			fscanf(stream, "%s", tmp);
			strcat(tmp, "\0");
			//printf("%s\n", tmp);
			for (i=0;i<count;i++) { /* ciclo controlla utenti */
				if (strncmp(tmp,utente[i].nome,strlen(tmp))==0) { /* confronta le stringhe per corrispondenza */
					if (utente[i].tot_disponibilita<2) {
						utente[i].tot_disponibilita++;
						if(matrix_D[x].coperto==0) {
							strcat(matrix_D[x].utenti,utente[i].nome);
							matrix_D[x].coperto++;
							ii=1; /* cicla altro utente del turno */
							//printf("%s >turno %d :%s ! ", utente[i].nome, x, matrix_D[x].turno);
						}
						//printf("OK\n");
						break;
					}
				}
			}
		}
	}
	fclose(stream);
	pthread_mutex_unlock(&mu[4]);

	for (i=0; i<t; i++) {
		if (matrix_D[i].tot_utenti==0) {
			printf("[7.] Warning D: nessun utente disponibile per il turno %s\n", matrix_D[i].turno);
		}
		if (matrix_D[i].coperto==0) {
			printf("[7.] Warning D: turno %s non assegnato\n", matrix_D[i].turno);
		}
	}

	//printf("2\n");
	pthread_mutex_lock(&mu[1]);
	if((stream = fopen("matrice_turni.csv", "a+"))==NULL){
		printf("[7.] B Errore nella apertura File. Esegui prima punto 4\n");unlink("matrice_turni.csv");exit(1);
	}
	else {
		fprintf(stream, "\nUtente Gruppo D ;"); /* mette il primo utente disponibile */
		for (i=0;i<t;i++){
			for (ii=0;ii<t;ii++){
				if (strcmp(matrix[i].turno,matrix_D[ii].turno)==0) { /* confronta le stringhe per corrispondenza */
					//printf("%s \t %s\n", matrix[i].turno,matrix_D[ii].utenti);
					fprintf(stream, "%s;", matrix_D[ii].utenti);
					break;
				}
			}
		}
		fflush(stream);fclose(stream);
	}
	pthread_mutex_unlock(&mu[1]);pthread_mutex_unlock(&mu[2]);
	pthread_exit(NULL);
	exit(0); /* inutile, toglie warning eclipse */
}

void *pm(void *file) {
	char turni[1500]; /* stringa di turni */
	char orig[1500]; /* stringa di turni originale */
	char tmp[100]; /* stringa totalità */
	char nome[40];
	char index;
	long pointer; /* posizione ftell */
	int i, ii=0, t=0, x=0; /* tmp for */
	int count=0; /* contatore utenti */
	FILE *stream; /* file csv */

	pthread_mutex_lock(&mu[0]);
	if ((stream = fopen(file, "r"))==NULL) {
		printf("[7.] Errore nella visualizzazione del File\n");exit(1);
	}
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			count++;
			if (count==1) {
				fscanf(stream, "%c", &index);
				//fscanf(stream, "%c", &index);
				fscanf(stream, "%s", orig);
			}
			if (count==3) {
				pointer=ftell(stream);
			}
		}
	}

	fseek(stream, pointer, SEEK_SET);
	ut utente[count-3];
	i=0;
	for (i=0; i<count-3;i++) {
		fscanf(stream, "%c", &index);
		if (index!='M' && index!='D') {
			count--;
			if (i==0) {
				i=0;
			}
			else {
				i--;
			}
		}
		else {
			utente[i].gruppo=index;
			fscanf(stream, "%c", &index); /* salto " " */
			fscanf(stream, "%c", &index); /* salto ";" */
			fscanf(stream, "%s", nome); /* nome */
			fscanf(stream, "%c", &index);  /* salto " " */
			fscanf(stream, "%s", tmp); /* cognome */
			strcat(nome, tmp);
			strcat(utente[i].nome, nome);
			strcat(utente[i].nome, "\0");
			utente[i].tot_disponibilita=0;
		}
		while (!feof(stream)) {
			fscanf(stream, "%c", &index);
			if (index=='\n') {
				break;
			}
		}
	}
	fclose(stream);
	pthread_mutex_unlock(&mu[0]);

	for (i=1; i<count-3;i++) { /* bug dello scanf. copia anche valori errati */
		//fprintf(stream,"%s\n", utente[i].nome); /* mostrabile in stampata */
		if (!isalpha(utente[i].nome[0])) { /* data link escape o del */
			for (ii=0;ii<strlen(utente[i].nome)-1;ii++) {
				utente[i].nome[ii]=utente[i].nome[ii+1];
			}
			utente[i].nome[ii]='\0';
		}
	}

	pthread_mutex_lock(&mu[4]);
	if((stream = fopen(".matrix_M_output.csv", "r"))==NULL){
		printf("[7.] Errore nella apertura File. Esegui prima punto 4\n");unlink(".matrix_M_output.csv");exit(1);
	}
	fscanf(stream, "%s", tmp); /* colonna info */
	fscanf(stream, "%c", &index); /* salto " " */
	fscanf(stream, "%c", &index); /* salto " " */
	fscanf(stream, "%s", turni);

	t=0;
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n' && t==1) {
			break;
		}
		if (index=='\n' && t==0) {
			fscanf(stream, "%s", tmp);
			fscanf(stream, "%s", tmp);
			fscanf(stream, "%c", &index);
			pointer=ftell(stream);t++;
		}
	}

	fscanf(stream, "%s", tmp); /* colonna info */
	fscanf(stream, "%s", tmp); /* colonna info */
	fscanf(stream, "%s", tmp);

	gr matrix_M[strlen(turni)];/* strutture gruppi */
	t=0;
	for (i=0; i<strlen(turni); i++) {
		if (turni[i]!=';' && turni[i+1]!=';' && turni[i+2]!=';') { //2 cifre + 1 orario
			matrix_M[t].turno[0]=turni[i];matrix_M[t].turno[1]=turni[i+1];matrix_M[t].turno[2]=turni[i+2];t++;
			i+=2;
		}
		else if (turni[i]!=';' && turni[i+1]!=';') { //2 cifre o 1 cifra+orario
			matrix_M[t].turno[0]=turni[i];matrix_M[t].turno[1]=turni[i+1];t++;
			i+=1;
		}
		else if (turni[i]!=';') { //1 cifra
			matrix_M[t].turno[0]=turni[i];t++;
		}
		matrix_M[i].coperto=0;
	}
	ii=0;
	for (i=0; i<strlen(tmp); i++) {
		if (isdigit(tmp[i])) {
			matrix_M[ii].tot_utenti=tmp[i]-'0';
			ii++;
		}
	}

	gr matrix[strlen(turni)];/* strutture gruppi originale */
	x=0;
	for (i=0; i<strlen(orig); i++) {
		if (orig[i]!=';' && orig[i+1]!=';' && orig[i+2]!=';') { //2 cifre + 1 orario
			matrix[x].turno[0]=orig[i];matrix[x].turno[1]=orig[i+1];matrix[x].turno[2]=orig[i+2];x++;
			i+=2;
		}
		else if (orig[i]!=';' && orig[i+1]!=';') { //2 cifre o 1 cifra+orario
			matrix[x].turno[0]=orig[i];matrix[x].turno[1]=orig[i+1];x++;
			i+=1;
		}
		else if (orig[i]!=';') { //1 cifra
			matrix[x].turno[0]=orig[i];x++;
		}
	}

	ut utenti[t-1]; /* array utenti, massimale, numero turni totali */
	fseek(stream, pointer, SEEK_SET);
	fscanf(stream, "%c", &index);//fscanf(stream, "%c", &index);
	ii=0; /* contatore ascendente per trovare occorrenza utente */
	x=0; /* contatore posizione */
	int v=0;
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			x--; /* tolgo parte finale */
			break;
		}
		if (index==';') {
			x++;ii=0;
		}
		else if (index=='-') {
			//printf("%s\n", nome);
		}
		else if(isalpha(index) && ii==0) {
			fseek(stream, -1, SEEK_CUR); /* posizione a -1 per prendere carattere iniziale */
			fscanf(stream, "%s", tmp);
			strcat(tmp, "\0");
			for (i=0;i<count;i++) { /* ciclo controlla utenti */
				if (strncmp(tmp,utente[i].nome,strlen(tmp))==0) { /* confronta le stringhe per corrispondenza */
					if (utente[i].tot_disponibilita<2) {
						utente[i].tot_disponibilita++;
						if(matrix_M[x].coperto==0) {
							strcat(matrix_M[x].utenti,utente[i].nome);
							matrix_M[x].coperto++;
							ii=1; /* cicla altro utente del turno */
							//printf("%s >turno %d :%s ! ", utente[i].nome, x, matrix_M[x].turno);
						}
						v=x;
						//printf("OK\n");
						break;
					}
				}
			}
		}
	}
	fclose(stream);
	pthread_mutex_unlock(&mu[4]);

	pthread_mutex_lock(&mu[3]);
	if((stream = fopen(".matrix_D_output.csv", "r"))==NULL){
		printf("[7.] Errore nella apertura File. Esegui prima punto 4\n");unlink(".matrix_D_output.csv");exit(1);
	}
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			fscanf(stream,"%s", tmp); /* utenti */
			fscanf(stream,"%c", &index);
			fscanf(stream,"%s", tmp); /* disponibili */
			fscanf(stream,"%c", &index);
			break;
		}
	}

	x=v;
	ii=0; /* contatore ascendente per trovare occorrenza utente */
	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			x--; /* tolgo parte finale */
			break;
		}
		if (index==';') {
			x++;ii=0;
		}
		else if (index=='-') {
			//printf("%s\n", nome);
		}
		else if(isalpha(index) && ii==0) {
			fseek(stream, -1, SEEK_CUR); /* posizione a -1 per prendere carattere iniziale */
			fscanf(stream, "%s", tmp);
			strcat(tmp, "\0");
			//printf("%s\n", tmp);
			for (i=0;i<count;i++) { /* ciclo controlla utenti */
				if (strncmp(tmp,utente[i].nome,strlen(tmp))==0) { /* confronta le stringhe per corrispondenza */
					if (utente[i].tot_disponibilita<2) {
						utente[i].tot_disponibilita++;
						if(matrix_M[x].coperto==0) {
							strcat(matrix_M[x].utenti,utente[i].nome);
							matrix_M[x].coperto++;
							ii=1; /* cicla altro utente del turno */
							//printf("%s >turno %d :%s ! ", utente[i].nome, x, matrix_M[x].turno);
						}
						//printf("OK\n");
						break;
					}
				}
			}
		}
	}
	fclose(stream);
	pthread_mutex_unlock(&mu[3]);

	for (i=0; i<t; i++) {
		if (matrix_M[i].tot_utenti==0) {
			printf("[7.] Warning M: nessun utente disponibile per il turno %s\n", matrix_M[i].turno);
		}
		if (matrix_M[i].coperto==0) {
			printf("[7.] Warning M: turno %s non assegnato\n", matrix_M[i].turno);
		}
	}

	//printf("3\n");
	pthread_mutex_lock(&mu[2]);
	if((stream = fopen("matrice_turni.csv", "a+"))==NULL){
		printf("[7.] B Errore nella apertura File. Esegui prima punto 4\n");unlink("matrice_turni.csv");exit(1);
	}
	else {
		fprintf(stream, "\nUtente Gruppo M ;"); /* mette il primo utente disponibile */
		for (i=0;i<t;i++){
			for (ii=0;ii<t;ii++){
				if (strcmp(matrix[i].turno,matrix_M[ii].turno)==0) { /* confronta le stringhe per corrispondenza */
					//printf("%s \t %s\n", matrix[i].turno,matrix_M[ii].utenti);
					fprintf(stream, "%s;", matrix_M[ii].utenti);
					break;
				}
			}
		}
		fflush(stream);fclose(stream);
	}
	pthread_mutex_unlock(&mu[2]);
	pthread_exit(NULL);
	exit(0); /* inutile, toglie warning eclipse */
}

void sched_T() {
	pthread_t threads[3];
	pthread_attr_t attr;
	FILE *stream; /* file csv */
	char mese[9]; /* input mese */
	char file[20]; /* file estrapolato dai vari input */
	int rc;
	int i; /* var temporanea */
	int anno; /* input anno */
	int days; /* set giorni del mese */

	do{
		printf("[7.] Inserisci Mese: ");
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
		printf("[7-] Mese non valido\n");
	}while (1);

	if (strcmp(mese,"Febbraio")==0) {
		anno=set_anno(days, 2, 7);
	}
	else {
		anno=set_anno(days, 1, 7);
	}
	sprintf(file, "%s_%d.csv", mese, anno);

	if((stream = fopen("matrice_turni.csv", "r"))==NULL){
		printf("[7.] Errore nella apertura File. Esegui prima punto 4\n");unlink("matrice_turni.csv");return;
	}
	fclose(stream);

	pthread_attr_init(&attr);
	for (i=0;i<5;i++) {
		pthread_mutex_init(&mu[i], NULL);
	}

	pthread_mutex_lock(&mu[1]);pthread_mutex_lock(&mu[2]); /* blocco per sbloccarli in ordine */
	for(i=0; i<3; i++) {
		if (i==0) {
			rc= pthread_create(&threads[i], &attr, pa, (void *) file);
		}
		if (i==1) {
			rc= pthread_create(&threads[i], &attr, pd, (void *) file);
		}
		if (i==2) {
			rc= pthread_create(&threads[i], &attr, pm, (void *) file);
		}
		if (rc) {
			printf("[8.] Errore nella creazione Thread\n");return;
		}
	}
	pthread_join(threads[0], NULL);
	for (i=1;i<3;i++) {
		pthread_join(threads[i], NULL);
		pthread_mutex_destroy(&mu[i]);
	}
	pthread_mutex_destroy(&mu[0]);pthread_mutex_destroy(&mu[3]);pthread_mutex_destroy(&mu[4]);
	printf("[7.] Concluso\n\n");
	return;
}
