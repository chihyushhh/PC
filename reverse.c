#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){
    char *text=argv[1];

    char buf[2049];
    for(int i=0; i<=2048; i++){buf[i]='\0';}
    char *ptr, *qtr;
    int input, flag;
    unsigned int fileSize;
    struct stat stbuf;

    input=open(text, O_RDWR);
    fstat(input, &stbuf);
    fileSize=stbuf.st_size;
    char *ch=(char *)malloc(sizeof(char)*(fileSize+1));
    char *re_ch=(char *)malloc(sizeof(char)*(fileSize+1));
    qtr=ch;
    while((flag=read(input, buf, 2048))>0){
        buf[flag]='\0';
        //printf("%s\n", buf);
        ptr=buf;
        int cnt=0;
        while(cnt<2048){
            *qtr++=*ptr++;
            cnt++;
        }
    }
    *qtr='\0';
    //printf("%s\n", ch);
    char *p=ch;
    while(*p!='\0'){
        *p++;
    }
    p--;
    //printf("%c\n", *p);
    char *q=re_ch;
    while(p!=ch){
        *q++=*p--;
    }
    //printf("%c\n", *p);
    *q++=*p;
    //printf("%c\n", *q);
    *q='\0';
    //printf("%s\n", re_ch);
    lseek(input, 0, SEEK_SET);
    write(input, re_ch, fileSize);
    close(input);
    free(ch);
    free(re_ch);

    return 0;
}