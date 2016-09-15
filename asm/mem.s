.bss
.section .data


standbya:
	.ascii "STAND-BY per APRI\n"
standbya_lung:
	.long . - standbya
standbyc:
	.ascii "STAND-BY per CHIUDI\n"
standbyc_lung:
	.long . - standbyc
standbyn:
	.ascii "STAND-BY per Luminosita' Corretta\n"
standbyn_lung:
	.long . - standbyn
	
	count: .byte 0

.section .text
.global mem
.type mem, @function  #dichiarazione tipo funzione

mem:
	pushl %ebp
	movl %edx, %ebp
	movl %edx,%ecx
	subl $16,%ecx

	xor %esi,%esi
	movl %ecx,%esi  #prima istruzione libera
	movl %eax,count

controllo:
	xor %eax,%eax
	movb count,%ah
	cmp $0,%ah
	je end  #salta se 0
	decl count  #decrementa counter
	subl $4,%esi
	cmp $1,(%esi)
	je stampaa  #se uguale per apri (definito nel confronto)
	cmp $2,(%esi)
	je stampac  #se uguale per chiudi (definito nel confronto)
	cmp $3,(%esi)
	je stampas  #se uguale per stand-by (definito nel confronto)

	jmp end
	
stampaa:
	movl $4, %eax 
	movl $1, %ebx
	leal standbya, %ecx  #stampa per stand-by per apri
	movl standbya_lung, %edx
	int $0x80

	jmp controllo
	
stampac:
	movl $4, %eax
	movl $1, %ebx
	leal standbyc, %ecx  #stampa per stand-by per apri
	movl standbyc_lung, %edx
	int $0x80
	
	jmp controllo

stampas:
	movl $4, %eax 
	movl $1, %ebx
	leal standbyn, %ecx
	movl standbyn_lung, %edx
	int $0x80
	
	jmp controllo

end:
	movl %ebp, %edx
	movl %edx,%eax
	subl $20,%eax  #stack 5 casella
	movl %eax,%esi
	movl $0,count
	xorl %eax,%eax  #azzeramento registri
	xorl %ebx,%ebx
	xorl %ecx,%ecx
	xorl %edx,%edx
	
popl %ebp  #riporta il registro ebp alla situazione di partenza
ret  #ritorno

