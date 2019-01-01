#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd1,fd2,fd3,fd4;
 
    char * c1 = "/tmp/c1";
    char * c2 = "/tmp/c2";
    char * c3 = "/tmp/c3";
    char * c4 = "/tmp/c4";
 
    mkfifo(c1, 0666);
    mkfifo(c2, 0666);
    mkfifo(c3, 0666);
    mkfifo(c4, 0666);
 
    int ed1=10,ed2=10,ed3=10,ed4=10, str2=100,pr=-1;
    while (str2 != pr)
    {
        pr = str2;
        
        printf("%d\n", pr);

        fd1 = open(c1,O_RDONLY);
        read(fd1, &ed1, 4);
        close(fd1);
 
        fd2 = open(c2,O_RDONLY);
        read(fd2, &ed2, 4);
        close(fd2);
 
        fd3 = open(c3,O_RDONLY);
        read(fd3, &ed3, 4);
        close(fd3);
 
        fd4 = open(c4,O_RDONLY);
        read(fd4, &ed4, 4);
        close(fd4);
 

        str2 = (str2*2 + ed1 + ed2 + ed3 + ed4)/6;

        fd1 = open(c1,O_WRONLY);
        write(fd1, &str2, sizeof(str2));
        fd2 = open(c2,O_WRONLY);
        write(fd2, &str2, sizeof(str2));
        fd3 = open(c3,O_WRONLY);
        write(fd3, &str2, sizeof(str2));
        fd4 = open(c4,O_WRONLY);
        write(fd4, &str2, sizeof(str2));
        
        close(fd1);
        close(fd2);
        close(fd3);
        close(fd4);
    }
    return 0;
}