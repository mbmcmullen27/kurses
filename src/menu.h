#ifndef MENU_HEADER
#define MENU_HEADER

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct Menu Menu;
typedef struct Item Item;
typedef struct Cursor Cursor;

void addSubMenu(char*,Menu*,int,char**);
void initializeMenu(Menu*,char**);
void defaultMenu(Menu*);
void drawMenu(Menu*);


struct Cursor {
    int sel;
    int offset;
    WINDOW *win;
};

struct Item {
    char *name;
    void (*action)(int);
    Menu *submenu;
    WINDOW *win;
};

struct Menu {
    char *title;
    int length;
    int width;
    int offset;
    Item **items;
    WINDOW *win;
    Cursor *cursor;
    Menu *parent;
};

static char *items[7] = {
        "Jobs",
        "Manifests",
        "Tools",
        "Options",
        "Context",
        "Kubectl",
        NULL
    };

static char *scripts[7] = {
    "Build",
    "Deploy",
    "Edit",
    "Destroy",
    "Devops/util",
    "Python/scratch",
    NULL
};

static char *secondary[3] = {
    "By Path",
    "By Kind",
    NULL
};

static char *paths[6] = {
    "/manifests/online/pods",
    "/manifests/security/pods",
    "/manifests/stolen/pods",
    "/manifests/legacy/pods",
    "/secrets/all",
    NULL
};

static char *kinds[6] = {
    "Pods",
    "Deployments",
    "Services",
    "Ingresses",
    "Configmaps",
    NULL
};

static char *tools[8] = {
    "Curl-Pod",
    "Ping-Pod",
    "Goldfish",
    "Clusterbuster",
    "Porpoise",
    "Sniff",
    "Kurses",
    NULL
};

static char *options[7] = {
    "Theme",
    "Keybinds",
    "Crontab",
    "Integrations",
    "Storage",
    "Accessibility",
    NULL
};

static char *context[8] = {
    "Account",
    "Service Bus",
    "Get-Credentials",
    "Security Policy",
    "AKS version: 0.0.1",
    "Kubernetes version: 1.19.9",
    "Config File Path: ~/.config/kurses",
    NULL
};

static char *kubectl[5] = {
    "Get...",
    "Describe...",
    "Exec...",
    "Rollout Restart...",
    NULL
};

#endif