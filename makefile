lzw: main.o lzw.o rbtree.o
	g++ main.o lzw.o rbtree.o -lm -o lzw
main.o: main.cpp
	g++ -c main.cpp
lzw.o: lzw.cpp
	g++ -c lzw.cpp
rbtree.o: rbtree.cpp
	g++ -c rbtree.cpp
clean:
	rm *.o lzw
perms:
	chmod a+rwx lzw

