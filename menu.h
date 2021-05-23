#ifndef MENU_HEADER
#define MENU_HEADER

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct Menu Menu;
typedef struct Item Item;
typedef struct Cursor Cursor;

void addSubMenu(char*,Menu*,int,char**);

struct Cursor {
    int sel[2];
    int depth;
    char* selection;
    WINDOW **cwin;
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
    WINDOW *win;
};

static char *items[6] = {
        "Jobs",
        "Manifests",
        "Tools",
        "Options",
        "Context",
        "Kubectl"
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