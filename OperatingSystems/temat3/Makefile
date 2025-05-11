.SUFFIXES: .c .cpp .o .x .h

# zmienne inne
DIR = $(notdir $(CURDIR))
LIBDIR = ./lib

# nazwy plikow .c
NAME1 = cw3a
NAME2 = funkcjaWypiszID
NAME3 = cw3b
NAME4 = cw3c
NAME5 = cw3cProgramLiderGrupy

SIGNAL_NUM = 3
REACT1 = d
REACT2 = i
REACT3 = c

# posrednie pliki skompilowane
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o

# pliki wykonywalne
EXEC1 = $(NAME1).x
EXEC2 = $(NAME3).x
EXEC3 = $(NAME4).x
EXEC4 = $(NAME5).x

# opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic

# linkowane biblioteki
LDLIBS = -lm

# kompilator i linker
CO = gcc
LD = $(CO)

# program archiwizer do tworzenia bibliotek statycznych
AR = ar

# opcje archiwizera tworzenie/uaktualnianie biblioteki wraz z indeksem plikow i wypisywanie komunikatow
ARFLAGS = rsv

LIB_OBJS = $(OBJS2)

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
$(OBJS1) $(OBJS3) $(OBJS4) $(OBJS5): $(LIB_STAT)
%.o: %.c
	$(CO) $(CFLAGS) -c $<

$(EXEC1): $(OBJS1) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
$(EXEC2): $(OBJS3) $(OBJS1) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
$(EXEC3): $(OBJS4) $(OBJS5) $(OBJS1) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
$(EXEC4): $(OBJS5) $(OBJS4) $(OBJS1) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

.PHONY: run1Def, run1Ign, run1Custom, run2Def, run2Ign, run2Custom, run3Def, run3Ign, run3Custom
run1Def: $(EXEC1)
	./$(EXEC1) $(SIGNAL_NUM) $(REACT1)

run1Ign: $(EXEC1)
	./$(EXEC1) $(SIGNAL_NUM) $(REACT2)

run1Custom: $(EXEC1)
	./$(EXEC1) $(SIGNAL_NUM) $(REACT3)

run2Def: $(EXEC2) $(EXEC1)
	./$(EXEC2) $(EXEC1) $(SIGNAL_NUM) $(REACT1)

run2Ign: $(EXEC2) $(EXEC1)
	./$(EXEC2) $(EXEC1) $(SIGNAL_NUM) $(REACT2)

run2Custom: $(EXEC2) $(EXEC1)
	./$(EXEC2) $(EXEC1) $(SIGNAL_NUM) $(REACT3)

run3Def: $(EXEC3) $(EXEC4) $(EXEC1)
	./$(EXEC3) $(EXEC4) $(EXEC1) $(SIGNAL_NUM) $(REACT1)

run3Ign: $(EXEC3) $(EXEC4) $(EXEC1)
	./$(EXEC3) $(EXEC4) $(EXEC1) $(SIGNAL_NUM) $(REACT2)

run3Custom: $(EXEC3) $(EXEC4) $(EXEC1)
	./$(EXEC3) $(EXEC4) $(EXEC1) $(SIGNAL_NUM) $(REACT3)

.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
