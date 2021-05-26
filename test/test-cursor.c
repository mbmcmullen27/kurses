#include "../src/menu.h"

void drawCursor(Cursor*);
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

    defaultMenu(&menu);

    titlebar = derwin(stdscr,1,COLS,0,0);

    // keypad(stdscr,TRUE);
    drawMenu(&menu);
    activeMenu = &menu;
    cursor=activeMenu->cursor;
    do {
        curs_set(0);
        int pos[] = { menu.cursor->sel, menu.cursor->sel };
        werase(titlebar);
        wprintw(titlebar,"sel: %d, activeLength: %d, coffset: %d",cursor->sel, activeMenu->length,cursor->offset);
        wrefresh(titlebar);

        drawCursor(cursor);
        if (activeMenu->title!=menu.title) drawLines(activeMenu->parent,activeMenu);

        Menu *next;
        int selection = cursor->sel;
        ch = wgetch(cursor->win);
        switch(ch) {
            case KEY_DOWN:
                if (selection < activeMenu->length-1)
                    cursor->sel++;
                break;
            case KEY_UP:
                if (selection > 0) 
                    cursor->sel--;
                break;
            case KEY_LEFT:
                if(activeMenu->title!=menu.title){
                    Menu *parent = activeMenu->parent;
                    werase(parent->items[parent->cursor->sel]->submenu->win);
                    wrefresh(parent->items[parent->cursor->sel]->submenu->win);
                    werase(cursor->win);
                    wrefresh(cursor->win);
                    activeMenu=parent;
                    cursor=activeMenu->cursor;
                }
                break;
            case KEY_RIGHT:
                if (!activeMenu->items[selection]->submenu) break;
                next = activeMenu->items[selection]->submenu;
                drawMenu(next);
                activeMenu=next;
                cursor=activeMenu->cursor;
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
    int lpos = left->cursor->sel;
    int rpos = right->cursor->sel;

    WINDOW *l=left->cursor->win;
    WINDOW *r=right->cursor->win;
    
    if(lpos<rpos) { // turns down
        wmove(r,lpos,0);
        waddch(r,A_ALTCHARSET | ACS_URCORNER);
        wmove(r,lpos+1,0);
        wvline(r,0,rpos-lpos-1);
        wmove(r,rpos,0);
        waddch(r,A_ALTCHARSET | ACS_LLCORNER);
    }else if(rpos<lpos){ // turns up
        wmove(r,rpos,0);
        waddch(r,A_ALTCHARSET | ACS_ULCORNER);
        wmove(r,rpos+1,0);
        wvline(r,0,lpos-rpos);
        wmove(r,lpos,0);
        waddch(r,A_ALTCHARSET | ACS_LRCORNER);
    }else{
        wmove(r,rpos,0);
        whline(r,0,1);
    }

}
