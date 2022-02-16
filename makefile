###################################
#    Makefile for SmileDB		  #
###################################

# The general compiling commands  #

CP = cp
CC = gcc
SUDO = sudo
CCFLAGES = -c

TARGET = SmileDB

TGT = tgt/*

OBJS = tgt/smile.o tgt/utils.o tgt/storage.o tgt/header.o

.PHONY : build clean

build : clean $(TARGET)

tgt/utils.o : src/utils/utils.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/storage.o : src/storage/storage.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/header.o : src/page/header.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/smile.o : src/smile.c
	$(CC) $(CCFLAGES) $< -o $@

SmileDB :tgt/smile.o tgt/utils.o tgt/storage.o tgt/header.o
	$(CC) $(OBJS) -o $@ -lz -lm