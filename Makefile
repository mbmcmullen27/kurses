all: kurses test
kurses: menu.o main.o
	clang menu.o main.o -o kurses -lncurses
menu.o: menu.c menu.h
	clang -c menu.c
main.o: main.c menu.h
	clang -c main.c
test: testmenu.o menu.o
	clang testmenu.o menu.o -o test -lncurses
testmenu.o: testmenu.c menu.h
	clang -c testmenu.c
clean:
	rm *.o kurses test