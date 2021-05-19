#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Menu Menu;
typedef struct Item Item;

void levelOne(int*, char**);
void levelTwo(int*, char*);

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

    Menu jobs;
    jobs.title = "Jobs";
    jobs.level = 1;
    jobs.length = 4;

    Menu manifests;
    manifests.title = "Jobs";
    manifests.level = 1;
    manifests.length = 5;


    char *items[6] = {
        "Jobs",
        "Manifests",
        "Tools",
        "Options",
        "Context",
        "Kubectl"
    };

    char *scripts[4] = {
        "Build",
        "Deploy",
        "Edit",
        "Destroy",
    };

    char *kinds[5] = {
        "Pods",
        "Deployments",
        "Services",
        "Ingresses",
        "Configmaps"
    };

    menu.items = malloc(sizeof(Item) * menu.length); 
    jobs.items = malloc(sizeof(Item) * jobs.length); 
    manifests.items = malloc(sizeof(Item) * manifests.length); 

    //build menu
    printf("Title: %s\n",menu.title);
    printf("Size: %d\n",menu.length);

    for(int i=0;i<menu.length;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = items[i];
        menu.items[i] = cur;
    }

    for(int i=0;i<jobs.length;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = scripts[i];
        jobs.items[i] = cur;
    }

    for(int i=0;i<manifests.length;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = kinds[i];
        manifests.items[i] = cur;
    }

    menu.items[0]->submenu = &jobs;
    menu.items[1]->submenu = &manifests;

    
    //print menu items
    printf("Menu item names:\n");
    for(int i=0;i<menu.length;i++) {
        printf("%s\n",menu.items[i]->name);
    }

    printf("\nJobs item names:\n");
    for(int i=0;i<jobs.length;i++) {
        printf("%s\n",menu.items[0]->submenu->items[i]->name);
    }

    printf("\nManifests item names:\n");
    for(int i=0;i<manifests.length;i++) {
        printf("%s\n",menu.items[1]->submenu->items[i]->name);
    }

    return 0;
}