#!/bin/sh
ntmin=16
ntmax=1
nevtst=100
nt=$ntmin
#measure pedestal
export NEVTS=$nevtst
export NT=1
touch log_1.txt
time ParFullCMS bench1.g4 $nt 2>&1 >> log_1.txt
time ParFullCMS bench1.g4 $nt 2>&1 >> log_1.txt
time ParFullCMS bench1.g4 $nt 2>&1 >> log_1.txt
while [ $nt -ge $ntmax ];do
  nevts=$(( $nevtst * $nt ))
  echo "Number of events: "$nevts" Number of threads: "$nt
  export NEVTS=$nevts
  export NT=$nt
  touch log_${nt}.txt
  time ParFullCMS bench1.g4 $nt 2>&1 >> log_${nt}.txt
  nt=$(( $nt - 1 ))
done

