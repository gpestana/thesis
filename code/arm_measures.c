
/* Linux */
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>

/* Unix */
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

struct sigaction sigact;
int hid_fd;

struct minfo {
 float watt;
 float amps;
 float volts;
 float wattph;
};

struct minfo make_minfo(unsigned char * raw) {
 struct minfo ret;
 ret.volts = strtof(raw + 2, NULL);
 ret.amps = strtof(raw + 10, NULL);
 ret.watt = strtof(raw + 17, NULL);
 ret.wattph = strtof(raw + 25, NULL);
 return ret;
}

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

int switch_meter(void) {
 unsigned char buf[65];
 memset(buf, 0x00, sizeof(buf));
 buf[0] = 0x00;
 buf[1] = 0x80;
 return write(hid_fd, buf, sizeof(buf));
}

static void signal_handler(int sig) {
 if (sig == SIGINT) {
   switch_meter();
   exit(0);
 }
 if (sig == SIGTERM) {
   switch_meter();
   exit(0);
 }
}

static void cleanup(void) {
 sigemptyset(&sigact.sa_mask);
}

void init_signals(void) {
 sigact.sa_handler = signal_handler;
 sigemptyset(&sigact.sa_mask);
 sigact.sa_flags = 0;
 sigaction(SIGINT, &sigact, (struct sigaction *)NULL);
 sigaction(SIGTERM, &sigact, (struct sigaction *)NULL);
};

int main(int argc, char **argv) {
 int res;
 int i;
 FILE *fp_stat;
 unsigned char buf[65];
 struct minfo mret;
 struct timeval timestamp_now;
 struct timeval timestamp_last;
 double sleeptime;
 long u_sleeptime;
 unsigned long long old[4], cur[4];
 double cpuutil = 0.;

 atexit(cleanup);
 init_signals();

 //gettimeofday(&timestamp_last, 0);

 hid_fd = open("/dev/hidraw0", O_RDWR); /* O_NONBLOCK */
 if (hid_fd < 1) {
   perror("Unable to open device");
   return 1;
 }

 if (argc == 2 && strcmp(argv[1], "switch") == 0) {
   if (switch_meter() < 0) {
     perror("Failed start/stop measuring power consumption");
     return 1;
   }
   return 0;
 }

 // Enable power consumption counting
 if (switch_meter() < 0) {
   perror("Failed starting power consumption counting");
   return 1;
 }

 while(1) {
   gettimeofday(&timestamp_last, 0);

   fp_stat = fopen("/proc/stat", "r");
   if (fp_stat == NULL) {
     perror("Failed to open /proc/stat");
   }

   fscanf(fp_stat, "%*s %llu %llu %llu %llu", &cur[0], &cur[1], &cur[2], &cur[3]);
   fclose(fp_stat);

   for (i = 0; i < 4; i++) {
     cur[i] = cur[i] - old[i];
   }
   cpuutil = 100. - (cur[3] * 100. / (cur[0] + cur[1] + cur[2] + cur[3]));

   memset(buf, 0x00, sizeof(buf));
   buf[0] = 0x00;
   buf[1] = 0x37;

   res = write(hid_fd, buf, sizeof(buf));
   if (res < 0) {
     perror("Failed to send fetch command");
     return 1;
   }
   /* usleep(1000); on O_NONBLOCK */
   res = read(hid_fd, buf, sizeof(buf));
   if (res < 0) {
     perror("Failed to read measurement");
     return 1;
   }

   mret = make_minfo(buf);
   printf("%.3fV %.3fA %.3fW %.3fWh %f\n", mret.volts, mret.amps, mret.watt, mret.wattph, cpuutil);

   fp_stat = fopen("/proc/stat", "r");
   if (fp_stat == NULL) {
     perror("Failed to open /proc/stat");
   }
   fscanf(fp_stat, "%*s %llu %llu %llu %llu", &old[0], &old[1], &old[2], &old[3]);
   fclose(fp_stat);
   gettimeofday(&timestamp_now, 0);
   sleeptime = difftime(timestamp_now.tv_sec, timestamp_last.tv_sec);
   u_sleeptime = abs(timestamp_now.tv_usec - timestamp_last.tv_usec);

   sleeptime = 1.0 - sleeptime - (u_sleeptime * 1e-6);
   //printf("%.6f\n", sleeptime);
   //printf("%d\n", u_sleeptime);

   lsleep(sleeptime);
 }
 return 0;
}
