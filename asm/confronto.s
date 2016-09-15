.bss
.section .data

aprire:
	.ascii "COMANDO TENDE: APRI\n\n"
aprire_lung:
	.long . - aprire
chiudere:
	.ascii "COMANDO TENDE: CHIUDI\n\n"
chiudere_lung:
	.long . - chiudere
standby:
	.ascii "COMANDO TENDE: STAND-BY\n\n"
standby_lung:
	.long . - standby

	count: .byte 0
	aper: .byte 0
	chiu: .byte 0
	lumvol: .byte 0
	lumeff: .byte 0
	
.section .text
.global confronto
.type confronto, @function  #dichiarazione tipo funzione

confronto:

	pushl %ebp  #recupero valori dallo stack
	movl %edx, %ebp
	movl %ecx,count
	movl -16(%ebp), %eax   #recupero il valore di aperte (4 casella)
	movl %eax,aper
	movl -12(%ebp), %eax  #recupero il valore di chiuse (3 casella)
	movl %eax,chiu
	movl -8(%ebp), %eax  #recupero il valore di luminosità voluta (2 casella)
	movl %eax,lumvol	
	movl -4(%ebp), %eax  #recupero il valore di luminosità effettiva (1 casella)	
	movl %eax,lumeff
	
	
	xor %eax,%eax
	movb lumvol,%al
	cmp lumeff,%al
	jl chiudi 	#se lum vol è minore di lum eff
	cmp lumeff,%al
	jg apri	#se lum voluta è maggiore di lum eff
	cmp lumeff,%al  
	je stanbyn	#se le due luminosità sono uguali


chiudi:
	xorl %eax,%eax
	movb chiu,%al  #se sono già chiuse metto stand-by
	cmp $49,%al
	je stanbyc

	xor %eax,%eax
	movb count,%ah
	cmp $0,%ah
	je stampa_ch
	movl %ebp,%edx

	xor %eax,%eax
	movl count,%eax
	call mem  #chiamo la funzione per memorizzare
	
stampa_ch:	
	movl $0,count
	movl  $4, %eax  
	movl  $1, %ebx
	leal  chiudere, %ecx  #stampa per chiudere
	movl  chiudere_lung, %edx
	int   $0x80
	jmp end

apri:
	xorl %eax,%eax
	movb aper,%al 
	cmp $49,%al  #se sono già aperte metto stand-by
	je stanbya

	xor %eax,%eax
	movb count,%ah
	cmp $0,%ah
	je stampa_ap
	movl %ebp,%edx
	
	xor %eax,%eax
	movl count,%eax
	call mem #chiamo la funzione per memorizzare
	
stampa_ap:
	movl $0,count
	movl  $4, %eax 
	movl  $1, %ebx
	leal  aprire, %ecx  #stampa per aprire
	movl  aprire_lung, %edx
	int   $0x80
	jmp end

stanbya:
	incl count
	xor %eax,%eax
	movl $1,%eax
	movl %eax,(%esi)  #nello stack memorizzo 1 come sb aperte
	movl $4, %eax 
	movl $1, %ebx
	leal standby, %ecx  #stampa per stand-by
	movl standby_lung, %edx
	int $0x80
	subl $4,%esi

	jmp end

stanbyc:
	incl count
	xor %eax,%eax
	movl $2,%eax
	movl %eax,(%esi)  #nello stack memorizzo 2 come sb chiuse
	subl $4,%esi
	movl $4, %eax  	
	movl $1, %ebx
	leal standby, %ecx  #stampa per stand-by
	movl standby_lung, %edx
	int $0x80
	jmp end

stanbyn:
	incl count
	xor %eax,%eax
	movl $3,%eax  #nello stack memorizzo 3 come sb uguali
	movl %eax,(%esi)
	subl $4,%esi
	movl $4, %eax
	movl $1, %ebx 
	leal standby, %ecx  #stampa per stand-by
	movl standby_lung, %edx
	int $0x80
	jmp end

end:

	xor %ecx,%ecx
	movl count,%ecx  #salvo il counter
	movl %ebp, %edx
	popl %ebp
	ret   #ritorno

