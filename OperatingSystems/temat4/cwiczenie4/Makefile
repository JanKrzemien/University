.SUFFIXES: .c .cpp .o .x .h

# zmienne inne
DIR = $(notdir $(CURDIR))
LIBDIR = ./lib

# nazwy plikow .c
NAME1 = main
NAME3 = dane.txt
NAME4 = wynik.txt

# posrednie pliki skompilowane
OBJS1 = $(NAME1).o

# pliki wykonywalne
EXEC1 = $(NAME1).x

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

.PHONY: all
all: $(EXEC1)

.PHONY: run1
run1: $(EXEC1)
	./$(EXEC1) $(NAME3) $(NAME4)
	diff -s $(NAME3) $(NAME4)

.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
