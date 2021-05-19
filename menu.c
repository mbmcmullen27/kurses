#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void levelOne(int*, char**);
void levelTwo(int*, char*);

typedef struct Item {
    char *name;
    void (*action)(int);
    struct Menu *submenu;
} Item;

typedef struct Menu {
    char *title;
    int sel[2];
    int level;
    int length;
    Item **items;
} Menu;

int main(){

    struct Menu menu;
    menu.title = "Main";
    menu.level = 0;
    menu.sel[0] = menu.sel[0] = 0;
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

    keypad(stdscr,TRUE);
    do {
        // //print menu items
        // for(int i=0;i<menu.length;i++) {
        //     move((LINES/2)+i,0);
        //     printw(menu.items[i]->name);
        // }
        // refresh();
        
        int pos = menu.sel[0];
        move(0,0);
        printw("menu.sel[0]: %d, menu.sel[1]: %d , pos: %d",menu.sel[0],menu.sel[1],pos);
        levelOne(menu.sel,items);
        if(menu.level>0){
            int selection = pos;
            levelTwo(menu.sel, menu.items[selection]->name);
        } 
        ch = getch();
        switch(ch) {
            case KEY_DOWN:
                if (menu.sel[menu.level] < lvllen[menu.level]-1)
                    menu.sel[menu.level]++;
                break;
            case KEY_UP:
                if (menu.sel[menu.level] > 0) menu.sel[menu.level]--;
                break;
            case KEY_LEFT:
                if (menu.level > 0) menu.level--;
                break;
            case KEY_RIGHT:
                if (menu.level < 1) menu.level++;
                menu.sel[menu.level]=pos;
                break;
            default:
                break;
        }
        clear();
    } while (ch != 27);


    endwin();
    return(0);
}

void levelOne(int *pos, char **items) {
    for (int i=0;i<6;i++) {
        move(i+1,4);
        addstr(items[i]);
    }

    move(pos[0]+1,1);
    addch(A_ALTCHARSET | ACS_HLINE);
    addstr(">");
    
    refresh();
}

void levelTwo(int *pos, char *item) {
    move(LINES/2,COLS/2);
    int len=strlen(item);
    printw("selection length: %d",len);
    move((LINES/2)+1,COLS/2);
    printw("selection: ");
    printw(item);

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

    refresh();
}