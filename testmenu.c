#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Menu Menu;
typedef struct Item Item;

void levelOne(int*, char**);
void levelTwo(int*, char*);

void addSubMenu(char*,Menu*,int,char**);

struct Item {
    char *name;
    Menu *submenu;
};

struct Menu {
    char *title;
    int sel[2];
    int level;
    int length;
    Item **items;
};

int main(){

    Menu menu;
    menu.title = "Main";
    menu.level = 0;
    menu.length = 6;

    char *items[6] = {
        "Jobs",
        "Manifests",
        "Tools",
        "Options",
        "Context",
        "Kubectl"
    };

    char *scripts[5] = {
        "Build",
        "Deploy",
        "Edit",
        "Destroy",
        NULL
    };

    char *kinds[6] = {
        "Pods",
        "Deployments",
        "Services",
        "Ingresses",
        "Configmaps",
        NULL
    };

    char *options[9] = {
        "Get-Credentials",
        "Theme",
        "Keybinds",
        "Crontab",
        "Config File Path: ~/.config/kurses",
        "Integrations",
        "Storage",
        "Accessibility Settings",
        NULL
    };
    
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
    // addSubMenu("Options", &menu, 3, options);
    
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

void addSubMenu(char *name, Menu *menu, int pos, char **items) {

    Menu temp;
    int size=0;     //sizeof items / sizeof (items[0]);

    while(items[size]) size++;

    temp.items = malloc(sizeof(Item) * size);

    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = items[i];
        temp.items[i] = cur;
    }
    temp.length = size;

    menu->items[pos]->submenu = &temp;
}