lzw: main.o lzw.o
	g++ main.o lzw.o -lm -o lzw
main.o: main.cpp
	g++ -c main.cpp
lzw.o: lzw.cpp
	g++ -c lzw.cpp
clean:
	rm *.o *.lzw lzw
perms:
	chmod a+rwx lzw

