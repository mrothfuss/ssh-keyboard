CC = cc
CFLAGS = -Wall -g

SRC = main.c ascii.c
OBJ = ${SRC:.c=.o}

all: sshkeyboard

options:
	@echo build options:
	@echo "CFLAGS	= ${CFLAGS}"
	@echo "CC	= ${CC}"


sshkeyboard: ${OBJ}
	@echo ${CC} -o $@ ${OBJ}
	@${CC} -o $@ ${OBJ}

clean:
	@echo cleaning
	@rm -f sshkeyboard ${OBJ}

.PHONY: all options clean
