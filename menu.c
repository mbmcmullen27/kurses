#include <ncurses.h>
#include <string.h>

void levelOne(int*, char**);
void levelTwo(int*, char**);

struct Menu {
    char **items;
    int sel[2];
    int level;
    struct Menu **submenu;
};

int main(){

    struct Menu menu;
    menu.sel[0] = menu.sel[0] = 0;
    int lvllen[2] = {6,6};
    int level;

    int ch;
    char *items[6] = {
        "Jobs",
        "Manifests",
        "Tools",
        "Options",
        "Context",
        "Kubectl"
    };

    initscr();
    keypad(stdscr,TRUE);
    do {
        int pos = menu.sel[0];
        printw("menu.sel[0]: %d, menu.sel[1]: %d ",menu.sel[0],menu.sel[1]);;
        levelOne(menu.sel,items);
        if(level>0) levelTwo(menu.sel,items);
        ch = getch();
        switch(ch) {
            case KEY_DOWN:
                if (menu.sel[level] < lvllen[level]-1) menu.sel[level]++;
                break;
            case KEY_UP:
                if (menu.sel[level] > 0) menu.sel[level]--;
                break;
            case KEY_LEFT:
                if (level > 0) level--;
                break;
            case KEY_RIGHT:
                if (level < 1) level++;
                menu.sel[level]=pos;
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

void levelTwo(int *pos, char **items) {
    move(LINES/2,COLS/2);
    int len=strlen(items[pos[0]]);
    printw("selection length: %d",len);

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