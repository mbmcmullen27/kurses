#include "menu.h"

void addSubMenu(char *name, Menu *menu, int pos, char **items) {

    Menu *temp = malloc(sizeof(Menu));
    int size=0;    
    int width=0;
    while(items[size]){
        if(width < strlen(items[size]))
            width = strlen(items[size]);
        size++;
    }   

    temp->items = malloc(sizeof(Item) * size);

    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = items[i];
        temp->items[i] = cur;
    }

    temp->length = size;
    temp->width = width;
    temp->offset = menu->offset+menu->width+5;
    temp->win=derwin(stdscr,size,width,1,temp->offset);
    menu->items[pos]->submenu = temp;
}

/* initalize a cursor with depth of 2 pointing to (0,0) */
void initializeCursor(Cursor *cursor) {
    cursor->sel[0] = cursor->sel[1] = 0;
    cursor->depth=0;
}

/* adds title, calculates size, and adds submenus to the given menu */
void initializeMenu(Menu *menu, int offset) {
    menu->title = "Main";
    int size = sizeof items / sizeof (items[0]);
    menu->length = size;
    menu->items = malloc(sizeof(Item) * size); 
    menu->width = 0;
    menu->offset = 3;
    
    // build menu
    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        if (menu->width < strlen(items[i])) {
            menu->width = strlen(items[i]);
        }
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