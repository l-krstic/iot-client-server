CLIENT_SRC=client/client.c client/main_client.c
CLIENT_APP=app_client
SERVER_SRC=server/server.c server/main_server.c
SERVER_APP=app_server

CFLAGS=-Wall
LDFLAGS=-lm -pthread
GCC=gcc

default:
	@echo "Choose target!";

all:
	${GCC} ${CFLAGS} ${CLIENT_SRC} -o ${CLIENT_APP} ${LDFLAGS}
	${GCC} ${CFLAGS} ${SERVER_SRC} -o ${SERVER_APP} ${LDFLAGS}

clean:
	@if test -f "${CLIENT_APP}"; then \
		rm -f ${CLIENT_APP};\
	fi
	@if test -f "${SERVER_APP}"; then \
		rm -f ${SERVER_APP};\
	fi
	-rm -f *.o
