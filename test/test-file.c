#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../src/menu.h"

int main() {

    struct dirent *entry;
    DIR *dp;
    char *files[5];

    int i=0;
    Menu menu;
    menu.title = "Main";

    dp = opendir("/home/fishbot/git/mern-stack");
    if (dp == NULL) 
    {
        perror("opendir");
        return 1;
    }
    // rewinddir(dp);

    while((entry = readdir(dp))){
        if (!strcmp(entry->d_name,".") || !strcmp(entry->d_name,"..")) 
            continue;
        printf("%s ->",entry->d_name);
        switch(entry->d_type){
            case (DT_REG):
                printf(" FILE\n");
                files[i] = entry->d_name;
                i++;
                break;
            case (DT_DIR):
                printf(" DIRECTORY\n");
                break;
            default:
                break;
        }
    }
    files[i]=NULL;

    for (i=0;i<5;i++){
        printf("\t[%d] - %s\n",i,files[i]);
    }

    closedir(dp);

    initializeMenu(&menu,files);

    initscr();
    drawMenu(&menu);
    wrefresh(menu.win);
    refresh();
    getch();
    endwin();

    // int len = menu.items[0]->submenu->length;
    printf("\n>>>> Submenu Items\n");
    for (i=0;i<menu.length;i++){
        printf("\t[%d] - %s\n",i,menu.items[i]->name);
    }
    puts("");
    for (i=0;i<5;i++){
        printf("\t[%d] - %s\n",i,files[i]);
    }

    return 0;
}