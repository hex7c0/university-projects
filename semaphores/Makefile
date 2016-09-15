
# Sources:
SRCS:=main.c mylib.c crea_calendario.c disponibilità.c inserisci_indisponibilità.c scheduling.c stampa.c visualizza_calendario.c visualizza_giornaliere.c visualizza_nominali.c
OBJS:=$(SRCS:.c=.o)

# Config:
CC:=gcc
CFLAGS:= -c
LD:=gcc

# Targets:

all: vr087968

clean:
	@echo Cleaning.
	@rm -f *.o
	@rm -f example

vr087968: $(OBJS)
	@echo $@
	@$(LD) -o $@ $^


%.o:%.c
	@echo $@
	@ $(CC) $(CFLAGS) -o $@ $<

.PHONY: all clean
