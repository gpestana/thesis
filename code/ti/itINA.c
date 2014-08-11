#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv) {

int MEM_ENABLER = open("/sys/bus/i2c/drivers/INA231/4-0044/enable", O_RDWR);
int A7_ENABLER = open("/sys/bus/i2c/drivers/INA231/4-0045/enable", O_RDWR);
int A15_ENABLER = open("/sys/bus/i2c/drivers/INA231/4-0040/enable", O_RDWR);
int res;

FILE *MEM_fp;
FILE *A7_fp;
FILE *A15_fp;

char *buffer;

if(res = write(MEM_ENABLER, "1\n", 1) < 0) {
    printf("error enabling device MEM: %d\n",res);
    exit(0);
}

if(res = write(A7_ENABLER, "1\n", 1)  < 0) {
    printf("error enabling device A7: %d\n",res);
    exit(0);
}

if(res = write(A15_ENABLER, "1\n", 1) < 0) {
    printf("error enabling device A15: %d\n",res);
    exit(0);
}

while(1) {
MEM_fp = fopen("/sys/bus/i2c/drivers/INA231/4-0044/sensor_W", "r");    
fgets(buffer, 100, MEM_fp);
printf("%s", buffer);
fclose(MEM_fp);

A7_fp = fopen("/sys/bus/i2c/drivers/INA231/4-0045/sensor_W", "r");    
fgets(buffer, 100, A7_fp);
printf("%s", buffer);
fclose(A7_fp);

A15_fp = fopen("/sys/bus/i2c/drivers/INA231/4-0040/sensor_W", "r");    
fgets(buffer, 100, A15_fp);
printf("%s", buffer);
fclose(A15_fp);

sleep(1);
}
}

