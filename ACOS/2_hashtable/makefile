main: main.o libhashtable.so
	gcc -o main main.o -lhashtable -llist -L.

main.o: main.c hashtable.h
	gcc -std=c99 -c -g main.c

libhashtable.so: hashtable.o liblist.so
	gcc -shared -Wl,-soname,libhashtable.so hashtable.o -o libhashtable.so -llist -L.

hashtable.o: hashtable.c hashtable.h list.h
	gcc -std=c99 -c -g hashtable.c -fPIC

liblist.so: list.o
	gcc -shared -Wl,-soname,liblist.so list.o -o liblist.so

list.o: list.c list.h
	gcc -std=c99 -c -g list.c -fPIC

