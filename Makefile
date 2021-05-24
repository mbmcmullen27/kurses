all: kurses tests
kurses: src/menu.o src/main.o
	clang src/menu.o src/main.o -o kurses -lncurses
src/menu.o: src/menu.c src/menu.h
	clang -c src/menu.c -o src/menu.o
src/main.o: src/main.c src/menu.h
	clang -c src/main.c -o src/main.o
tests: content cursor
content: test/test-contents.o src/menu.o
	clang test/contents.o src/menu.o -o test/content.test -lncurses
test/contents.o: test/test-contents.c src/menu.h
	clang -c test/test-contents.c -o test/contents.o
cursor: test/cursor.o src/menu.o
	clang test/cursor.o src/menu.o -o test/cursor.test -lncurses
test/cursor.o: test/test-cursor.c src/menu.h
	clang -c test/test-cursor.c -o test/cursor.o
clean:
	rm *.o kurses test/*.o test/*.test