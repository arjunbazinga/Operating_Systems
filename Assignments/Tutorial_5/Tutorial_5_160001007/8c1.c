#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    char * myfifo = "/tmp/c1";
    mkfifo(myfifo, 0666);
    int a=7, b=200,pr=-1;
    while (b != pr){
        fd = open(myfifo, O_WRONLY);
        pr = b;
        b = (b*3 + 2*a)/5;
        write(fd, &b, sizeof(b));
        close(fd);
        fd = open(myfifo, O_RDONLY);
        read(fd, &a, sizeof(a));
        printf("%d\n", a);
        close(fd);
    }
    return 0;
}