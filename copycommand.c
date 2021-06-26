#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){
    char *copied_path=argv[1];
    char *target_path=argv[2];

    char buf[2048];
    int input, output, flag;

    input=open(copied_path, O_RDONLY);
    if(input==-1) printf("開啟檔案失敗\n");
    output=open(target_path, O_WRONLY|O_CREAT);
    if(output==-1) printf("開啟或建立檔案失敗\n");
    while((flag=read(input, buf, 2048))>0){
        write(output, buf, flag);
    }
    close(input);
    close(output);

    return 0;
}