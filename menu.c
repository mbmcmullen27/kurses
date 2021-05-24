#include "menu.h"

void addSubMenu(char *name, Menu *menu, int pos, char **items) {

    Menu *temp = malloc(sizeof(Menu));
    temp->parent=menu;
    Cursor *cursor;
    cursor = malloc(sizeof(Cursor));
    cursor->sel=0;
    WINDOW *win;
    temp->width = 0;
    int size = 0;
    while(items[size]) size++;

    temp->items = malloc(sizeof(Item) * size);

    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        if (temp->width < strlen(items[i])) {
            temp->width = strlen(items[i]);
        }
        cur->name = items[i];
        cur->submenu = NULL;
        temp->items[i] = cur;
    }

    temp->length = size;
    cursor->offset = menu->offset+menu->width+1;

    //size must be at least the same as the main menu size
    //otherwise the window is too small to draw the connecting line
    if(size>menu->length){
        cursor->win = derwin(stdscr,size,3,1,cursor->offset);
    } else {
        cursor->win = derwin(stdscr,menu->length,3,1,cursor->offset);
    }
    temp->offset = cursor->offset+3;
    temp->win = derwin(stdscr,size,temp->width,1,temp->offset);
    temp->cursor = cursor;
    menu->items[pos]->submenu = temp;

    keypad(cursor->win,TRUE);
}

/* adds title, calculates size, and adds submenus to the given menu */
void initializeMenu(Menu *menu) {
    WINDOW *cwin;
    WINDOW *mwin;

    Cursor *cursor = malloc(sizeof(Cursor));
    cursor->sel=0;
    menu->title = "Main";
    int size = sizeof items / sizeof (items[0]);
    menu->length = size;
    menu->items = malloc(sizeof(Item) * size); 
    menu->width = 0;
    menu->offset = 3;
    
    // main menu menu
    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        if (menu->width < strlen(items[i])) {
            menu->width = strlen(items[i]);
        }
        cur->name = items[i];
        menu->items[i] = cur;
    }

    // submenus
    addSubMenu("Jobs", menu, 0, scripts);
    addSubMenu("Manifests", menu, 1, secondary); // ***
    addSubMenu("tools", menu, 2, tools);
    addSubMenu("Options", menu, 3, options);
    addSubMenu("Context", menu, 4, context);
    addSubMenu("Kubectl", menu, 5, kubectl);

    addSubMenu("By Path",menu->items[1]->submenu,0,paths);
    addSubMenu("By Kind",menu->items[1]->submenu,1,kinds);

    // windows
    cwin = derwin(stdscr,menu->length,3,1,0);
    cursor->win = cwin;
    cursor->offset = 0;

    mwin = derwin(stdscr,menu->length,menu->width,1,3);
    menu->win = mwin;

    menu->cursor=cursor;

    keypad(menu->cursor->win,TRUE);
}