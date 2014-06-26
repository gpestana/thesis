/* read RAPL registers on sandybridge machine				*/
/* /dev/cpu/--/msr 											*/
/* 															*/
/* --> compile with: gcc -O2 -Wall -o rapl rapl.c -lm 		*/
/*															*/
/* read msr registers each 0.001 seconds. 					*/
/* save data in binary 										*/
/* get power consumed by the different cpus					*/
/* (4cores, 38cpus)											*/
/* identify the packages of each cpu (package == 1|2|3|4)	*/
/* (checking here:/sys/devices/system/cpu/cpu0/topology)    */
/*															*/	
/* based on Vince Weave code 								*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define MSR_RAPL_POWER_UNIT			0x606

/* Package RAPL Domain */
#define MSR_PKG_RAPL_POWER_LIMIT	0x610
#define MSR_PKG_ENERGY_STATUS		0x611
#define MSR_PKG_PERF_STATUS			0x613
#define MSR_PKG_POWER_INFO			0x614

/* Package RAPL Domain */
#define MSR_PKG_RAPL_POWER_LIMIT  	0x610
#define MSR_PKG_ENERGY_STATUS   	0x611
#define MSR_PKG_PERF_STATUS   		0x613
#define MSR_PKG_POWER_INFO    		0x614

/* PP1 RAPL Domain, may reflect to uncore devices */
#define MSR_PP1_POWER_LIMIT			0x640
#define MSR_PP1_ENERGY_STATUS		0x641
#define MSR_PP1_POLICY				0x642

/* DRAM RAPL Domain */
#define MSR_DRAM_POWER_LIMIT		0x618
#define MSR_DRAM_ENERGY_STATUS		0x619
#define MSR_DRAM_PERF_STATUS		0x61B
#define MSR_DRAM_POWER_INFO			0x61C

/* RAPL UNIT BITMASK */
#define POWER_UNIT_OFFSET			0
#define POWER_UNIT_MASK				0x0F

#define ENERGY_UNIT_OFFSET			0x08
#define ENERGY_UNIT_MASK			0x1F00

#define TIME_UNIT_OFFSET			0x10
#define TIME_UNIT_MASK				0xF000


int open_msr(int core) {
	char msr_filename[BUFSIZ];
	int fd;
	sprintf(msr_filename, "/dev/cpu/%d/msr", core);
	fd = open(msr_filename, O_RDONLY);
	if(fd < 0) {
		if(errno == ENXIO) {
			fprintf(stderr, "rmdsr: No CPU %d\n",core);
			exit(2);
		} else if(errno == EIO) {
			fprintf(stderr, "rmdsr: CPU %d\n doesn't support MSRs\n", core);
			exit(3);
		} else {
			perror("rmdsr:open");
			fprintf(stderr, "Trying to open %s\n",msr_filename);
			exit(127);
		}
	}
	return fd;
}

long long read_msr(int fd, int which) {
	uint64_t data;
	if (pread(fd, &data, sizeof data, which) != data) {
		perror("rmdsr:pread");
		exit(127);
	}
	return (long long) data;
}

#define CPU_SANDYBRIDGE		42
#define CPU_SANDYBRIDGE_EP	45
#define CPU_IVYBRIDGE		58
#define CPU_IVYBRIDGE_EP	62
#define CPU_HASWELL			60

int detect_cpu(void) {

	FILE *fff;

	int family,model=-1;
	char buffer[BUFSIZ],*result;
	char vendor[BUFSIZ];

	fff=fopen("/proc/cpuinfo","r");
	if (fff==NULL) return -1;

	while(1) {
		result=fgets(buffer,BUFSIZ,fff);
		if (result==NULL) break;

		if (!strncmp(result,"vendor_id",8)) {
			sscanf(result,"%*s%*s%s",vendor);

			if (strncmp(vendor,"GenuineIntel",12)) {
				printf("%s not an Intel chip\n",vendor);
				return -1;
			}
		}

		if (!strncmp(result,"cpu family",10)) {
			sscanf(result,"%*s%*s%*s%d",&family);
			if (family!=6) {
				printf("Wrong CPU family %d\n",family);
				return -1;
			}
		}

		if (!strncmp(result,"model",5)) {
			sscanf(result,"%*s%*s%d",&model);
		}

	}

	fclose(fff);

	switch(model) {
		case CPU_SANDYBRIDGE:
			printf("Found Sandybridge CPU\n");
			break;
		case CPU_SANDYBRIDGE_EP:
			printf("Found Sandybridge-EP CPU\n");
			break;
		case CPU_IVYBRIDGE:
			printf("Found Ivybridge CPU\n");
			break;
		case CPU_IVYBRIDGE_EP:
			printf("Found Ivybridge-EP CPU\n");
			break;
		case CPU_HASWELL:
			printf("Found Haswell CPU\n");
			break;
		default:	printf("Unsupported model %d\n",model);
				model=-1;
				break;
	}

	return model;
}



int main(int argc, char **argv) {
 
  int fd;
  long long result;
  double power_units,energy_units,time_units;
  double package_before,package_after;
  double pp0_before,pp0_after;
  double pp1_before=0.0,pp1_after;
  double dram_before=0.0,dram_after;
  double thermal_spec_power,minimum_power,maximum_power,time_window;
  int cpu_model;
  int c;

  //should select all cores
  int core = 0;
 
  opterr=0;

  cpu_model=detect_cpu();
  if (cpu_model<0) {
	printf("Unsupported CPU type\n");
	return -1;
  }

    printf("core: #%d\n",core);
    fd = open_msr(core);

    result = read_msr(fd, MSR_RAPL_POWER_UNIT);

  power_units=pow(0.5,(double)(result&0xf));
  energy_units=pow(0.5,(double)((result>>8)&0x1f));
  time_units=pow(0.5,(double)((result>>16)&0xf));

  printf("Power units = %.3fW\n",power_units);
  printf("Energy units = %.8fJ\n",energy_units);
  printf("Time units = %.8fs\n",time_units);
  printf("\n");

	return 0;
}