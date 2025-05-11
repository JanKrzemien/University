.SUFFIXES: .c .cpp .o .x .h

# zmienne inne
DIR = $(notdir $(CURDIR))
LIBDIR = ./lib

# nazwy plikow .c
NAME1 = main
NAME2 = producent
NAME3 = konsument

DANE = dane.txt
WYNIK = wynik.txt
MEM_NAME = /mem13
PROD_SEM_NAME = psem21
KONS_SEM_NAME = ksem11

NAME4 = obsluga_semaforow
NAME5 = obsluga_pamieci

# pliki naglowkowe
HEADERS = $(NAME4).h $(NAME5).h

# posrednie pliki skompilowane
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o

OBJS_STATIC1 = $(NAME4)_static.o
OBJS_STATIC2 = $(NAME5)_static.o

OBJS_SHARED1 = $(NAME4)_shared.o
OBJS_SHARED2 = $(NAME5)_shared.o


# pliki wykonywalne
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x

# opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic -pthread

# linkowane biblioteki
LDLIBS = -lrt

# kompilator i linker
CO = gcc
LD = $(CO)

# program archiwizer do tworzenia bibliotek statycznych
AR = ar

# opcje archiwizera tworzenie/uaktualnianie biblioteki wraz z indeksem plikow i wypisywanie komunikatow
ARFLAGS = rsv

$(OBJS_STATIC1): $(NAME4).c $(HEADERS)
	$(CO) $(CFLAGS) -c $< -o $@
$(OBJS_STATIC2): $(NAME5).c $(HEADERS)
	$(CO) $(CFLAGS) -c $< -o $@

LIB_NAME = _stat
# Katalog dla bibliotek
LIB_DIR = ./lib
# Biblioteka statyczna (static library)
LIB_STAT = lib$(LIB_NAME).a

make_static: $(OBJS_STATIC1) $(OBJS_STATIC2)
	$(AR) $(ARFLAGS) $(LIB_STAT) $(OBJS_STATIC1) $(OBJS_STATIC2)
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)


$(OBJS_SHARED1): $(NAME4).c $(HEADERS)
	$(CO) $(CFLAGS) -fPIC -c $< -o $@
$(OBJS_SHARED2): $(NAME5).c $(HEADERS)
	$(CO) $(CFLAGS) -c -fPIC $< -o $@

LIB_NAME2 = _shared
LIB_SHAR = lib$(LIB_NAME2).so
# Tworzenie biblioteki dzielonej (shared library)
make_shared: $(OBJS_SHARED1) $(OBJS_SHARED2)
	$(LD) $(LFLAGS) -shared -o $(LIB_SHAR) $(OBJS_SHARED1) $(OBJS_SHARED2)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)


##############
# reguly zaleznosci
##############
$(OBJS1): $(NAME1).c
	$(CO) $(CFLAGS) -c $< -o $@
$(OBJS2): $(NAME2).c
	$(CO) $(CFLAGS) -c $< -o $@
$(OBJS3): $(NAME3).c
	$(CO) $(CFLAGS) -c $< -o $@

make_exec_static: make_static $(OBJS1) $(OBJS2) $(OBJS3)
	$(LD) -o $(EXEC1) $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
	$(LD) -o $(EXEC2) $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
	$(LD) -o $(EXEC3) $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

make_exec_shared_1: make_shared $(OBJS1) $(OBJS2) $(OBJS3)
	$(LD) -o $(EXEC1) $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME2) $(LDLIBS) -Wl,-R $(LIB_DIR)
	$(LD) -o $(EXEC2) $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME2) $(LDLIBS) -Wl,-R $(LIB_DIR)
	$(LD) -o $(EXEC3) $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME2) $(LDLIBS) -Wl,-R $(LIB_DIR)

make_exec_shared_2: make_shared $(OBJS1) $(OBJS2) $(OBJS3)
	$(LD) -o $(EXEC1) $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME2) $(LDLIBS)
	$(LD) -o $(EXEC2) $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME2) $(LDLIBS)
	$(LD) -o $(EXEC3) $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME2) $(LDLIBS)

.PHONY: run1s, run1d1, run1d2
run1s: make_exec_static
	./$(EXEC1) $(EXEC2) $(EXEC3) $(DANE) $(WYNIK) $(MEM_NAME) $(PROD_SEM_NAME) $(KONS_SEM_NAME)
	diff -s $(DANE) $(WYNIK)

run1d1: make_exec_shared_1
	./$(EXEC1) $(EXEC2) $(EXEC3) $(DANE) $(WYNIK) $(MEM_NAME) $(PROD_SEM_NAME) $(KONS_SEM_NAME)
	diff -s $(DANE) $(WYNIK)

run1d2: make_exec_shared_2
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC1) $(EXEC2) $(EXEC3) $(DANE) $(WYNIK) $(MEM_NAME) $(PROD_SEM_NAME) $(KONS_SEM_NAME)
	diff -s $(DANE) $(WYNIK)

.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
