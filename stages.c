#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAR_OF_INCLUDE 7

FILE *comments_delete(FILE * fd,char *name){/*stage 1*/

    FILE *fd1; /*for a file that ends  with .1 */
    enum status{OUT,IN_STRING,LEFT_SLASH,IN_COMMENT,RIGHT_STAR};
    int status=OUT;
    int c;
    char *s[1];   
    s[0]="1";
    strcat(name,s[0]);
    if(!(fd1=fopen(name,"w+"))){
     	  printf("Cannot open file _____.c1");
  	  exit(0);
    }
    while((c=fgetc(fd))!=EOF){
        switch (status) {
            case OUT: {
                if (c == '/')
                    status = LEFT_SLASH;
                else {
                    fputc(c, fd1);
                }
                if (c == '\"') {
                    status = IN_STRING;
                }
                break;
            }
            case LEFT_SLASH: {
                if (c == '*')
                    status = IN_COMMENT;
                else {
                    fputc('/', fd1);
                    fputc(c, fd1);
                    status = OUT;
                }
                break;
            }
            case IN_COMMENT: {
                if (c == '*')
                    status = RIGHT_STAR;
                break;
            }
            case RIGHT_STAR: {
                if (c == '/')
                    status = OUT;
                else if (c != '*')
                    status = IN_COMMENT;
                break;
            }
            case IN_STRING: {
                if (c == '\"')
                    status = OUT;
                fputc(c, fd1);
                break;
            }
        }
    }
    if(fclose(fd)){
	printf("Cannot close file ____.c\n");
  	exit(0);
    }
    rewind(fd1);
    return fd1;
}

void includes(FILE * fd1,char *name){ /*stage 2*/
    FILE *fd2;  /*for a file that ends  with .2 */
    FILE *fd3;  /*for a file we need to import data*/
    fpos_t p2;
    enum status {OUT,IN_INCLUDE,IN_HASHTAG,IN_QUOTATION_MARK,COPY2FILE};
    int status =OUT;
    int c;
    int i=0;
    int j=0;
    char *s[1];
    char strCmp[CHAR_OF_INCLUDE];
    char strCmp1[CHAR_OF_INCLUDE];
    char fileName[250];
    strcpy(strCmp1, "include"); 
    s[0]="2";
    strcat(name,s[0]);

    if(!(fd2=fopen(name,"w"))){
     	printf("Cannot open file _____.c2");
  	exit(0);
    }

    while((c=fgetc(fd1))!=EOF){
        switch (status) {
            case OUT:{
                fgetpos(fd1,&p2);
                if (c=='#'){
                    status=IN_HASHTAG;
                    break;
                }
                fputc(c,fd2);
                break;
            }
            case IN_HASHTAG:{
                if(i<=6) {
                    strCmp[i] = (char)c;
                    i++;
                    break;
             }
                if (!strncmp(strCmp, strCmp1,6)){ 
                    if (c=='\"'){               
         		status = IN_QUOTATION_MARK;
                        i=0;
                        break;
                    }
                    else break;
                }
                else{
                    fsetpos(fd1,&p2);
                    fputc('#',fd2);
                    status=OUT;
                    i=0;
                    break;
                }
            }
            case IN_QUOTATION_MARK:{ 
                if (c!='\"'){
                    fileName[j]=(char)c;
                    j++;
		    break;
                }
                fileName[j]='\0';  
                j=0;
                status= COPY2FILE;
                break;
            }
            case COPY2FILE:{
               if(!(fd3=fopen(fileName,"r"))){
                   printf("Cannot open file ____.h\n");
                   exit(0);
               }
                while((c=fgetc(fd3))!=EOF){
                    fputc(c,fd2);
                }
                status=OUT;
                break;
            }
        }
    }
   if(fclose(fd1)){
	printf("Cannot close file ____.c1\n");
  	exit(0);
    }
   if(fclose(fd2)){
	printf("Cannot close file ____.c2\n");
  	exit(0);
    }
   if(fclose(fd3)){
	printf("Cannot close file ____.h\n");
  	exit(0);
   }
}
