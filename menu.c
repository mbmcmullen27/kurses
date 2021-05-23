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

void initializeCursor(Cursor *cursor) {
    cursor->sel[0] = cursor->sel[1] = 0;
    cursor->depth=0;
}

void initializeMenu(Menu *menu) {
    menu->title = "Main";
    int size = sizeof items / sizeof (items[0]);
    menu->length = size;
    menu->items = malloc(sizeof(Item) * size); 

    
    // build menu
    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = items[i];
        menu->items[i] = cur;
    }


    addSubMenu("Jobs", menu, 0, scripts);
    addSubMenu("Manifests", menu, 1, kinds);
    addSubMenu("tools", menu, 2, tools);
    addSubMenu("Options", menu, 3, options);
    addSubMenu("Context", menu, 4, context);
    addSubMenu("Kubectl", menu, 5, kubectl);
}