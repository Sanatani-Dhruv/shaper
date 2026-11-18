CC=cc

BUILD_DIR=build
BIN=${BUILD_DIR}/game

SRC=$(shell find -type f -path "./src/*.c")
HEADER=$(shell find -type f -path "./src/include/*.h")

ESC=\e[

RED=${ESC}31m
GREEN=${ESC}32m
B=${ESC}1m
RESET=${ESC}0m

CFLAGS=-O2 -L/usr/lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LDFLAGS=

DEBUG=-DDEBUG

all: ${BIN} run

${BIN}: tags ${BUILD_DIR} ${SRC} ${HEADER}
	${CC} ${DEBUG} ${SRC} ${CFLAGS} ${EXTRA_CFLAGS} -o ${BIN}
	@echo -e "${GREEN}${B}Compiled and generated Binary at ${BIN}${RESET}"

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

run:
	./${BIN}

clean:
	rm -rf *.o *.out build/* *.plist compile_commands.json tags *.cache
	@echo -e "${RED}${B}Removed All Build and temporary files${RESET}"

tags: ${SRC} ${HEADER}
	ctags ${SRC} ${HEADER}
