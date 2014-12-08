#!/bin/sh
ntmin=1
ntmax=24
nevtst=100
nt=$ntmin
#measure pedestal
export NEVTS=$nevtst
export NT=1

time taskset -c 1 ParFullCMS bench1.g4 $nt 2>&1 >> log_1.txt
time taskset -c 1 ParFullCMS bench1.g4 $nt 2>&1 >> log_1.txt
while [ $nt -le $ntmax ];do
  nevts=$(( $nevtst * $nt ))
  echo "Number of events: "$nevts" Number of threads: "$nt
  export NEVTS=$nevts
  export NT=$nt
  touch log_${nt}.txt
  if [ $nt -eq 1 ];then
     time taskset -c 1 ParFullCMS bench1.g4 $nt 2>&1 >> log_${nt}.txt
  elif [ $nt -eq $ntmax ];then
     time taskset -c 0-$(( $nt - 1 )) ParFullCMS bench1.g4 $nt 2>&1 >> log_${nt}.txt
  else
     time taskset -c 1-$nt ParFullCMS bench1.g4 $nt 2>&1 >> log_${nt}.txt 
  fi
  nt=$(( $nt + 1 ))
done

