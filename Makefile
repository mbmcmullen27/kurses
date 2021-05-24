all: kurses test
kurses: menu.o main.o
	clang menu.o main.o -o kurses -lncurses
menu.o: menu.c menu.h
	clang -c menu.c
main.o: main.c menu.h
	clang -c main.c
tests: menutest cursortest
menutest: testmenu.o menu.o
	clang testmenu.o menu.o -o test -lncurses
testmenu.o: testmenu.c menu.h
	clang -c testmenu.c
cursortest: testcursor.o menu.o
	clang testcursor.o menu.o -o ctest -lncurses
testcursor.o: testcursor.c menu.h
	clang -c testcursor.c
clean:
	rm *.o kurses test