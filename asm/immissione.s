.bss  #riserva spazio memoria

stringa: .word 20  #stringa lunga 20 word per informazioni dall'utente

.section .data
	str:  #etichetta
		.ascii "Immettere i valori per APERTE, CHIUSE, LUMINOSITA' VOLUTA, LUMINOSITA' EFFETTIVA\n"
	str_lung:
		.long . - str  #lunghezza della stringa in byte	
error_i:
	.ascii "COMANDO TENDE: ERRORE INPUT\n\n"
error_i_lung:
	.long . - error_i
error_s:
	.ascii "COMANDO TENDE: ERRORE SENSORI\n\n"
error_s_lung:
	.long . - error_s

	aper: .byte 0
	chiu: .byte 0
	lumvol: .byte 0
	lumeff: .byte 0

.section .text
	.global immissione
.type immissione, @function  #dichiarazione tipo funzione

immissione:


	pushl %ebp  #stack
	movl %edx, %ebp  #ebp di input

cod:

	movl $0,aper  #inizializzo variabili definite nel .data
	movl $0,chiu
	movl $0,lumvol
	movl $0,lumeff

	mov $4,%eax  #codice per stampare richesta dati, carica system call write
	mov $1,%ebx  #scrivere in standard output
	leal str, %ecx  #carica indirizzo memoria associato
	mov str_lung, %edx  #lunghezza stringa
	int $0x80  #esegue la system call 

	movl $3, %eax  #codice per leggere dati, carica system call read
	movl $0, %ebx  #standard input
	movl $stringa, %ecx
	movl $100, %edx 
	int $0x80

	xor %ecx,%ecx
	leal stringa, %ecx  #primo elem con il counter ecx
	
	xor %eax,%eax  #codice aper
	movb 0(%ecx),%al  
	movb %al,aper  #memorizza in aper 8 byte meno significativi di eax
	cmp $48,aper  #confronto con codice ascii del carattere '0'
	je continua_a  #salta se uguale 0
	cmp $49,aper  #confronto con codice ascii del carattere '1'
	je continua_a  #salta se uguale 1
	jmp erroreinput  #da specifiche altri dati da errore

continua_a:  #codice spazio
	xor %eax,%eax
	incl %ecx  #incrementa valore
	movb 0(%ecx),%al
	cmp $0x20,%al   #confronto con codice ascii del carattere ' '
	jne erroreinput	 #da specifiche, se diverso da spazio da errore

	xor %eax,%eax  #codice chiu
	incl %ecx
	movb 0(%ecx),%al
	movb %al,chiu
	cmp $48,chiu
	je continua_c  #salta se uguale 0
	cmp $49,chiu
	je continua_c  #salta se uguale 1
	jmp erroreinput  #da specifiche altri dati da errore

continua_c:
	xor %edx,%edx
	movb aper,%dl  #8 byte meno significativi di edx
	cmp $49,%dl
	jne continua_v
	movb chiu,%dh
	cmp $49,%dh
	je erroresensori  #codice per verificare che aper e chiu non siano tutti e due 1

continua_v:

	xor %eax,%eax  #codice spazio
	incl %ecx
	movb 0(%ecx),%al
	cmp $0x20,%al
	jne erroreinput

	xor %eax,%eax  #codice lumvol
	incl %ecx
	movb 0(%ecx),%al
	movb %al,lumvol
	cmp $48,lumvol
	jl erroreinput  #se lumvol è minore di 0
	cmp $57,lumvol  #codice ascii per '9'
	jg erroreinput  #se lumvol è maggiore di 9
	cmp $49,lumvol
	jne continua_vol_n10	 #se lumvol diverso da 1

	mov %eax,%eax  #codice per trovare 10
	incl %ecx
	movb 0(%ecx),%al
	cmp $48,%al
	jne continua_vol_10  #se lumvol diverso da 0
	movl $58,lumvol  
	
continua_vol_n10: 
	xor %eax,%eax  #se tra 0 e 9, cifra dopo è spazio, completato da codice dopo
	incl %ecx
	movb 0(%ecx),%al

continua_vol_10:
	cmp $0x20,%al  #range massimo doppia cifra è 10, oltre è errore
	jne erroreinput

continua_eff:
	xor %eax,%eax  #codice lumeff
	incl %ecx
	movb 0(%ecx),%al
	movb %al,lumeff
	cmp $48,lumeff
	jl erroreinput  #se lumeff è minore di 0
	cmp $57,lumeff
	jg erroreinput  #se lumeff è maggiore di 9
	cmp $49,lumeff
	jne continua_eff_n10	

	xor %eax,%eax  #codice per trovare 10
	incl %ecx
	movb 0(%ecx),%al
	cmp $48,%al
	jne continua_eff_10  #se lumeff diverso da 0
	movl $58,lumeff

continua_eff_n10:  
	xor %eax,%eax  #se tra 0 e 9, cifra dopo è invio, completato da codice dopo
	inc %ecx
	movb 0(%ecx),%al

continua_eff_10:
	cmp $10,%al  #codice ascii 'line feed'
	jne erroreinput
	
	jmp sal  #fine input, salta a dopo errori
	

erroresensori:
	movl $4,%eax
	movl $1,%ebx
	movl $error_s,%ecx  #stampa errore sensori
	movl error_s_lung,%edx
	int $0x80
	jmp cod  #ritorna a richiedere dati
		
erroreinput: 
	movl  $4, %eax  	
	movl  $1, %ebx
	leal  error_i, %ecx  #stampa errore input
	movl  error_i_lung, %edx
	int   $0x80
	jmp cod  #ritorna a richiedere dati
	
sal:  #salto per inserire le funzioni di errore
	xor %eax,%eax

#aper sullo stack come valore di ritorno
	movb aper,%al
	movb %al,-16(%ebp)  #4 casella

#chiu sullo stack come valore di ritorno
	movb chiu,%al
	movb %al,-12(%ebp)  #3 casella

#lumvol sullo stack come valore di ritorno
	movb lumvol,%al
	movb %al,-8(%ebp)  #2 casella

#lumeff sullo stack come valore di ritorno
	movb lumeff,%al
	movb %al,-4(%ebp)  #1 casella

#puntatore alla variabile di ritorno 
	movl %ebp,%edx
	popl %ebp

ret  #ritorno

