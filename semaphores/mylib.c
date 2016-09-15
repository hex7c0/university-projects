/*********************
		Libreria
/********************/
#include "mylib.h"
#include <stdio.h> /* I/O */
#include <stdlib.h> /* system() */
#include <string.h>
#include <sys/stat.h> /* FIFO */

#include <ctype.h>
#include <sys/types.h> /* system call */
#include <fcntl.h> /* system call */

void clearscreen() {
	/* pulizia schermo in base all'os */

	if (system("clear")) {
		system("cls");
	}
	return;
}

void flush() {
	/* pulizia stdin */

	while (getchar() != '\n');
}

int compare(const void *a, const void *b){
	/* funzione da passare al sort. ordina per minore */

	return (*(int*)a - *(int*)b);
}

/*int check(ut *u, int n, int t) {
	int i;int x=0;
	printf("%s>>%d>>%c\n", u[n].buffer, t, u[n].buffer[0]);

	for (i=0; i<strlen(u[n].buffer); i++) {
		if (x>t) {
			return (0);
		}
		if (u[n].buffer[i]==';') {
			if(t==x){
				return (1);
			}
			x++;
		}
		if (u[n].buffer[i]=='X'){
			i++;
		}
	}
	return (0);
}*/


int set_anno(int days, int mese, int i) {
	int anno;

	printf("[%d.] Inserisci Anno: ", i);
	while (1) {
		if (scanf ("%d", &anno) == 1){
			flush();
			if (anno > 1950 && anno <= 2100) {
				if (anno % 4 == 0 && (anno % 100 != 0 || anno % 400 == 0)) {
					if (mese==0) {
						days = 29;
					}
				}
				break;
			}
		}
	}
	return (anno);
}
