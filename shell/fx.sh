#!/bin/bash
#funzioni del main
#Carnielli Francesco

MList() {
	#Funzione menu argomenti

	echo "##### #MENU# ######"
	echo $a
	echo $b
	echo $c
	echo $d
	echo $e
	echo $f
	echo $g
	echo "##### ###### ######"
	return 0
}

MList_Up() {
	#Funzione menu funzione

	clear
	MList
	echo
	echo $1 $2
	echo -n $fil; read X #valore del file
	return 0 
}

MTab() {
	#Funzione identificare colonne
	#input nome file, restituisce gli spazi
	
	for (( C=1 ; C>0 ; C++ )); do #loop infinito
	#equiparabile while [ 1 ]; do (con counter)
		#dato il file, avanza per i campi, basandosi sulla prima riga
		T=$( head -n 1 $1 | cut -d ' ' -f$C ) #$1 valore passato alla funzione, C contatore campo
		#guarda solo 1 riga, supponendo che il resto del programma non permetta inserimento di campi maggiori dentro altre righe
		if [[ $T ]]; then #se restituisce risultato, ok
			continue
		else
			#esce quando non ci sono pi� campi (spazi)
			(( C-- )) #passa il numero di campi reali
			break
		fi
	done
	return 0
}

FSort() {
	#1 Funzione Ordinare liste

	MList_Up $a
	if [[ -r $X ]]; then #se file leggibile (-r readable)
		echo
		sort $X | uniq #sort ordina, pipe uniq che elimina doppi
		#uniq $X | sort (possibile anche contrario)
		echo $ok; echo
	else
		echo $not; echo
	fi
	return 0
}

FAdd() {
	#2 aggiunge una riga in tabella

	MList_Up $b
	if [[ -rw $X ]]; then #se file leggibile e scrivibile (-r readable, -w writable)
		MTab $X #funzione campi
		str= #stringa vuota per aggiungere i campi
		echo "[]Disponibili $C CAMPI dentro file"
		for (( C1=0 ; C1<C ; C1++ )); do #cicla per riempire i campi
			echo -n $nam "in CAMPO $C1  :"; read Y #valore del campo
			if [[ -n $Y ]]; then
				str="$str $Y" #riempe campo aggiungendo lo spazio
			else
				echo $not_str; echo
				return 1
			fi
		done
		echo -n $rig; read Z #riga ove inserire stringa
		if [[ -n $Z && $Z == [0-9]* ]]; then #se Z non void ed isdigit
			C=$( wc -l $X | cut -d ' ' -f8 ) #f8 per mac, restituisce il numero delle righe
			if (( $Z>$C )); then #se maggiore righe disponibile
				(( Z-- )) #posizionarsi una riga sotto (si parte da 0)
				for (( C ; C<Z ; C++ )); do
					echo "" >> $X #aggiunge riga vuota
				done
				echo $str >> $X #aggiunge la riga desiderate sotto C righe dopo ultima
			else
				cp $X $X.tmp #copia temporanea
				C=1; F= #C 1 contatore, F flag se da accodare stringhe
				while read Line; do #legge riga per riga
					if (( $Z == $C )); then #se riga voluta == contatore
						if [[ $C == 1 ]]; then
							echo $str > $X #mette la stringa, senza curarsi del resto del file
							F=1
						else
							head -n$((C-1)) $X.tmp > $X #copia le prime righe del file
							echo $str >> $X #poi la aggiunge la stringa
							F=1
						fi
					fi
					if [[ -n $F ]]; then #se c'� stata l'aggiunta
						echo $Line >> $X #aggiunge le righe rimanenti, fino a EOF
					fi
					(( C++ )) #incrementa counter
				done < $X.tmp #loop while per leggere righe
				rm $X.tmp
			fi
			echo $ok
		else
			echo $not_dec
		fi
	else
		echo $not
	fi
	echo
	return 0
}

FDel() {
	#3 eliminare una riga in tabella

	MList_Up $c
	if [[ -rw $X ]]; then
		echo -n $rig; read Y
		if [[ -n $Y ]]; then #valore da cercare
			found=$( grep -niw -m1 "$Y" $X | cut -d ':' -f1 ) #scarta tutto il resto dopo ':' (ottiene solo numero riga)
			#m1 1 occorrenza, n numeri riga, i no distinzione maiusc, w parola intera
			if [[ -n $found ]]; then
				sed -i.tmp "$found"d $X #cancella valore in loco (tmp come backup)
				rm $X.tmp
				echo $ok
			else
				echo $ko
			fi
		else
			echo $not_str
		fi
	else
		echo $not
	fi
	echo
	return 0
}

FSet () {
	#4 prende 3 argomenti e stampa le occorrenze

	MList_Up $d
	if [[ -r $X ]]; then
		echo -n $nam "da CERCARE  :"; read Y #valore stringa da cercare
		if [[ -n $Y ]]; then
			echo -n $rig; read Z #valore campo per fare cernita
			if [[ -n $Z && $Z == [0-9]* ]]; then
				found=$(cut -d ' ' -f$Z $X | grep -i $Y ) #restringe al campo da cercare
				#1 passo mostra solo il campo selezionato con Z, poi cerca all'interno del risultato
				if [[ -n $found ]]; then
					echo
					sort $X | uniq > $X.tmp #crea un file temporaneo con i dati ordinati e scremati, per non doverlo fare dopo
					while read Line; do #passa ogni riga del file temp e stampa risultato
						found=$(echo $Line | cut -d ' ' -f$Z | grep -i $Y )
						#echo mostra la linea, cut taglia in base al campo, grep mostra se la riga � quella voluta altrimenti non la stampa in output
						if [[ -n $found ]]; then
							echo $Line
						fi
					done < $X.tmp
					rm $X.tmp
					echo $ok
				else
					echo $ko
				fi
			else
				echo $not_dec
			fi
		else
			echo $not_str
		fi
	else
		echo $not
	fi
	echo
	return 0
}

FJoin () {
	#5 prende 2 tabelle e unisce alla 1 la 2

	MList_Up $e
	if [[ -rw $X ]]; then
		echo -n $cop; read Y #valore del 2 file
		if [[ -rw $Y && $X != $Y ]]; then #controlla che non siano uguali
			MTab $X
			C1=$C #C1 counter temporaneo per verificare correttezza campi
			MTab $Y
			if [[ $C1 == $C ]]; then #C1 campi del 1, C campo del 2
				cat $Y >> $X #mette 2 tab in coda alla prima
				echo $ok
			else
				echo $ko
			fi
		else
			echo $not
		fi
	else
		echo $not
	fi
	echo
	return 0
}

FList () {
	#6 cerca in un path e sottodirectory delle key

	clear
	MList
	echo; echo $f
	echo -n $pat; read X #valore del path
	if [[ -r $X ]]; then
		echo -n $key; read Y #valore della chiave
		if [[ -n $Y ]]; then
			found=$( grep -lr --include="*.tab" $Y $X )
			if [[ -n $found ]]; then
				echo
				grep -l -r --include="*.tab" $Y $X
				#-l printa solo nome file
				#-r recursive, --include, nome file
				#Y chiave da cercare dentro i file
				#X directory in base a dove mi trovo e/o con radice, (. == dir corrente)
				#in caso di ricerca tramite root (solo '/'), mancano permessi
				echo $ok
			else
				echo $ko
			fi
		else
			echo $not_str
		fi
	else
		echo $not
	fi
	echo
	return 0
}