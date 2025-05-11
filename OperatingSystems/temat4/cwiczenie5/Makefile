.SUFFIXES: .c .cpp .o .x .h

# zmienne inne
DIR = $(notdir $(CURDIR))
LIBDIR = ./lib

# nazwy plikow .c
NAME1 = producent
NAME2 = konsument
NAME3 = main
NAME6 = dane.txt
NAME7 = wynik.txt
POTOK = potok

# posrednie pliki skompilowane
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o

# pliki wykonywalne
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x

# opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic

# linkowane biblioteki
LDLIBS = -lm

# kompilator i linker
CO = gcc
LD = $(CO)

##############
# reguly zaleznosci
##############
%.o: %.c
	$(CO) $(CFLAGS) -c $<



$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $< $(LDLIBS)
$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $< $(LDLIBS)
$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $< $(LDLIBS)

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)

.PHONY: run1
run1: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC3) $(EXEC1) $(EXEC2) $(NAME6) $(NAME7) $(POTOK)
	diff -s $(NAME6) $(NAME7)

run2: $(EXEC1) $(EXEC2)
	mkfifo -m 0644 $(POTOK)
	xterm -hold -title PRODUCENT -e ./$(EXEC1) $(NAME6) $(POTOK) &
	xterm -hold -title KONSUMENT -e ./$(EXEC2) $(NAME7) $(POTOK)
	rm $(POTOK)
	diff -s $(NAME6) $(NAME7)

.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
