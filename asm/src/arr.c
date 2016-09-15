#include <stdio.h>
#include "arr.h"

int main () {
int ape, chi, eff, vol, ris=0;

//system ("cls"); da usare se SO windows

do {
puts("");
puts("inserire APERTE");
scanf("%d", &ape);
puts("inserire CHIUSE");
scanf("%d", &chi);
puts("inserire VOL");
scanf("%d", &vol);
puts("inserire EFF");
scanf("%d", &eff);

if ( (ape == 1 || chi == 1)&& chi == ape)
	{
	printf("COMANDO TENDE: ERRORE SENSORI");
	exit(1);
	}
	
if (err_input(ape, chi, vol, eff)==0)
	{
	printf("COMANDO TENDE: ERRORE INPUT");
	exit(1);
	}

comando_tende(ape, chi, vol, eff);

puts("");
puts("Vuoi inserire altri dati? rispondi 1 per si, 0 per no");
scanf("%d", &ris);

}while (ris==1);

return 0;
}
