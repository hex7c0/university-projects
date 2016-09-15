#!/bin/bash
#main del progetto
#Carnielli Francesco
source fx.sh

#Inizializzo Variabili
a="#1. Visualizza."
b="#2. Inserisci."
c="#3. Cancella."
d="#4. Seleziona."
e="#5. Unisci."
f="#6. Elenca Chiavi."
g="#7. Esci."
ins="#Inserire numero richiesta menu :"
qui="[]Chiusura. Bye!"
fil="[]Inserisci FILE su cui operare :"
rig="[]Inserisci RIGA su cui operare :"
nam="[]Inserisci il nome "
pat="[]Inserisci il PATTERN da usare :"
cop="[]Inserisci FILE da cui copiare :"
key="[]Inserisci KEY con cui lavorare:"
pat="[]Inserisci PATH su cui cercare :"
not="-- File non disponibile --"
ok="++ Done ++"
ko="-- Done --"
not_str="!Inserire una stringa corretta  ."
not_dec="!Inserire numero decimale valido."

#Stampa Elenco
clear
echo "### Terminale Human Traffic ###"
echo
MList
echo
echo -n $ins; read Input

#Passaggio Funzioni
while [[ $Input != 7 ]]
do
	case $Input in
		1) FSort;;
		2) FAdd;;
		3) FDel;;
		4) FSet;;
		5) FJoin;;
		6) FList;;
		*) echo "!Opzione non corretta.";;
	esac
	echo -n $ins; read Input
done
echo
echo $g
echo $qui
