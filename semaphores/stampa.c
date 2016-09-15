/*********************
		Punto 8
/********************/
#include "mylib.h" /* definizione mylib */
#include <string.h> /* stringhe */
#include <stdlib.h> /* exit */
#include <stdio.h> /* I/O */
#include <unistd.h> /* fork */
#include <sys/types.h> /* libreria processi */
#include <sys/ipc.h> /* code */
#include <sys/msg.h>
#define MSGTYPE 1

int pr(char file[25]) {
	char turni[2000]; /* stringa di turni tmp*/
	msg *mA;
	msg *mD;
	msg *mM;
	char index;
	int i=0; /* tmp for */
	int count=0; /* contatore utenti */
	FILE *stream; /* file csv */
	FILE *stream2; /* file csv */
	key_t msgkey;
	int msgid, pwa, pwd, pwm;

	if((stream = fopen(file, "r"))==NULL){
		printf("[8.] Errore nella apertura File Src\n");exit(1);
	}
	else {
		sprintf(turni, "turni_%s",file);
		while (!feof(stream)) {
			fscanf(stream, "%c", &index);
			if (index==';' && i==1) {
				break;
			}
			if (index==';') {
				i++;
			}
		}
		if((stream2 = fopen(turni, "w"))==NULL){
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
	mA = (msg *) malloc (sizeof(msg));
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%c", &index);
	fscanf(stream, "%c", &index);

	while (!feof(stream)) {
			fscanf(stream, "%c", &index);
			if (index=='\n') {
				mA->string[i++]='\0';i=0;break;
			}
			mA->string[i++]=index;
	}
	mA->type=MSGTYPE;

	/* PWD read */
	mD = (msg *) malloc (sizeof(msg));
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%c", &index);
	fscanf(stream, "%c", &index);

	while (!feof(stream)) {
			fscanf(stream, "%c", &index);
			if (index=='\n') {
				mD->string[i++]='\0';i=0;break;
			}
			mD->string[i++]=index;
	}
	mD->type=MSGTYPE;

	/* PWM read */
	mM = (msg *) malloc (sizeof(msg));
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%s", turni);
	fscanf(stream, "%c", &index);
	fscanf(stream, "%c", &index);

	while (!feof(stream)) {
			fscanf(stream, "%c", &index);
			if (index=='\n') {
				mM->string[i++]='\0';i=0;break;
			}
			mM->string[i++]=index;
	}
	mM->type=MSGTYPE;

	fclose(stream);

	/* PWA */
	pwa=ftok("stampa.c", 'a');
	if ((msgid = msgget(pwa, (0666|IPC_CREAT|IPC_EXCL)))==-1) {
		perror("Errore creazione coda messaggi P A");
		exit(1);
	}
	msgsnd(msgid, mA, sizeof(msg)-sizeof(mA->type),0);

	/* PWM */
	pwm=ftok("stampa.c", 'm');
	if ((msgid = msgget(pwm, (0666|IPC_CREAT|IPC_EXCL)))==-1) {
		perror("Errore creazione coda messaggi P M");
		exit(1);
	}
	msgsnd(msgid, mM, sizeof(msg)-sizeof(mM->type),0);

	/* PWD */
	pwd=ftok("stampa.c", 'd');
	if ((msgid = msgget(pwd, (0666|IPC_CREAT|IPC_EXCL)))==-1) {
		perror("Errore creazione coda messaggi P A");
		exit(1);
	}
	msgsnd(msgid, mD, sizeof(msg)-sizeof(mD->type),0);

	exit(0);
}

int pwa(char file[25]) {
	char tmp[30]; /* stringa di turni */
	FILE *stream; /* file csv */
	int msgid, pwa;

	sprintf(tmp, "turni_%s",file);
	pwa=ftok("stampa.c", 'a');
	msg *m;
	m = (msg *) malloc (sizeof(msg));

	sleep(1);
	if ((msgid = msgget(pwa,0666))==-1){
		perror("Errore creazione coda messaggi A");
		exit(1);
	}
	msgrcv(msgid, m, sizeof(msg) -sizeof(m->type), MSGTYPE,0);
	msgctl(msgid, IPC_RMID, NULL);

	if((stream = fopen(tmp, "a"))==NULL){
		printf("[8.] Errore nella apertura File Dest A\n");exit(1);
	}
	fprintf(stream, "\n%s\n", m->string);
	fclose(stream);

	exit(0);
}

int pwd(char file[25]) {
	char tmp[30]; /* stringa di turni */
	FILE *stream; /* file csv */
	int msgid, pwd;

	sprintf(tmp, "turni_%s",file);
	pwd=ftok("stampa.c", 'd');
	msg *m;
	m = (msg *) malloc (sizeof(msg));

	sleep(2);
	if ((msgid = msgget(pwd,0666))==-1){
		perror("Errore creazione coda messaggi D");
		exit(1);
	}
	msgrcv(msgid, m, sizeof(msg) -sizeof(m->type), MSGTYPE,0);
	msgctl(msgid, IPC_RMID, NULL);

	if((stream = fopen(tmp, "a"))==NULL){
		printf("[8.] Errore nella apertura File Dest D\n");exit(1);
	}
	fprintf(stream, "%s\n", m->string);
	fclose(stream);

	exit(0);
}

int pwm(char file[25]) {
	char tmp[30]; /* stringa di turni */
	FILE *stream; /* file csv */
	int msgid, pwm;

	sprintf(tmp, "turni_%s",file);
	pwm=ftok("stampa.c", 'm');
	msg *m;
	m = (msg *) malloc (sizeof(msg));

	sleep(3);
	if ((msgid = msgget(pwm,0666))==-1){
		perror("Errore creazione coda messaggi M");
		exit(1);
	}
	msgrcv(msgid, m, sizeof(msg) -sizeof(m->type), MSGTYPE,0);
	msgctl(msgid, IPC_RMID, NULL);

	if((stream = fopen(tmp, "a"))==NULL){
		printf("[8.] Errore nella apertura File Dest M\n");exit(1);
	}
	fprintf(stream, "%s\n", m->string);
	fclose(stream);

	exit(0);
}

void stamp_C() {
	char mese[9]; /* input mese */
	char file[25]; /* file estrapolato dai vari input */
	pid_t pro[4]; /* array pid processi */
	int i; /* var temporanea */
	int anno; /* input anno */
	int days; /* set giorni del mese */
	FILE *stream; /* file csv */

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
	sprintf(file, "%s_%d.csv", mese, anno);

	if((stream = fopen(file, "r"))==NULL){
		printf("[8.] Errore nella apertura File\n");return;
	}
	fclose(stream);

	for(i=0; i<4; i++) {
		if((pro[i] = fork()) == -1) {
			printf("[8.] Errore nella creazione di Processi\n");exit(1);
		}
		if(pro[i]==0 && i==0) {
			if (pr(file)==0) {
				exit(0);
			}
		}
		if(pro[i]==0 && i==1) {
			if (pwa(file)==0) {
				exit(0);
			}
		}
		if(pro[i]==0 && i==2) {
			if (pwd(file)==0) {
				exit(0);
			}
		}
		if(pro[i]==0 && i==3) {
			if (pwm(file)==0) {
				exit(0);
			}
		}
	}

	wait(0);wait(0);wait(0);wait(0);
	printf("[8.] Concluso\n\n");
	return;
}
