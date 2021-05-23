#include "menu.h"

void addSubMenu(char *name, Menu *menu, int pos, char **items) {

    Menu *temp = malloc(sizeof(Menu));
    int size=0;    

    while(items[size]) size++;

    temp->items = malloc(sizeof(Item) * size);

    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = items[i];
        temp->items[i] = cur;
    }
    temp->length = size;
    menu->items[pos]->submenu = temp;
}
