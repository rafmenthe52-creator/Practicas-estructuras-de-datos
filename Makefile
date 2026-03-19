########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
STACKFLAGS= -g -Wall -pedantic -lstack -L.
EJS = p1_e1 p1_e2 p1_e3 p2_e1 p2_e2a p2_e2b p2_e3 p2_e1S p2_e2aS p2_e2bS p2_e3S p3_e1
#EJS = p3_e1
########################################################
OBJECTSP1E1 = p1_e1.o music.o
OBJECTSP1E2 = p1_e2.o radio.o music.o
OBJECTSP1E3 = p1_e3.o radio.o music.o
OBJECTSP2E1 = p2_e1.o radio.o music.o stack.o
OBJECTSP2E1S = p2_e1.o radio.o music.o 
OBJECTSP2E2a = p2_e2a.o radio.o music.o stack.o
OBJECTSP2E2aS = p2_e2a.o radio.o music.o 
OBJECTSP2E2b = p2_e2b.o radio.o music.o stack.o
OBJECTSP2E2bS = p2_e2b.o radio.o music.o 
OBJECTSP2E3 = p2_e3.o radio.o music.o stack.o
OBJECTSP2E3S = p2_e3.o radio.o music.o 
OBJECTSP3E1 = p3_e1.o radio.o music.o queue.o stack.o
########################################################

all: $(EJS)

p1_e1: $(OBJECTSP1E1)
	$(CC) $(CFLAGS) -o p1_e1 $(OBJECTSP1E1) -lstack -L.

p1_e2: $(OBJECTSP1E2)
	$(CC) $(CFLAGS) -o p1_e2 $(OBJECTSP1E2) -lstack -L.

p1_e3: $(OBJECTSP1E3)
	$(CC) $(CFLAGS) -o p1_e3 $(OBJECTSP1E3) -lstack -L.

p2_e1: $(OBJECTSP2E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2E1)

p2_e1S: $(OBJECTSP2E1S)
	$(CC) $(CFLAGS) -o p2_e1S $(OBJECTSP2E1S) -lstack -L.

p2_e2a: $(OBJECTSP2E2a)
	$(CC) $(CFLAGS) -o p2_e2a $(OBJECTSP2E2a)

p2_e2aS: $(OBJECTSP2E2aS)
	$(CC) $(CFLAGS) -o p2_e2aS $(OBJECTSP2E2aS) -lstack -L.

p2_e2b: $(OBJECTSP2E2b)
	$(CC) $(CFLAGS) -o p2_e2b $(OBJECTSP2E2b)

p2_e2bS: $(OBJECTSP2E2bS)
	$(CC) $(CFLAGS) -o p2_e2bS $(OBJECTSP2E2bS) -lstack -L.

p2_e3: $(OBJECTSP2E3)
	$(CC) $(CFLAGS) -o p2_e3 $(OBJECTSP2E3)

p2_e3S: $(OBJECTSP2E3S)
	$(CC) $(CFLAGS) -o p2_e3S $(OBJECTSP2E3S) -lstack -L.

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

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

p2_e2b.o: p2_e2b.c types.h music.h radio.h stack.h file_utils.h
	$(CC) $(CFLAGS) -c p2_e2b.c 

p2_e3.o: p2_e3.c types.h music.h radio.h stack.h 
	$(CC) $(CFLAGS) -c p2_e3.c
	
p3_e1.o: p3_e1.c music.h types.h radio.h stack.h file_utils.h queue.h
	$(CC) $(CFLAGS) -c p3_e1.c

music.o: music.c music.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

stack.o: stack.c stack.h types.h file_utils.h music.h radio.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) -c queue.c

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
	@echo ">>>>>>Running p2_e1"
	./p2_e1 g1.txt
	@echo ">>>>>>Running p2_e2a"
	./p2_e2a
	@echo ">>>>>>Running p2_e2b"
	./p2_e2b
	@echo ">>>>>>Running p2_e3"
	./p2_e3
	@echo ">>>>>>Running p2_e1S"
	./p2_e1S
	@echo ">>>>>>Running p2_e2aS"
	./p2_e2aS
	@echo ">>>>>>Running p2_e2bS"
	./p2_e2bS
	@echo ">>>>>>Running p2_e3S"
	./p2_e3S
	@echo ">>>>>>Running p3_e1"
	./p3_e1 playlist1.txt

runv:
	@echo ">>>>>>Running p1_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p1_e1
	@echo ">>>>>>Running p1_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p1_e2 
	@echo ">>>>>>Running p1_e3 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p1_e3 radio1.txt
	@echo ">>>>>>Running p2_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e1 playlist1.txt
	@echo ">>>>>>Running p2_e2a with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e2a playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e2b with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e2b	playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e3 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e3 radio1.txt 1 9
	@echo ">>>>>>Running p2_e1S with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e1S playlist1.txt
	@echo ">>>>>>Running p2_e2aS with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e2aS playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e2bS with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e2bS playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e3S with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e3S radio1.txt 1 9
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e1 playlist1.txt
