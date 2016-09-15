/*********************
		Punto 8
/********************/
#include "mylib.h" /* definizione mylib */
#include <string.h> /* stringhe */
#include <stdlib.h> /* exit */
#include <stdio.h> /* I/O */
#include <unistd.h>
#include <pthread.h>

struct arg {
	char file[25];
	char file2[25];
	msg *m;
};

void *pr(void *data) {
	char turni[2000]; /* stringa di turni tmp */
	char index;
	int i=0; /* tmp for */
	int count=0; /* contatore utenti */
	FILE *stream; /* file csv */
	FILE *stream2; /* file csv */

	struct arg *a;
	a = (struct arg *) data;

	if((stream = fopen(a->file2, "r"))==NULL){
		printf("[8.] Errore nella apertura File Src\n");exit(1);
	}
	else {
		while (!feof(stream)) {
			fscanf(stream, "%c", &index);
			if (index==';' && i==1) {
				break;
			}
			if (index==';') {
				i++;
			}
		}
		if((stream2 = fopen(a->file, "w"))==NULL){
			printf("[8.] Errore nella apertura File Dest\n");exit(1);
		}
		else {
			fscanf(stream, "%s", turni);
			fprintf(stream2,"%s", turni);
			fscanf(stream, "%c", &index);
			fprintf(stream2,"%c", index);
			fscanf(stream, "%c", &index);
			fscanf(stream, "%c", &index);
			fscanf(stream, "%s", turni);
			fprintf(stream2,"%s", turni);
		fflush(stream2);fclose(stream2);
		}
	fclose(stream);
	}

	if((stream = fopen("matrice_turni.csv", "r"))==NULL){
		printf("[8.] Errore nella apertura File\n");exit(1);
	}

	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			i=0;break;
		}
	}

	/* PWA read */
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%c", &index);
	fscanf(stream, "%c", &index);

	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			a->m->string_A[i++]='\0';i=0;break;
		}
		a->m->string_A[i++]=index;
	}

	/* PWD read */
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%c", &index);
	fscanf(stream, "%c", &index);

	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			a->m->string_D[i++]='\0';i=0;break;
		}
		a->m->string_D[i++]=index;
	}

	/* PWM read */
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%c", &index);
	fscanf(stream, "%c", &index);

	while (!feof(stream)) {
		fscanf(stream, "%c", &index);
		if (index=='\n') {
			a->m->string_M[i++]='\0';i=0;break;
		}
		a->m->string_M[i++]=index;
	}
	fclose(stream);
	pthread_exit(NULL);
	exit(0); /* inutile, toglie warning eclipse */
}

void *pwa(void *data) {
	FILE *stream; /* file csv */

	struct arg *a;
	a = (struct arg *) data;

	if((stream = fopen(a->file, "a"))==NULL){
		printf("[8.] Errore nella apertura File Dest A\n");exit(1);
	}
	fprintf(stream, "\n%s\n", a->m->string_A);
	fclose(stream);
	pthread_exit(NULL);
	exit(0); /* inutile, toglie warning eclipse */
}

void *pwd(void *data) {
	FILE *stream; /* file csv */

	struct arg *a;
	a = (struct arg *) data;

	if((stream = fopen(a->file, "a"))==NULL){
		printf("[8.] Errore nella apertura File Dest D\n");exit(1);
	}
	fprintf(stream, "%s\n", a->m->string_D);
	fclose(stream);
	pthread_exit(NULL);
	exit(0); /* inutile, toglie warning eclipse */
}

void *pwm(void *data) {
	FILE *stream; /* file csv */

	struct arg *a;
	a = (struct arg *) data;

	if((stream = fopen(a->file, "a"))==NULL){
		printf("[8.] Errore nella apertura File Dest M\n");exit(1);
	}
	fprintf(stream, "%s\n", a->m->string_M);
	fclose(stream);
	pthread_exit(NULL);
	exit(0); /* inutile, toglie warning eclipse */
}

void *ppp(void *data) {
	FILE *stream; /* file csv */

	struct arg *a;
	a = (struct arg *) data;
	
	if((stream = fopen("matrice_turni.csv", "r"))==NULL){
		printf("[8.] Errore nella apertura File\n");exit(1);
	}
	char c;
	while (!feof(stream)) {
		fscanf(stream, "%c", &c);
		printf("%c", c);
	}
	fclose(stream);
	pthread_exit(NULL);
	exit(0); /* inutile, toglie warning eclipse */
}

void stamp_C() {
	char mese[9]; /* input mese */
	char file[25]; /* file estrapolato dai vari input */
	int i; /* var temporanea */
	int anno; /* input anno */
	int days; /* set giorni del mese */
	FILE *stream; /* file csv */
	msg *m; m = (msg *) malloc (sizeof(msg));
	pthread_t threads[5];
	int rc;

	do{
		printf("[8.] Inserisci Mese: ");
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
		printf("[8-] Mese non valido\n");
	}while (1);

	if (strcmp(mese,"Febbraio")==0) {
		anno=set_anno(days, 2, 8);
	}
	else {
		anno=set_anno(days, 1, 8);
	}
	struct arg a;
	sprintf(a.file2, "%s_%d.csv", mese, anno);
	sprintf(a.file, "turni_%s",a.file2);
	a.m=m;

	if((stream = fopen(a.file, "r"))==NULL){
		printf("[8.] Errore nella apertura File\n");return;
	}
	fclose(stream);

	for(i=0; i<4; i++) {
		if (i==0) {
			rc= pthread_create(&threads[i], NULL, pr, (void *) &a);
		}
		if (i==1) {
			rc= pthread_create(&threads[i], NULL, pwa, (void *) &a);
		}
		if (i==2) {
			rc= pthread_create(&threads[i], NULL, pwd, (void *) &a);
		}
		if (i==3) {
			rc= pthread_create(&threads[i], NULL, pwm, (void *) &a);
		}
		if (rc) {
			printf("[8.] Errore nella creazione Thread\n");return;
		}
		pthread_join(threads[i], NULL);
	}


	rc= pthread_create(&threads[4], NULL, ppp, (void *) &a);
	if (rc) {
		printf("[8.] Errore nella creazione Thread\n");return;
	}
	pthread_join(threads[i], NULL);
	
	printf("[8.] Concluso\n\n");
	return;
}
