.section .data
	aper: .byte 0
	chiu: .byte 0
	count: .byte 0
	lumvol: .byte 0
	lumeff: .byte 0

.section .text
	.global _start
	
_start:

	xor %eax,%eax  #azzero ed inizializzo tutte i registri
	xor %ebx,%ebx
	xor %ecx,%ecx
	xor %edx,%edx
	movb $0,aper  # pongo a zero tutte le variabili
	movb $0,chiu
	movb $0,count
	movb $0,lumvol
	movb $0,lumeff

	pushl %ebp  #salva in cima allo stack il contenuto di ebp
	movl %esp, %ebp	 #ebp punta alla memoria puntata da esp
	subl $96, %esp		#grandezza stack

	xorl %edx,%edx
	movl %ebp,%edx
	movl %edx,%eax

	subl $20,%eax  #stack prima usate per immissione, ora seleziono per confronto
	movl %eax,%esi  #punta alla stringa vettore/sorgente
	xor %eax,%eax  #azzera eax

go:

	call immissione  #chiamo funzione immissione
 	
	xor %eax,%eax 

	movl %ebp,%edx  #chiamo funzione confronto
	xorl %ecx,%ecx
	movl count,%ecx
	call confronto

	movl %ebp,%edx
	movl %ecx,count
	
	jmp go  #salto a go, se non ci sono errori esterni (come spegnimento hardware) il programma continua a girare
