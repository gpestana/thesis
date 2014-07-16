#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv) {

//enable sensors
int MEM_ENABLER = open("/...", O_RDWR);
int A7_ENABLER = open("/...", O_RDWR);
int A15_ENABLER = open("/...", O_RDWR);

if(write(MEM_ENABLER, "1\n", 1) < 0) {
    printf("error enabling device");
    exit(0);
}

if(write(A7_ENABLER, "1\n", 1)  < 0) {
    printf("error enabling device");
    exit(0);
}

if(write(A15_ENABLER, "1\n", 1) < 0) {
    printf("error enabling device");
    exit(0);
}


while(true) {
    //read sensors
    
    //sleep
    
    //read sensors

    //print    

}


}
