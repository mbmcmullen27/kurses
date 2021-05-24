#include <stdio.h>
#include "menu.h"

void levelOne(int*, char**);
void levelTwo(int*, char*);


int main(){

    Menu menu;
    Cursor *cursor;
    cursor = malloc(sizeof(Cursor));
    menu.title = "Main";
    menu.length = 6;
    int i;

    menu.items = malloc(sizeof(Item) * menu.length); 

    //build menu
    // printf("Title: %s\n",menu.title);
    // printf("Size: %d\n",menu.length);

    // for(int i=0;i<menu.length;i++) {
    //     Item *cur = malloc(sizeof(Item));
    //     cur->name = items[i];
    //     menu.items[i] = cur;
    // }

    // addSubMenu("Jobs", &menu, 0, scripts);
    // addSubMenu("Manifests", &menu, 1, kinds);
    // addSubMenu("tools", &menu, 2, tools);
    // addSubMenu("Options", &menu, 3, options);
    // addSubMenu("Context", &menu, 4, context);
    // addSubMenu("Kubectl", &menu, 5, kubectl);

    initializeMenu(&menu);

    //print cursor
    printf("Menu Cursor:\n");
    printf("  sel:%d, offset:%d\n",cursor->sel,cursor->offset);

    //print menu items
    printf("Menu items:\n");
    for(i=0;i<menu.length;i++) {
        Item *item = menu.items[i];
        printf("%s:\n",item->name);
        if(item->submenu) {
            Menu *sub = item->submenu;
            printf("  length=%d\n",sub->length);
            printf("  width=%d\n",sub->width);
            printf("    Submenu Cursor:\n");
            printf("    sel:%d, offset:%d\n",sub->cursor->sel,sub->cursor->offset);
            for(int k=0;k<sub->length;k++) {
                Item *entry = sub->items[k];
                printf("\t- %s\n",entry->name);
            }
        }
    }

    return 0;
}

