#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "menu.h"

void levelOne(int*, char**);
void levelTwo(int*, char*);


int main(){

    Menu menu;
    Cursor cursor;
    menu.title = "Main";
    cursor.depth = 0;
    menu.length = 6;

    menu.items = malloc(sizeof(Item) * menu.length); 

    //build menu
    printf("Title: %s\n",menu.title);
    printf("Size: %d\n",menu.length);

    for(int i=0;i<menu.length;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = items[i];
        menu.items[i] = cur;
    }

    addSubMenu("Jobs", &menu, 0, scripts);
    addSubMenu("Manifests", &menu, 1, kinds);
    addSubMenu("Options", &menu, 3, options);
    
    //print menu items
    printf("Menu item names:\n");
    for(int i=0;i<menu.length;i++) {
        Item *item = menu.items[i];
        printf("%s:\n",item->name);
        if(item->submenu) {
            for(int k=0;k<item->submenu->length;k++) {
                Item *sub = item->submenu->items[k];
                printf("\t- %s\n",sub->name);
            }
        }
    }

    return 0;
}

