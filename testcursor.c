#include "menu.h"

void drawCursor(Cursor*);
void drawMenu(Menu*);
void drawLines(Menu*,Menu*);

int main(){

    Cursor *cursor = malloc(sizeof(Cursor));
    Menu *activeMenu = malloc(sizeof(Menu));
    Menu menu;
    WINDOW *titlebar;
    int ch;

    initscr();
    // curs_set(0);
    refresh();

    initializeMenu(&menu);

    titlebar = derwin(stdscr,1,COLS,0,0);

    keypad(stdscr,TRUE);
    drawMenu(&menu);
    int level = 0;
    activeMenu = &menu;
    cursor=activeMenu->cursor;
    do {
        curs_set(0);
        int pos[] = { menu.cursor->sel, menu.cursor->sel };
        werase(titlebar);
        wprintw(titlebar,"sel: %d, activeLength: %d, coffset: %d",cursor->sel, activeMenu->length,cursor->offset);
        wrefresh(titlebar);

        drawCursor(cursor);
        if (level > 0) drawLines(&menu,activeMenu);

        Menu *next;
        ch = wgetch(cursor->win);
        switch(ch) {
            case KEY_DOWN:
                if (cursor->sel < activeMenu->length-1)
                    cursor->sel++;
                break;
            case KEY_UP:
                if (cursor->sel > 0) 
                    cursor->sel--;
                break;
            case KEY_LEFT:
                if(level>0){
                    werase(menu.items[menu.cursor->sel]->submenu->win);
                    wrefresh(menu.items[menu.cursor->sel]->submenu->win);
                    werase(cursor->win);
                    wrefresh(cursor->win);
                    level--;
                    activeMenu=&menu;
                    cursor=activeMenu->cursor;
                }
                break;
            case KEY_RIGHT:
                // if (menu->items[pos]->submenu) break;
                if(level<1){
                    level++;
                
                    next = menu.items[pos[level]]->submenu;
                    drawMenu(next);
                    activeMenu=next;
                    cursor=activeMenu->cursor;
                }
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
    mvwaddstr(cursor->win,cursor->sel,1, ">");
}

void drawLines(Menu *left, Menu *right){
    int pos1 = left->cursor->sel;
    int pos2 = right->cursor->sel;

    WINDOW *r=right->cursor->win;
    // werase(r);
    if(pos1<pos2) {
        wmove(r,pos1,0);
        waddch(r,A_ALTCHARSET | ACS_URCORNER);
        wmove(r,pos1+1,0);
        wvline(r,0,pos2-pos1-1);
        wmove(r,pos2,0);
        waddch(r,A_ALTCHARSET | ACS_LLCORNER);
    }else if(pos2<pos1){
        wmove(r,pos2,0);
        waddch(r,A_ALTCHARSET | ACS_ULCORNER);
        wmove(r,pos2+1,0);
        wvline(r,0,pos1-pos2);
        wmove(r,pos1,0);
        waddch(r,A_ALTCHARSET | ACS_LRCORNER);
    }else{
        wmove(r,pos2,0);
        whline(r,0,1);
    }

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