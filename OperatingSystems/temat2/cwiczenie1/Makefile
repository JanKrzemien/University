.SUFFIXES: .c .cpp .o .x .h

# zmienne inne
DIR = $(notdir $(CURDIR))
LIBDIR = ./lib

# nazwy plikow .c
NAME1 = cw1a
NAME2 = cw1b
NAME3 = cw1c
NAME4 = cw1d
NAME5 = cw1e
NAME6 = funkcjaWypiszID

# posrednie pliki skompilowane
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o
OBJS6 = $(NAME6).o

# pliki wykonywalne
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x

# opcje kompilatora i linkera
CFLAGS = -Wall -std=gnu99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

# linkowane biblioteki
LDLIBS = -lm

# kompilator i linker
CO = gcc
LD = $(CO)

# program archiwizer do tworzenia bibliotek statycznych
AR = ar

# opcje archiwizera tworzenie/uaktualnianie biblioteki wraz z indeksem plikow i wypisywanie komunikatow
ARFLAGS = rsv

LIB_OBJS = $(OBJS6)

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
$(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5): $(LIB_STAT)
%.o: %.c
	$(CO) $(CFLAGS) -c $<
%.x: %.o $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

.PHONY: run1 run2 run3 run4 run5
run1: $(EXEC1)
	./$(EXEC1)
run2: $(EXEC2)
	./$(EXEC2)
run3: $(EXEC3)
	./$(EXEC3)
run4: $(EXEC4)
	./$(EXEC4)
run5: $(EXEC5)
	./$(EXEC5)

.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
