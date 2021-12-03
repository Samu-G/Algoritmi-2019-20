CC=gcc
CFLAGS=-Wall -I include -I Resources/C/Unity/

all: bin/sorting_record_app bin/Utest

clean:
	$(RM) -rf bin/sorting_record_app
	$(RM) -rf bin/Utest
	$(RM) -rf build/*

build/sorting_lib.o: src/sorting_lib.c include/sorting_lib.h 
	$(CC) $(CFLAGS) -c src/sorting_lib.c -o build/sorting_lib.o

build/record_lib.o: src/record_lib.c include/record_lib.h 
	$(CC) $(CFLAGS) -c src/record_lib.c -o build/record_lib.o

bin/sorting_record_app: include/sorting_lib.h build/sorting_lib.o include/record_lib.h build/record_lib.o
	$(CC) $(CFLAGS) application/sorting_record_app.c build/sorting_lib.o build/record_lib.o -o bin/sorting_record_app

bin/Utest: include/sorting_lib.h build/sorting_lib.o include/record_lib.h build/record_lib.o
	$(CC) $(CFLAGS) test/Utest.c build/sorting_lib.o build/record_lib.o Resources/C/Unity/unity.c -o bin/Utest