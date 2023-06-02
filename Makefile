CLIENT_SRC=client/client.c client/main_client.c
CLIENT_APP=app_client
CFLAGS=-Wall
LDFLAGS=-lm
GCC=gcc

default:
	@echo "Choose target!";

all:
	${GCC} ${CFLAGS} ${CLIENT_SRC} -o ${CLIENT_APP} ${LDFLAGS}

clean:
	@if test -f "${CLIENT}"; then \
		rm -f ${CLIENT};\
	fi
	@if test -f "${SERVER}"; then \
		rm -f ${SERVER};\
	fi
	-rm -f *.o
