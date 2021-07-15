# GCC COMPILE
CC = gcc
COMP_FLAGS = -g -Wall -Werror -c
C_FILES := $(wildcard *.c)

# LINKER 
C_OBJ := $(patsubst %.c, %.o, $(C_FILES))
LINK_FLAGS = -o
EXEC_NAME = chess

$(EXEC_NAME): $(C_FILES)
	$(CC) $(COMP_FLAGS) $(C_FILES)
	$(CC) $(C_OBJ) $(LINK_FLAGS) $(EXEC_NAME)

clean:
	rm -rf $(C_OBJ) $(EXEC_NAME)
