EXE= main
AS= as
LD= ld
FLAGS= -gstabs
OBJ= main.o immissione.o confronto.o mem.o
$(EXE): $(OBJ)
 $(LD) -o $(EXE) $(OBJ)
main.o: main.s
 $(AS) $(FLAGS) -o main.o main.s
immissione.o: immissione.s
 $(AS) $(FLAGS) -o immissione.o immissione.s
confronto.o: confronto.s
 $(AS) $(FLAGS) -o confronto.o confronto.s
mem.o: mem.s
 $(AS) $(FLAGS) -o mem.o mem.s
