#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stages.h"

int main(int argc,char* argv[]) {
    FILE *fd;
    FILE *fd1;
    int i=0;
    char buf[100];
    char *name;
    
    if(argc!=2){
        if(argc>2){
            printf("To many arguments\n");
            exit(0);
        }
        else {
            printf("No arguments entered\n");
            exit(0);
        }
    }

    name=strdup(argv[1]);

    strcpy(buf,argv[1]);
    while(buf[i]!='\0')
	i++;
 
    if(buf[i-2] == '.' && buf[i-1] == 'c' )
        ;
    else {
        printf("This file is not a C type\n");
        exit(0);
    }

    if(!(fd=fopen(argv[1],"r+"))) {
        printf("Cannot open file\n");
        exit(0);
    }

    fd1=comments_delete(fd,argv[1]);
    includes(fd1,name);
   
    return 0;
}
