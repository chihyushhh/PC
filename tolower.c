#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char **argv){
    char *text=argv[1];

    char buf[2049]={'\0'};
    char *ptr, *qtr;
    int input, flag;
    unsigned int fileSize;
    struct stat stbuf;

    input=open(text, O_RDWR);
    fstat(input, &stbuf);
    fileSize=stbuf.st_size;
    //printf("%d\n", stbuf.st_size);
    char *tolower=(char *)malloc(sizeof(char)*(fileSize+1));
    qtr=tolower;
    while((flag=read(input, buf, 2048))>0){
        //printf("%s\n", buf);
        buf[flag]='\0';
        ptr=buf;
        int cnt=0;
        while(cnt<2048){
            if(isupper(*ptr)){
                char *tmp=ptr;
                *tmp=*ptr-'A'+'a';
                *qtr++=*tmp;
                ptr++;
            }
            else {
                *qtr++=*ptr++;
            }
            cnt++;
        }
    }
    *qtr='\0';
    //printf("%s\n", tolower);
    lseek(input, 0, SEEK_SET);
    write(input, tolower, fileSize);
    close(input);
    free(tolower);

    return 0;
}