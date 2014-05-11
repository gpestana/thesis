#!/bin/bash

#$1 config file name
#$2 estimate time to run

dir="$(date +'%d.%H%M')"

mkdir -p $dir

sudo perf record -a -o $dir/perf_record.log &
pid_perf=$!
echo 'perf record running with '$pid_perf

sudo perf stat -a -r $2 sleep 1 &

#sudo -u time cmsRun $1
#time $1

sudo kill -2 $pid_perf
echo 'done'
