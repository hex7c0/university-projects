#include <stdio.h>
#include "arr.h"

int standbya=0, standbyc=0, standbyn=0, count=0;

int err_input(int ape, int chi, int vol, int eff) {

if (diverso_2 (ape)==0 || diverso_2 (chi)==0 || diverso_10 (vol)==0 || diverso_10 (eff)==0 )
	return 0;
else
	return 1;
}

int diverso_2 (int a) {
if (a <0 || a >1) //range massimo tra 0 e 1
	return 0;
else 
	return 1;

}

int diverso_10 (int v) {
if ( v <0 || v >10) //range massimo tra o e 10
	return 0;
else 
	return 1;
}

void comando_tende (int ape, int chi, int vol, int eff) {
int i;

if (vol>eff && ape==0) {
	puts("COMANDO TENDE:APRI");
	for (i=0; i<=count; i++) {
		if (standbya>0) {
		puts("STAND-BY per APRI");
		standbya--;
		}
		if (standbyc>0) {
		puts("STAND-BY per CHIUDI");
		standbyc--;
		}
		if (standbyn>0) {
		puts("STAND-BY per Lum Uguale");
		standbyn--;
		}
	}
	}
else if (vol>eff && ape==1) {
	puts("STAND-BY per APRI");
	standbya++; count++;
	}
else if (vol<eff && chi==0) {
	puts("COMANDO TENDE:CHIUDI");
		for (i=0; i<count; i++) {
		if (standbya>0) {
		puts("STAND-BY per APRI");
		standbya--;
		}
		if (standbyc>0) {
		puts("STAND-BY per CHIUDI");
		standbyc--;
		}
		if (standbyn>0) {
		puts("STAND-BY per Lum Uguale");
		standbyn--;
		}
	}
	}
else if (vol<eff && chi==1) {
	puts("STAND-BY per CHIUDI");
	standbyc++; count++;
	}
else if (vol==eff)
	puts("STAND-BY per Lum Uguale"); {
	standbyn++; count++;
	}

}
