#include "menu.h"

void addSubMenu(char *name, Menu *menu, int pos, char **list) {
    WINDOW *cwin;
    WINDOW *win;
    Menu *temp = malloc(sizeof(Menu));
    Cursor *cursor = malloc(sizeof(Cursor));
    temp->parent=menu;
    cursor->sel=0;
    temp->width = 0;
    
    int size = 0;
    while(list[size]) size++;

    temp->items = malloc(sizeof(*temp->items) * size);

    for(int i=0;i<size;i++) {
        int len = strlen(list[i]);
        Item *cur = malloc(sizeof(Item) + sizeof(char*)*len);
        if (temp->width < len) {
            temp->width = len;
        }
        cur->name = list[i];
        cur->submenu = NULL;
        temp->items[i] = cur;
    }

    temp->length = size;
    cursor->offset = menu->offset+menu->width+1;

    //size must be at least the same as the main menu size
    //otherwise the window is too small to draw the connecting line
    if(size>menu->length){
        cwin = derwin(stdscr,size,3,1,cursor->offset);
    } else {
        cwin = derwin(stdscr,menu->length,3,1,cursor->offset);
    }
    
    cursor->win = cwin;
    temp->offset = cursor->offset+3;
    temp->win = derwin(stdscr,size,temp->width,1,temp->offset);
    temp->cursor = cursor;
    menu->items[pos]->submenu = temp;

    keypad(cursor->win,TRUE);
}

/* adds title, calculates size, and adds submenus to the given menu */
void initializeMenu(Menu *menu, char** list) {
    WINDOW *cwin;
    WINDOW *mwin;

    Cursor *cursor = malloc(sizeof(Cursor));
    cursor->sel=0;
    menu->title = "Main";
    int size = 0;               // sizeof list / sizeof (list[0]);
    while(list[size]) size++;   // only arrays defined with [] syntax can use ^^ for length

    menu->length = size;
    menu->items = malloc(sizeof(*menu->items) * size);
    menu->width = 0;
    menu->offset = 3;
    
    // main menu 
    for(int i=0;i<size;i++) {
        int len = strlen(list[i]);
        Item *cur = malloc(sizeof(Item) + sizeof(char*)*len);
        if (menu->width < len) {
            menu->width = len;
        }
        cur->name = list[i];
        menu->items[i] = cur;
    }

    // windows
    cwin = derwin(stdscr,menu->length,3,1,0);
    cursor->win = cwin;
    cursor->offset = 0;

    mwin = derwin(stdscr,menu->length,menu->width,1,3);
    menu->win = mwin;

    menu->cursor=cursor;

    keypad(menu->cursor->win,TRUE);
}

void defaultMenu(Menu *menu){


    initializeMenu(menu,items);
    // submenus
    addSubMenu("Jobs", menu, 0, scripts);
    addSubMenu("Manifests", menu, 1, secondary); // ***
    addSubMenu("tools", menu, 2, tools);
    addSubMenu("Options", menu, 3, options);
    addSubMenu("Context", menu, 4, context);
    addSubMenu("Kubectl", menu, 5, kubectl);

    addSubMenu("By Path",menu->items[1]->submenu,0,paths);
    addSubMenu("By Kind",menu->items[1]->submenu,1,kinds);

}

void drawMenu(Menu *menu){
    werase(menu->win);
    for (int i=0;i<menu->length;i++) {
        mvwaddstr(
            menu->win,
            i,0,
            menu->items[i]->name
        );
    }
    wrefresh(menu->win);
}