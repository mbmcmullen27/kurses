#include "menu.h"

void drawCursor(Cursor*);
void drawMenu(Menu*);

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
                    werase(menu.items[pos[0]]->submenu->win);
                    wrefresh(menu.items[pos[0]]->submenu->win);
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
    mvwaddstr(cursor->win,cursor->sel,0, "->");
    wrefresh(cursor->win);
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