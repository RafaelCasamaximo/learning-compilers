# Name of the project
PROJ_NAME=pascal

# .c files
C_SOURCE=$(wildcard *.c)

# .h files
H_SOURCE=$(wildcard *.h)

# Compiler
CC=gcc

FLEX=flex

LEXICO = lexico.l

LEX_C = lex.yy.c

TMPVAR := $(C_SOURCE)

C_SOURCE = $(filter-out $(LEX_C), $(TMPVAR))

# Object files
OBJ=$(C_SOURCE:.c=.o)

# Flags for compiler
CC_FLAGS=

#
# Compilation and linking
#
all: $(PROJ_NAME)



$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CC_FLAGS) 

%.o: %.c %.h
	$(CC) -o $@ $< -c $(CC_FLAGS) 

main.o: main.c $(H_4SOURCE) $(LEX_C)
	$(CC) -o $@ $< -c $(CC_FLAGS) 

$(LEX_C): $(LEXICO) tokens.h
	$(FLEX) $(LEXICO)

clean:
	rm -rf *.o $(PROJ_NAME) $(LEX_C) *~
