#include <time.h>

/*
 * compilation: gcc time_mine.c -lrt
 * */

struct timespec start, end, temp;


struct timespec diff(struct timespec start, struct timespec end) {
        if ((end.tv_nsec - start.tv_nsec) < 0) {
                temp.tv_sec = end.tv_sec - start.tv_sec - 1;
                temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
        } else 
        {
                temp.tv_sec = end.tv_sec - start.tv_sec;
                temp.tv_nsec = end.tv_nsec - start.tv_nsec;
        }
        return temp;
}

int main() {
	while(1) {
            clock_gettime(CLOCK_REALTIME, &start);
			clock_gettime(CLOCK_REALTIME, &end);
			struct timespec d = diff(start, end);
			printf("%lld.%.9ld \n", (long long)d.tv_sec, d.tv_nsec);
		}
}
