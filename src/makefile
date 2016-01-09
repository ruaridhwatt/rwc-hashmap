OUT=test_rwc_hashmap
COMPILER=gcc
FLAGS=-g -Wall -pedantic

BIN_DIR=../bin

all: $(OUT)

$(OUT): main.o hashmap.o llist.o
	$(COMPILER) $(FLAGS) -o $(BIN_DIR)/$(OUT) $(BIN_DIR)/llist.o $(BIN_DIR)/hashmap.o $(BIN_DIR)/main.o

main.o: main.c hashmap.h
	$(COMPILER) $(FLAGS) -o $(BIN_DIR)/main.o main.c -c

hashmap.o: hashmap.c hashmap.h llist.h
	$(COMPILER) $(FLAGS) -o $(BIN_DIR)/hashmap.o hashmap.c -c

llist.o: llist.c llist.h
	$(COMPILER) $(FLAGS) -o $(BIN_DIR)/llist.o llist.c -c