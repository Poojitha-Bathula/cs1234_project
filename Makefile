# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -g

# Library name
LIB = libtransit.a

# Object files for library
LIB_OBJ = grid.o route.o graph.o

# Main object
MAIN_OBJ = main.o

# Final executable
TARGET = transit

# Default target
all: $(TARGET)

# Build executable using library
$(TARGET): $(MAIN_OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJ) -L. -ltransit

# Create static library
$(LIB): $(LIB_OBJ)
	ar rcs $(LIB) $(LIB_OBJ)

# Compile main
main.o: main.c grid.h route.h graph.h
	$(CC) $(CFLAGS) -c main.c

# Compile library components
grid.o: grid.c grid.h
	$(CC) $(CFLAGS) -c grid.c

route.o: route.c route.h grid.h
	$(CC) $(CFLAGS) -c route.c

graph.o: graph.c graph.h grid.h
	$(CC) $(CFLAGS) -c graph.c

# Clean
clean:
	rm -f *.o $(TARGET) $(LIB)

# Run
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run