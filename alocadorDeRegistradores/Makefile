# Name of the project
PROJ_NAME=regalloc

# .c files
C_SOURCE=$(wildcard *.c)

# .h files
H_SOURCE=$(wildcard *.h)

CC=gcc

CC_FLAGS = -g		\
		 -std=c99    

OBJ=$(C_SOURCE:.c=.o)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CC_FLAGS) 

%.o: %.c %.h
	$(CC) -o $@ $< -c $(CC_FLAGS) 

main.o: main.c
	$(CC) -o $@ $< -c $(CC_FLAGS) 

clean:
	rm -rf *.o $(PROJ_NAME) $(OBJ) *~