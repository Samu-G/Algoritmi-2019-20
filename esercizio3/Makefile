CC=gcc -O3
FLAGS=-Wall -I include -I Resources/C/Unity/

all: build/hash_map.o bin/test bin/app_es3

clear:
	$(RM) -rf bin/app_es3
	$(RM) -rf bin/test
	$(RM) -rf build/hash_map.o

build/hash_map.o: src/hash_map.c include/hash_map.h
	$(CC) $(FLAGS) -c src/hash_map.c -o build/hash_map.o

bin/test: include/hash_map.h build/hash_map.o
	$(CC) $(FLAGS) test/utest.c build/hash_map.o Resources/C/Unity/unity.c -o bin/test

bin/app_es3: include/hash_map.h build/hash_map.o
	$(CC) $(FLAGS) application/app_es3.c build/hash_map.o -o bin/app_es3