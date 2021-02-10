all: array.o hash_AVL.o driver.so

driver.so: driver.c driver.h array.o hash_AVL.o
	gcc -shared -o driver.so array.o hash_AVL.o -fPIC driver.c

array.o: array.c array.h
	gcc -o array.o -c array.c

hash_AVL.o: hash_AVL.c hash_AVL.h
	gcc -o hash_AVL.o -c hash_AVL.c