###################################
#    Makefile for SmileDB		  #
###################################

# The general compiling commands  #

CP = cp
CC = gcc
SUDO = sudo
CCFLAGES = -c -w

TARGET = SmileDB

TGT = tgt/*

OBJS = tgt/smile.o tgt/utils.o tgt/storage.o tgt/header.o tgt/page.o tgt/record.o tgt/arrayList.o tgt/hashMap.o tgt/stringType.o tgt/integerType.o tgt/shortType.o tgt/longType.o tgt/byteType.o tgt/floatType.o tgt/doubleType.o tgt/index.o tgt/table.o tgt/byteBuffer.o tgt/definition.o tgt/columnParse.o

.PHONY : build clean

build : clean $(TARGET)

clean : 
	rm -f $(TARGET) $(TGT)

tgt/arrayList.o : src/data/arrayList.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/hashMap.o : src/data/hashMap.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/stringType.o : src/data/stringType.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/integerType.o : src/data/integerType.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/shortType.o : src/data/shortType.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/byteType.o : src/data/byteType.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/longType.o : src/data/longType.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/floatType.o : src/data/floatType.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/doubleType.o : src/data/doubleType.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/utils.o : src/utils/utils.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/byteBuffer.o : src/page/byteBuffer.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/storage.o : src/storage/storage.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/header.o : src/page/header.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/definition.o : src/table/definition.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/table.o : src/table/table.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/columnParse.o : src/page/columnParse.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/page.o : src/page/page.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/record.o : src/page/record.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/index.o : src/storage/index.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/smile.o : src/smile.c
	$(CC) $(CCFLAGES) $< -o $@

SmileDB :tgt/smile.o tgt/utils.o tgt/storage.o tgt/header.o tgt/page.o tgt/record.o tgt/arrayList.o tgt/hashMap.o tgt/stringType.o tgt/integerType.o tgt/shortType.o tgt/longType.o tgt/byteType.o tgt/floatType.o tgt/doubleType.o tgt/index.o tgt/table.o tgt/byteBuffer.o tgt/definition.o tgt/columnParse.o
	$(CC) $(OBJS) -o $@ -lz -lm