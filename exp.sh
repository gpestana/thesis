#!/bin/bash

#how to use:
#	1) init python in cmssw environment
#	2) run a random sudo command
#	3) ./exp.sh <config_file path/name> <exp_seconds>

#input:
#	$1 config file name
#	$2 name for folder (optional)
#	$3 time for benchmarking 

dir="$(date +'%d.%H%M')"'_'$2

mkdir -p out/$dir
echo 'input: '$1' '$2'' >> out/$dir/cmd 

#top
top -d 1 -b > out/$dir/top.log &
pid_top=$!
echo 'top running with '$pid_top
#perf record
sudo perf record -a -o out/$dir/perf_record.log &
pid_perf=$!
echo 'perf record running with '$pid_perf

# >baseline
#  >CPU
#stress --cpu 4 --timeout $3 &
#  >mem
#stress --vm 4 --timeout $3 &

# >experiment 
#echo '-----------'
#time cmsRun $1 &
#echo '-----------'

#new perf stat
stress --cpu 1 --timeout $3 &
track=$!

while true
do
	if ps -p $track > /dev/null 2>&1; then
		ps v >> out/$dir/ps.out
		(sudo perf stat -a sleep 1) >>  out/$dir/perf_stat.out 2>&1
	else
		echo 'master process is done'
		break
	fi
	sleep 5
done

sudo kill -2 $pid_top;
echo 'top killed';
sudo kill -2 $pid_perf;
echo 'perf killed';
echo '-----'
echo 'done. check ./out/'$dir'
echo '-----'
exit
