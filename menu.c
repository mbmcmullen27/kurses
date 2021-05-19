#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct Menu Menu;
typedef struct Item Item;
typedef struct Cursor Cursor;

void levelTwo(int*, Item*);
void levelOne(int, int, Item**);
void addSubMenu(char*,Menu*,int,char**);


struct Cursor {
    int sel[2];
    int depth;
};

struct Item {
    char *name;
    void (*action)(int);
    Menu *submenu;
};

struct Menu {
    char *title;
    int length;
    Item **items;
};

int main(){

    struct Menu menu;
    menu.title = "Main";
    Cursor cursor;
    cursor.sel[0] = cursor.sel[1] = 0;
    cursor.depth=0;
    int lvllen[2] = {6,6};

    int ch;
    char *items[6] = {
        "Jobs",
        "Manifests",
        "Tools",
        "Options",
        "Context",
        "Kubectl"
    };

    char *options[9] = {
        "Get-Credentials",
        "Theme",
        "Keybinds",
        "Crontab",
        "Config File Path: ~/.config/kurses",
        "Integrations",
        "Storage",
        "Accessibility Settings",
        NULL
    };

    int size = sizeof items / sizeof (items[0]);
    menu.length = size;
    menu.items = malloc(sizeof(Item) * size); 

    initscr();

    //build menu
    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = items[i];
        menu.items[i] = cur;
    }

    addSubMenu("Options", &menu, 3, options);


    keypad(stdscr,TRUE);
    do {
        // //print menu items
        // for(int i=0;i<menu.length;i++) {
        //     move((LINES/2)+i,0);
        //     printw(menu.items[i]->name);
        // }
        // refresh();
        
        int pos = cursor.sel[0];
        int level = cursor.depth;
        move(0,0);
        printw("sel[0]: %d, sel[1]: %d, level: %d, length: %d",cursor.sel[0],cursor.sel[1],level, menu.length);

        levelOne(cursor.sel[0],0,menu.items);
        
        if(level>0){
            levelTwo(cursor.sel, menu.items[pos]);
        } 
        ch = getch();
        switch(ch) {
            case KEY_DOWN:
                if (level==1){
                    Item *item = menu.items[pos];
                    if (cursor.sel[1] < item->submenu->length-1)
                        cursor.sel[1]++;
                } else {
                    if (cursor.sel[0] < menu.length-1)
                        cursor.sel[0]++;
                }
                break;
            case KEY_UP:
                if (cursor.sel[level] > 0) cursor.sel[level]--;
                break;
            case KEY_LEFT:
                if (level > 0) cursor.depth--;
                break;
            case KEY_RIGHT:
                if (level < 1) cursor.depth++;
                cursor.sel[cursor.depth]=pos;
                break;
            default:
                break;
        }
        clear();
    } while (ch != 27);


    endwin();
    return(0);
}

void levelOne(int sel, int x, Item **items) {
    for (int i=0;i<6;i++) {
        move(i+1,x+4);
        addstr(items[i]->name);
    }

    move(sel+1,x+1);
    addch(A_ALTCHARSET | ACS_HLINE);
    addstr(">");
    
    refresh();
}

void levelTwo(int *pos, Item *selection) {
    char *name = selection->name;
    move(LINES/2,COLS/2);
    int len=strlen(name);
    printw("selection length: %d",len);
    move((LINES/2)+1,COLS/2);
    printw("selection: ");
    printw(name);

    move(pos[0]+1,5+len);
    for (int i=0; i<13-len; i++) {
        insch(A_ALTCHARSET | ACS_HLINE);
    }

    move(pos[0]+1,17);
    if ( pos[1]<pos[0] ) {
        addch(A_ALTCHARSET | ACS_LRCORNER);
        move(pos[1]+1,17);
        addch(A_ALTCHARSET | ACS_ULCORNER);
    } else if ( pos[1]>pos[0] ) {
        addch(A_ALTCHARSET | ACS_URCORNER);
        move(pos[1]+1,17);
        addch(A_ALTCHARSET | ACS_LLCORNER);
    } else {
        addch(A_ALTCHARSET | ACS_HLINE);
    }
    addch(A_ALTCHARSET | ACS_HLINE);
    addstr(">");

    for (int i=0;i<=6;i++) {
        if(i<pos[0] && i > pos[1])
            mvaddch(i+1,17,A_ALTCHARSET | ACS_VLINE);
        if(i>pos[0] && i < pos[1])
            mvaddch(i+1,17,A_ALTCHARSET | ACS_VLINE);
    }

    levelOne(pos[0],17,selection->submenu->items);

    refresh();
}

void addSubMenu(char *name, Menu *menu, int pos, char **items) {

    Menu *temp = malloc(sizeof(Menu));
    int size=0;     //sizeof items / sizeof (items[0]);

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