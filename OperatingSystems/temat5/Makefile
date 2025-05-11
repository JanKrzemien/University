.SUFFIXES: .c .cpp .o .x .h

# zmienne inne
DIR = $(notdir $(CURDIR))
LIBDIR = ./lib

# nazwy plikow .c
NAME1 = powielacz
NAME2 = wzajemne_wykluczanie
NAME3 = obsluga_semaforow

PLIK_NUMER = numer.txt
ILE_PROCESOW = 4
ILE_SEKCJI_KRYT = 3
SEM_NAME = sem1

# posrednie pliki skompilowane
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o

# pliki wykonywalne
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x

# opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -pthread
LFLAGS = -Wall -std=c99 -pedantic -pthread

# linkowane biblioteki
LDLIBS = -lm

# kompilator i linker
CO = gcc
LD = $(CO)

# program archiwizer do tworzenia bibliotek statycznych
AR = ar

# opcje archiwizera tworzenie/uaktualnianie biblioteki wraz z indeksem plikow i wypisywanie komunikatow
ARFLAGS = rsv

LIB_OBJS = $(OBJS3)

LIB_NAME = MojeFunkcje
# Katalog dla bibliotek
LIB_DIR = ./lib
# Biblioteka statyczna (static library)
LIB_STAT = lib$(LIB_NAME).a

$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

##############
# reguly zaleznosci
##############
$(OBJS1) $(OBJS2): $(LIB_STAT)
%.o: %.c
	$(CO) $(CFLAGS) -c $<

$(EXEC1): $(OBJS1) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
$(EXEC2): $(OBJS2) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

.PHONY: all
all: $(EXEC1) $(EXEC2)

.PHONY: run1
run1: $(EXEC1) $(EXEC2)
	./$(EXEC1) $(EXEC2) $(ILE_PROCESOW) $(ILE_SEKCJI_KRYT) $(PLIK_NUMER) $(SEM_NAME)

.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
