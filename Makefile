# make variables let us avoid pasting these options in multiple places
CC = gcc 
# CFLAGS = -std=c99 -Wall -Wextra -pedantic -O         # for final build
CFLAGS = -std=c99 -Wall -Wextra -pedantic -O0 -g   # for debugging

bin: hw4

test: test_functions
	@echo "Running tests..."
	./test_functions
	@echo "All Tests Passed."

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c
# (short for) gcc -std=c99 -Wall -Wextra -pedantic -O -c wordsearch.c

test_functions.o: test_functions.c functions.h
	$(CC) $(CFLAGS) -c test_functions.c

hw4.o: hw4.c functions.h
	$(CC) $(CFLAGS) -pedantic -O -c hw4.c

test_functions: test_functions.o functions.o
	$(CC) $(CFLAGS) -O -o test_functions test_functions.o functions.o

hw4: hw4.o functions.o
	$(CC) $(CFLAGS) -O -o hw4 hw4.o functions.o

clean:
	rm -f *.o test_functions hw4
