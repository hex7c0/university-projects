/*********************
		Punto 7
/********************/
#include "mylib.h" /* definizione mylib */
#include <string.h> /* stringhe */
#include <stdlib.h> /* exit */
#include <stdio.h> /* I/O */
#include <unistd.h> /* fork */
#include <sys/types.h> /* libreria processi */
#include <string.h>
#include <sys/ipc.h> /* semafori */
#include <sys/sem.h>
#include <time.h>

int pa(char file[18], int semid) {
	char turni[1500]; /* stringa di turni */
	char orig[1500]; /* stringa di turni originale */
	char tmp[100]; /* stringa totalità */
	char nome[40];
	char index;
	long pointer; /* posizione ftell */
	int i, ii=0, t=0, x=0; /* tmp for */
	int count=0; /* contatore utenti */
	FILE *stream; /* file csv */
	struct sembuf * sops = (struct sembuf * ) malloc (sizeof(struct sembuf));

	if ((stream = fopen(file, "r"))==NULL) {
		printf("[7.] Errore nella visualizzazione del File\n");
		exit(1);
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
	sops[0].sem_num=1; /* sblocco il semaforo 1 */
	sops[0].sem_op=-1; /* da 1 lo faccio passare a 0 */
	sops[0].sem_flg=0;
	semop(semid, sops, 1);
	sops[0].sem_num=2; /* sblocco il semaforo 2 */
	sops[0].sem_op=-1; /* da 1 lo faccio passare a 1 */
	sops[0].sem_flg=0;
	semop(semid, sops, 1);

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
	sops[0].sem_num=1;
	sops[0].sem_op=-1;
	sops[0].sem_flg=0;
	semop(semid, sops, 1); /* sblocco come sopra */
	sops[0].sem_num=2; /* sblocco il semaforo 2 */
	sops[0].sem_op=-1; /* da 1 lo faccio passare a 1 */
	sops[0].sem_flg=0;
	semop(semid, sops, 1);
	exit(0);
}

int pd(char file[18], int semid) {
	char turni[1500]; /* stringa di turni */
	char orig[1500]; /* stringa di turni originale */
	char tmp[100]; /* stringa totalità */
	char nome[40];
	char index;
	long pointer; /* posizione ftell */
	int i, ii=0, t=0, x=0; /* tmp for */
	int count=0; /* contatore utenti */
	FILE *stream; /* file csv */
	struct sembuf * sops = (struct sembuf * ) malloc (sizeof(struct sembuf));
	sops[0].sem_num=1; /* semaforo 1 posto a 1 */
	sops[0].sem_op=1;
	sops[0].sem_flg=0;
	semop(semid, sops, 1);

	sops->sem_num=1; /* attendo di essere posto a 0 */
	sops->sem_op=0;
	sops->sem_flg=0;
	if ((stream = fopen(file, "r"))==NULL) {
		printf("[7.] Errore nella visualizzazione del File\n");
		exit(1);
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
	sops[0].sem_num=2; /* semaforo 1 posto a 1 */
	sops[0].sem_op=-1;
	sops[0].sem_flg=0;
	semop(semid, sops, 1);

	for (i=0; i<count-3;i++) { /* bug dello scanf. copia anche valori errati */
		//fprintf(stream,"%s\n", utente[i].nome); /* mostrabile in stampata */
		if (!isalpha(utente[i].nome[0])) { /* data link escape o del */
			for (ii=0;ii<strlen(utente[i].nome)-1;ii++) {
				utente[i].nome[ii]=utente[i].nome[ii+1];
			}
			utente[i].nome[ii]='\0';
		}
	}
	sops[0].sem_num=4; /* semaforo 4 bloccato */
	sops[0].sem_op=1;
	sops[0].sem_flg=0;
	semop(semid, sops, 1);
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
	sops[0].sem_num=4; /* semaforo 4 posto sbloccato */
	sops[0].sem_op=-1;
	sops[0].sem_flg=0;
	semop(semid, sops, 1);

	sops->sem_num=5; /* semaforo 1 posto a 1 */
	sops->sem_op=0;
	sops->sem_flg=0;
	semop(semid, sops, 1);
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

	for (i=0; i<t; i++) {
		if (matrix_D[i].tot_utenti==0) {
			printf("[7.] Warning D: nessun utente disponibile per il turno %s\n", matrix_D[i].turno);
		}
		if (matrix_D[i].coperto==0) {
			printf("[7.] Warning D: turno %s non assegnato\n", matrix_D[i].turno);
		}
	}

	sops[0].sem_num=1; /* semaforo 1 posto a 1 */
	sops[0].sem_op=1;
	sops[0].sem_flg=0;
	semop(semid, sops, 1);

	sops->sem_num=1; /* attendo di essere posto a 0 */
	sops->sem_op=0;
	sops->sem_flg=0;
	//printf("2\n");
	sleep(1);
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
	sops[0].sem_num=2; /* sblocco il semaforo 2 */
	sops[0].sem_op=-1; /* da 1 lo faccio passare a 0 */
	sops[0].sem_flg=0;
	semop(semid, sops, 1);
	exit(0);
}

int pm(char file[18], int semid) {
	char turni[1500]; /* stringa di turni */
	char orig[1500]; /* stringa di turni originale */
	char tmp[100]; /* stringa totalità */
	char nome[40];
	char index;
	long pointer; /* posizione ftell */
	int i, ii=0, t=0, x=0; /* tmp for */
	int count=0; /* contatore utenti */
	FILE *stream; /* file csv */
	struct sembuf * sops = (struct sembuf * ) malloc (sizeof(struct sembuf));
	sops[0].sem_num=2; /* 2 a 1*/
	sops[0].sem_op=2;
	sops[0].sem_flg=0;
	semop(semid, sops, 1);

	sops->sem_num=2; /* attendo di essere posto a 0 */
	sops->sem_op=0;
	sops->sem_flg=0;
	if ((stream = fopen(file, "r"))==NULL) {
		printf("[7.] Errore nella visualizzazione del File\n");
		exit(1);
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

	for (i=0; i<count-3;i++) { /* bug dello scanf. copia anche valori errati */
		//fprintf(stream,"%s\n", utente[i].nome); /* mostrabile in stampata */
		if (!isalpha(utente[i].nome[0])) { /* data link escape o del */
			for (ii=0;ii<strlen(utente[i].nome)-1;ii++) {
				utente[i].nome[ii]=utente[i].nome[ii+1];
			}
			utente[i].nome[ii]='\0';
		}
	}

	sops[0].sem_num=5; /* semaforo 5 posto bloccato */
	sops[0].sem_op=1;
	sops[0].sem_flg=0;
	semop(semid, sops, 1);
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
	sops[0].sem_num=5; /* semaforo 5 posto sbloccato */
	sops[0].sem_op=-1;
	sops[0].sem_flg=0;
	semop(semid, sops, 1);

	sops->sem_num=4; /* semaforo 1 posto a 1 */
	sops->sem_op=0;
	sops->sem_flg=0;
	semop(semid, sops, 1);
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

	for (i=0; i<t; i++) {
		if (matrix_M[i].tot_utenti==0) {
			printf("[7.] Warning M: nessun utente disponibile per il turno %s\n", matrix_M[i].turno);
		}
		if (matrix_M[i].coperto==0) {
			printf("[7.] Warning M: turno %s non assegnato\n", matrix_M[i].turno);
		}
	}

	sops[0].sem_num=2; /* 2 a 1*/
	sops[0].sem_op=2;
	sops[0].sem_flg=0;
	semop(semid, sops, 1);

	sops->sem_num=2; /* attendo di essere posto a 0 */
	sops->sem_op=0;
	sops->sem_flg=0;
	//printf("3\n");
	sleep(2);
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
	exit(0);
}

void sched_T() {
	pid_t pro[3]; /* array pid processi */
	FILE *stream; /* file csv */
	char mese[9]; /* input mese */
	char file[18]; /* file estrapolato dai vari input */
	int i; /* var temporanea */
	int anno; /* input anno */
	int days; /* set giorni del mese */
	int semid;
	srand(time(NULL));

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

	/* inizializzo i semafori */
	if ((semid=semget(rand(), 5, IPC_CREAT | IPC_EXCL | 0777))==-1) {
		printf("[7.] Errore nella crezione semafori. Chiave già in uso\n");exit(1);
	}

	if((stream = fopen("matrice_turni.csv", "r"))==NULL){
		printf("[7.] Errore nella apertura File. Esegui prima punto 4\n");unlink("matrice_turni.csv");return;
	}
	fclose(stream);

	for(i=0; i<3; i++) {
		if((pro[i] = fork()) == -1) {
			printf("[7.] Errore nella creazione di Processi\n");
		}
		if(pro[i]==0 && i==0) {
			if (pa(file, semid)==0) {
				exit(0);
			}
		}
		if(pro[i]==0 && i==1) {
			if (pd(file, semid)==0) {
				exit(0);
			}
		}
		if(pro[i]==0 && i==2) {
			if (pm(file, semid)==0) {
				exit(0);
			}
		}
	}
	wait(0);wait(0);wait(0);
	printf("[7.] Concluso\n\n");
	return;
}
