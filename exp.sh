#!/bin/bash

#how to use:
#	1) init python in cmssw environment
#	2) run a random sudo command
#	3) ./exp.sh <config_file path/name> <exp_seconds>

#input:
#	$1 config file name
#	$2 estimate time to run
#	$3 name for folder (optional)

dir="$(date +'%d.%H%M')"'_'$3

mkdir -p out/$dir
echo 'input: '$1' '$2' '$3 >> out/$dir/cmd 

#top
top -d 1 -b > out/$dir/top.log &
pid_top=$!
echo 'top running with '$pid_top
#perf record
sudo perf record -a -o out/$dir/perf_record.log &
pid_perf=$!
echo 'perf record running with '$pid_perf
#perf stat
sudo perf stat -a -r $2 sleep 1 &

# >baseline
#  >CPU
stress --cpu 4 --timeout $2;
#  >mem
#stress --vm 4 --timeout $2

# >experiment 
echo '-----------'
time cmsRun $1;
echo '-----------'

sudo kill -2 $pid_top;
echo 'top killed';
sudo kill -2 $pid_perf;
echo 'perf killed';
exit
