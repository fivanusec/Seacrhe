CC=gcc
CFLAGS=-I.
OBJ = src/Search.c
NAME = Searche

all: build

%.o: %.c
	$(CC) -c $< -o $@

build:
	@echo "** Building $(NAME)..."
	$(CC) $(OBJ) -o $(NAME)

install:
	echo '** Installing...'
	sudo cp $(NAME) /usr/bin/
