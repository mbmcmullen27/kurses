#include "menu.h"

void levelTwo(int*, Item*);
void levelOne(int, int, Menu*);
void drawCursor(Cursor*);

int main(){

    Menu menu;
    Cursor cursor;
    int ch;

    initscr();
    initializeCursor(&cursor);
    initializeMenu(&menu);

    // main loop
    keypad(stdscr,TRUE);
    do {
        int pos = cursor.sel[0];
        int level = cursor.depth;
        cursor.selection = menu.items[pos]->name;
        move(0,0);
        printw("sel[0]: %d, sel[1]: %d, level: %d, length: %d",cursor.sel[0],cursor.sel[1],level, menu.length);

        levelOne(cursor.sel[0],0,&menu);
        drawCursor(&cursor);
        
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
                if ( pos+1 > menu.items[pos]->submenu->length )
                    cursor.sel[cursor.depth]=menu.items[pos]->submenu->length - 1;
                else
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

void drawCursor(Cursor *pos){
    if (pos->depth == 0) {
        move(pos->sel[0]+1,1);
        addch(A_ALTCHARSET | ACS_HLINE);
        addstr(">");

    } else if (pos->depth > 0)  {
        int len=strlen(pos->selection);
        move(pos->sel[0]+1,5+len);
        for (int i=0; i<13-len; i++) {
            insch(A_ALTCHARSET | ACS_HLINE);
        }

        move(pos->sel[0]+1,17);
        if ( pos->sel[1]<pos->sel[0] ) {
            addch(A_ALTCHARSET | ACS_LRCORNER);
            move(pos->sel[1]+1,17);
            addch(A_ALTCHARSET | ACS_ULCORNER);
        } else if ( pos->sel[1]>pos->sel[0] ) {
            addch(A_ALTCHARSET | ACS_URCORNER);
            move(pos->sel[1]+1,17);
            addch(A_ALTCHARSET | ACS_LLCORNER);
        } else {
            addch(A_ALTCHARSET | ACS_HLINE);
        }
        addch(A_ALTCHARSET | ACS_HLINE);
        addstr(">");

        for (int i=0;i<=6;i++) {
            if(i<pos->sel[0] && i > pos->sel[1])
                mvaddch(i+1,17,A_ALTCHARSET | ACS_VLINE);
            if(i>pos->sel[0] && i < pos->sel[1])
                mvaddch(i+1,17,A_ALTCHARSET | ACS_VLINE);
        }

    }
    
    refresh();
}

void levelOne(int sel, int x, Menu *menu) {
    for (int i=0;i<menu->length;i++) {
        move(i+1,x+4);
        addstr(menu->items[i]->name);
    }
}

void levelTwo(int *pos, Item *selection) {
    char *name = selection->name;
    move(LINES/2,COLS/2);
    int len=strlen(name);
    printw("selection length: %d",len);
    move((LINES/2)+1,COLS/2);
    printw("selection: ");
    printw(name);

    levelOne(pos[0],17,selection->submenu);

    refresh();
}