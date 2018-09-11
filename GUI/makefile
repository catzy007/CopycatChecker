# change application name here (executable output name)
TARGET=copycatchecker

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS1=main.o
OBJS2=checkcopy.o

all: $(OBJS1) $(OBJS2)
	$(LD) -o $(TARGET) $(OBJS1) $(OBJS2) $(LDFLAGS)
    
main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o
	
checkcopy.o: src/checkcopy.c
	$(CC) -c $(CCFLAGS) src/checkcopy.c $(GTKLIB) -o checkcopy.o
    
clean:
	rm -f *.o $(TARGET)
