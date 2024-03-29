# kurses

```bash
# compile with clang and run
clang -c menu.c
clang -c main.c
clang main.o menu.o -o kurses -lncurses
./kurses

# or build using provide Makefile
make kurses
./kurses
```

## Pointers & Structs & Arrays & Arrays of Structs & Pointers 

Some funny business with pointers and structs, our Menu struct holds an array of Item pointers. When we initalize this list, if we aren't careful we don't make a new item and we recycle a single pointer. 
My initial thought was because :

- you need to initialize the list pointers
- __then__ you initialize the structs

But this line isn't allocating space for pointers, we use sizeof(Item), not sizeof(*Item). Needs more research. We either got this right, or we're requesting twice as much space as we need.

> menu.items = malloc(sizeof(Item) * size); 


```C
int main(){

    int size = sizeof items / sizeof (items[0]);
    menu.length = size;
    menu.items = malloc(sizeof(Item) * size); 

    for(int i=0;i<size;i++) {               // This only gets us one object
        Item cur = malloc(sizeof(Item));    // When we print the list later
        cur.name = items[i];                // we get 6 instances of 'kubectl'
        menu.items[i] = cur;                // which is the last entry in the list
    }                                       // of titles


    //build menu
    for(int i=0;i<size;i++) {               // We need to malloc a new Item each
        Item *cur = malloc(sizeof(Item));   // time before we copy to avoid
        cur->name = items[i];               // overwriting
        menu.items[i] = cur;
    }
}

```
#### 5/19 
- similar problem as yesterday, but with whole submenu instead of just entries
- each submenu is getting unique entries, but when we add it to the menu, the old ones get overwritten
- testmenu.c results in 3 menus with the same entries (I'm not making a new pointer successfully somewhere where I think I am...)

> submenu size can't be calculated with sizeof because it was defined with ** syntax, you need to count the entries in a loop in [menu.c](./menu.c)

#### 5/26
- saw some strange overwrites happening when trying to build a submenu from a list of filenames in [test-file.c](./test/test-menu.c)
- fixed by changed how we malloc when initializing the Menu

from:
    
    menu->items = malloc(sizeof(Item) * size); 

to:
    
    menu->items = malloc(sizeof(*menu->items) * size); 
