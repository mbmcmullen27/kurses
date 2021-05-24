#include "menu.h"

void drawCursor(Cursor*);
void drawMenu(Menu*);

int main(){

    Menu menu;
    Cursor cursor;
    WINDOW *cwin;
    WINDOW *mwin;
    WINDOW *titlebar;
    int ch;

    initscr();
    // curs_set(0);
    refresh();

    initializeCursor(&cursor);
    initializeMenu(&menu,3);

    cwin = derwin(stdscr,menu.length,3,1,0);
    cursor.win = cwin;

    mwin = derwin(stdscr,menu.length,menu.width,1,3);
    menu.win = mwin;

    titlebar = derwin(stdscr,1,COLS,0,0);

    keypad(cursor.win,TRUE);
    drawMenu(&menu);
    do {
        curs_set(0);
        int pos = cursor.sel[0];
        int level = cursor.depth;
        move(0,0);
        werase(titlebar);
        wprintw(titlebar,"sel[0]: %d, sel[1]: %d, level: %d, length: %d",cursor.sel[0],cursor.sel[1],level, menu.length);
        wrefresh(titlebar);

        drawCursor(&cursor);

        ch = wgetch(cursor.win);
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
                if (level > 0){
                    cursor.depth--;
                    werase(menu.items[pos]->submenu->win);
                    wrefresh(menu.items[pos]->submenu->win);
                } 
                break;
            case KEY_RIGHT:
                if (level < 1) cursor.depth++;
                if ( pos+1 > menu.items[pos]->submenu->length )
                    cursor.sel[cursor.depth]=menu.items[pos]->submenu->length - 1;
                else
                    cursor.sel[cursor.depth]=pos;
                drawMenu(menu.items[pos]->submenu);
                break;
            default:
                break;
        }
    } while (ch != 27);


    endwin();
    return(0);
}

//wgetch does an implicit refresh so we don't need one in this function
void drawCursor(Cursor *cursor){
    werase(cursor->win);
    mvwaddstr(cursor->win,cursor->sel[0],0, "->");
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