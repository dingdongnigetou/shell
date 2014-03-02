#                         (C) 2014 HuangJinDong                        # 
########################################################################

CC=gcc
CFLAGS += -Wall
CFLAGS += -I$(INCLUDE) 
CFLAGS += -std=gnu99
CFLAGS += -lreadline # for readline
CFLAGS += -O3        # release

SRC=./src
OBJ=./obj
INCLUDE=./include


install:$(OBJ)/main.o $(OBJ)/scan.o $(OBJ)/build_in.o \
	$(OBJ)/readprocess.o $(OBJ)/exec.o $(OBJ)/errorprocess.o \
	$(OBJ)/parse.o
	$(CC) $(CFLAGS) $^ -o ddsh

$(OBJ)/main.o:$(SRC)/main.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ)/scan.o:$(SRC)/scan.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ)/build_in.o:$(SRC)/build_in.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/readprocess.o:$(SRC)/readprocess.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/exec.o:$(SRC)/exec.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/errorprocess.o:$(SRC)/errorprocess.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/parse.o:$(SRC)/parse.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)/* 
	rm -f ddsh 

