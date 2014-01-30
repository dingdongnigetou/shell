#                         2014 (C) HuangJinDong                        # 
########################################################################

CC=gcc
CFLAGS += -wall

SRC=./src
OBJ=./obj
INCLUDE=./include

install:$(OBJ)/main.o
	$(CC) $(CFLAGS) $^ -o ddsh

$(OBJ)/main.o:$(SRC)/mian.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ)/*
