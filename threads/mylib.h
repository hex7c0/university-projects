/*********************
		Definizioni
*********************/
#ifndef MYLIB_H_
#define MYLIB_H_

extern void flush();
extern int set_anno(int days, int mese, int i);
extern int compare(const void *a, const void *b);
typedef struct utenza {
	int tot_disponibilita;
	char gruppo;
	char nome[40];
	char buffer[200];
} ut;
typedef struct gruppi {
	int tot_utenti;
	char turno[4];
	char utenti[1000];
	int coperto;
} gr;
typedef struct record {
	char string_A[2000];
	char string_D[2000];
	char string_M[2000];
} msg;

extern void make_C();
extern void insert_I();
extern void view_C();
extern void disp_A();
extern void view_G();
extern void view_N();
extern void sched_T();
extern void stamp_C();

#endif /* MYLIB_H_ */
