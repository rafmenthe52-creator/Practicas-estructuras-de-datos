########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p2_e2a
#EJS = p1_e1 p1_e2 p1_e3 p2_e1
########################################################
OBJECTSP1E1 = p1_e1.o music.o
OBJECTSP1E2 = p1_e2.o radio.o music.o
OBJECTSP1E3 = p1_e3.o radio.o music.o
OBJECTSP2E1 = p2_e1.o radio.o music.o
OBJECTSP2E2a = p2_e2a.o radio.o music.o
########################################################

all: $(EJS)

p1_e1: $(OBJECTSP1E1)
	$(CC) $(CFLAGS) -o p1_e1 $(OBJECTSP1E1)

p1_e2: $(OBJECTSP1E2)
	$(CC) $(CFLAGS) -o p1_e2 $(OBJECTSP1E2)

p1_e3: $(OBJECTSP1E3)
	$(CC) $(CFLAGS) -o p1_e3 $(OBJECTSP1E3)

p2_e1: $(OBJECTSP2E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2E1) -lstack -L.

p1_e1.o: p1_e1.c music.h
	$(CC) $(CFLAGS) -c p1_e1.c

p1_e2.o: p1_e2.c music.h radio.h
	$(CC) $(CFLAGS) -c p1_e2.c
	
p1_e3.o: p1_e3.c music.h radio.h
	$(CC) $(CFLAGS) -c p1_e3.c

p2_e1.o: p2_e1.c types.h music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p2_e1.c 

p2_e2a.o: p2_e2a.c types.h music.h radio.h stack.h file_utils.h
	$(CC) $(CFLAGS) -c p2_e2a.c 

music.o: music.c music.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p1_e1"
	./p1_e1
	@echo ">>>>>>Running p1_e2"
	./p1_e2 
	@echo ">>>>>>Running p1_e3"
	./p1_e3 g1.txt
	@echo ">>>>>>Running p1_e3"
	./p2_e1 g1.txt

runv:
	@echo ">>>>>>Running p1_e1 with valgrind"
	valgrind --leak-check=full ./p1_e1
	@echo ">>>>>>Running p1_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p1_e2 
	@echo ">>>>>>Running p1_e3 with valgrind
	valgrind --leak-check=full ./p1_e3 radio1.txt
	@echo ">>>>>>Running p2_e1 with valgrind
	valgrind --leak-check=full ./p2_e1 playlist1.txt
