SRC_DIR = src
BUILD_DIR = build/debug
CC = g++-13
SRC_FILES = ${wildcard ${SRC_DIR}/*.cpp}
OBJ_NAME = play
INCLUDE_PATHS = -Iinclude -I/include/SDL2 -I/include/SDL2_image -I/src
LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.28.2/lib -Llib/SDL2_image
COMPILER_FLAGS = -std=c++20 -Wall -O0 -g
LINKER_FLAG = -lsdl2 -lSDL2_image
PGS = pkg-config --cflags --libs
PKG_LIST = sdl2 sdl2_image

all:
	${CC} ${COMPILER_FLAGS} `${PGS} ${PKG_LIST}` ${SRC_FILES} -o ${BUILD_DIR}/${OBJ_NAME}