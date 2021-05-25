#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

char** listdir(const char *path) {

    struct dirent *entry;
    DIR *dp;
    char **files = malloc(sizeof(char*)*20);
    int i=0;

    dp = opendir(path);
    if (dp == NULL) 
    {
        perror("opendir");
        return NULL;
    }

    int size=0;
    while((entry = readdir(dp))){

        printf("%s ->",entry->d_name);

        switch(entry->d_type){
            case (DT_REG):
                printf(" FILE\n");
                break;
            case (DT_DIR):
                printf(" DIRECTORY\n");
                break;
            default:
                break;
        }
        printf("%c",entry->d_type);
        files[i]=entry->d_name;
        i++;
    }

    closedir(dp);
    return files;
}

int main(int argc, char **argv) {
    int counter = 1;

    if (argc == 1)
	    listdir("/mnt/c/Users/mbmcm/fishbot/kubelet");

    while (++counter <= argc) {
        printf("\nListing %s...\n", argv[counter-1]);
        listdir(argv[counter-1]);
    }

    return 0;
}