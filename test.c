
#include         "stages.h"
/*new test *****8


test
*/
int main(int argc,char* argv[]) {
    FILE *fd1;
    FILE *fd2;
    int i=0;
    char buf[100];
    char *name;
    name=strdup(argv[1]);

    if(argc!=2){
        if(argc>2){
            printf("To many arguments\n");
            exit(0);
        }
        else {
            printf("No arguments /*test*/ entered"); 
            exit(0);
        }
    }
/*test*/strcpy(buf,/*test*/argv[1]);
    while(buf[i]!='\0')
	i++;
    
 
    if(buf[i-2] == '.' && buf[i-1] == 'c' )
        ;
    else {
        printf("This file is not a C type\n");
        exit(0);
    }

    if(!(fd1=fopen(argv[1],"r+"))) {
        printf("Cannot open file\n");
        exit(0);
    }

    fd2=comments_delete(fd1,argv[1]);
    includes(fd2,name);
        return 0;

}
