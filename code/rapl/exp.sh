#!/bin/bash

./rapl > out &
rapl=$!

time cmsRun MinBias_8TeV_pythia8_cff_GEN_SIM.py &
#stress --cpu 1 --timeout 15 &
track=$!

while true
do
	if ps -p $track > /dev/null 2>&1; then
		sleep 2
	else
		break
	fi
	sleep 2
done

sudo kill -9 $rapl;
echo 'done';
exit

