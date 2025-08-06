
# Compiler
CC=g++
# flags
CFLAGS=-c -Wall


# Default target to create an executable
all: main.o interface.o
	$(CC) $(CFLAGS) main.cpp -o main.o
	$(CC) $(CFLAGS) interface.cpp -o interface.o
	$(CC)  main.o interface.o -o my_inf_arith

# Rule to create a static library
libmy_inf_arith : main.o interface.o
	ar rcs libmy_inf_arith.a main.o interface.o

# Rule to compile main.cpp into main.o 
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

# Rule to compile interface.cpp into interface.o
interface.o: interface.cpp
	$(CC) $(CFLAGS) interface.cpp -o interface.o

# Cleaning up
clean:
	rm -f *.o my_inf_arith libmy_inf_arith.a

