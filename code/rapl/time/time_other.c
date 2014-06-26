#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
 
#define M_INTERVAL 1
 
int lsleep(double time) {
 struct timespec ts;
 ts.tv_sec = (time_t)time;
 ts.tv_nsec = (long)((time - ts.tv_sec) * 1e+9);
 while (1) {
   int rval = nanosleep(&ts, &ts);
   if (rval == 0) {
     return 0;
   } else if (errno == EINTR) {
     continue;
   } else {
     return rval;
   }
 }
}
 
int main(int argc, char **argv) {
  FILE *fp_stat;
  unsigned long long old[4], cur[4];
  double cpuutil = 0.;
  struct timeval timestamp_now;
  struct timeval timestamp_last;
  long u_sleeptime;
  double sleeptime;
  int i;
 
  while (1) {
    /* Get time */
    gettimeofday(&timestamp_last, 0);
 
    fp_stat = fopen("/proc/stat", "r");
    if (fp_stat == NULL) {
      perror("Failed to open /proc/stat");
    }
 
    fscanf(fp_stat, "%*s %llu %llu %llu %llu", &cur[0], &cur[1], &cur[2], &cur[3]);
    fclose(fp_stat);
 
    /* Calculate CPU utilization */
    for (i = 0; i < 4; i++) {
      cur[i] = cur[i] - old[i];
    }
    cpuutil = 100. - (cur[3] * 100. / (cur[0] + cur[1] + cur[2] + cur[3]));
 
    printf("%f\n", cpuutil);
 
    /* Get CPU utilization */
    fp_stat = fopen("/proc/stat", "r");
    if (fp_stat == NULL) {
      perror("Failed to open /proc/stat");
    }
    fscanf(fp_stat, "%*s %llu %llu %llu %llu", &old[0], &old[1], &old[2], &old[3]);
    fclose(fp_stat);
 
    /* Calculate sleep time */
    gettimeofday(&timestamp_now, 0);
    sleeptime = difftime(timestamp_now.tv_sec, timestamp_last.tv_sec);
    u_sleeptime = abs(timestamp_now.tv_usec - timestamp_last.tv_usec);
    sleeptime = M_INTERVAL - sleeptime - (u_sleeptime * 1e-6);
    lsleep(sleeptime);
  }
 
  return 0;
}