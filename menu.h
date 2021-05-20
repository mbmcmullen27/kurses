#ifndef MENU_HEADER
#define MENU_HEADER


typedef struct Menu Menu;
typedef struct Item Item;
typedef struct Cursor Cursor;

void addSubMenu(char*,Menu*,int,char**);

struct Cursor {
    int sel[2];
    int depth;
    char* selection;
};

struct Item {
    char *name;
    void (*action)(int);
    Menu *submenu;
};

struct Menu {
    char *title;
    int length;
    Item **items;
};

void addSubMenu(char *name, Menu *menu, int pos, char **items) {

    Menu *temp = malloc(sizeof(Menu));
    int size=0;    

    while(items[size]) size++;

    temp->items = malloc(sizeof(Item) * size);

    for(int i=0;i<size;i++) {
        Item *cur = malloc(sizeof(Item));
        cur->name = items[i];
        temp->items[i] = cur;
    }
    temp->length = size;
    menu->items[pos]->submenu = temp;
}

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
    "Accessibility",
    NULL
};

#endif