/*********************
		Elaborato 2
		@author Carnielli Francesco
		@file main.c, crea_calendario.c,
		disponibilità.c, inserisci_indisponibilità.c
		mylib.c mylib.h
		scheduling.c stampa.c
		visualizza_calendario.c
/********************/
#include "mylib.h" /* definizione mylib */
#include <stdio.h> /* printf() */
#include <ctype.h>
#include <stdlib.h>
#include <ctype.h>

void intro() {
	char menu[] = "MENU\n"
			"\t1. Crea calendario mese.\n"
			"\t2. Inserisci disponibilità utente.\n"
			"\t3. Visualizza calendario.\n"
			"\t4. Crea archivio disponibilità giornaliere.\n"
			"\t5. Visualizza totali disponibilità giornaliere.\n"
			"\t6. Visualizza totali disponibilità nominali.\n"
			"\t7. Scheduling dei turni.\n"
			"\t8. Stampa calendario dei turni.\n"
			"\t9. Esci.\n"
			"OPZIONE: ";
	char choice;

	clearscreen();
	do{
		printf("%s", menu);
		choice = getchar();
		//flush();
		if (isdigit(choice)) {
			switch(choice) {
			case '1':
				printf("\n");make_C();
				break;
			case '2':
				printf("\n");insert_I();
				break;
			case '3':
				printf("\n");view_C();
				break;
			case '4':
				printf("\n");disp_A();
				break;
			case '5':
				printf("\n");view_G();
				break;
			case '6':
				printf("\n");view_N();
				break;
			case '7':
				printf("\n");sched_T();
				break;
			case '8':
				printf("\n");stamp_C();
				break;
			case '9':
				printf("\nBye!\n");return;
			default:
				printf("Opzione non valida\n");
				break;
			}
		}
	} while (choice != '9');
	printf("\nBye!\n");
	return;
}

int main (int argc, char *argv[]){

	intro();
	exit(0);
}

