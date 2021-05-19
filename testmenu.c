#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void levelOne(int*, char**);
void levelTwo(int*, char*);

typedef struct Item {
    char *name;
} Item;

typedef struct Menu {
    char *title;
    int sel[2];
    int level;
    int length;
    Item **items;
} Menu;

int main(){

    Menu menu;
    menu.title = "Main";
    menu.level = 0;
    menu.sel[0] = menu.sel[1] = 0;

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
    printf("size of Item %lu\n",sizeof(Item));
    menu.items = malloc(sizeof(Item) * size); 

    //build menu
    printf("Title: %s\n",menu.title);
    printf("Size: %d\n",menu.length);

    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = items[i];
        menu.items[i] = cur;
    }

    //print menu items
    for(int i=0;i<menu.length;i++) {
        printf("%s\n",menu.items[i]->name);
    }

    return 0;
}