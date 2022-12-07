PROJECT =  trove
HEADERS =  $(PROJECT).h
OBJ     =  trove.o compression.o files.o hashtable.o list.o debug.o globals.o

C11     =  cc -std=c11
CFLAGS  =  -Wall -Werror

$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ)
trove.o : trove.c $(HEADERS)
	$(C11) $(CFLAGS) -c trove.c
compression.o : compression.c trove.h
	$(C11) $(CFLAGS) -c compression.c
files.o : files.c $(HEADERS)
	$(C11) $(CFLAGS) -c files.c
hashtable.o : hashtable.c $(HEADERS)
	$(C11) $(CFLAGS) -c hashtable.c
list.o : list.c $(HEADERS)
	$(C11) $(CFLAGS) -c list.c
debug.o : debug.c $(HEADERS)
	$(C11) $(CFLAGS) -c debug.c
globals.o : globals.c $(HEADERS)
	$(C11) $(CFLAGS) -c globals.c