#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv) {
    int fd = open("./f", O_RDWR);
    if(fd < 0) {
        printf("error while opening file");
        exit(0);
    }

    int size = write(fd ,"1", 1);

    if(size < 0) {
        printf("error writting on file: %d\n",size);
        exit(0);
    }
    
}
