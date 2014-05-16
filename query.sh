echo $(date +"%T");
ipmitool -H 192.168.0.28 -U admin -P admin -I lanplus sensor get 'Node Power';
ipmitool -H 192.168.0.10 -U admin -P admin -I lanplus sensor get 'Node Power';
ipmitool -H 192.168.0.29 -U admin -P admin -I lanplus sensor get 'Node Power';
ipmitool -H 192.168.0.30 -U admin -P admin -I lanplus sensor get 'Node Power';
ipmitool -H 192.168.0.31 -U admin -P admin -I lanplus sensor get 'Node Power';
ipmitool -H 192.168.0.32 -U admin -P admin -I lanplus sensor get 'Node Power';
ipmitool -H 192.168.0.33 -U admin -P admin -I lanplus sensor get 'Node Power';
ipmitool -H 192.168.0.34 -U admin -P admin -I lanplus sensor get 'Node Power';
echo '--'
ipmitool -H 192.168.0.28 -U admin -P admin -I lanplus sdr list all;
ipmitool -H 192.168.0.28 -U admin -P admin -I lanplus sdr list all;
ipmitool -H 192.168.0.28 -U admin -P admin -I lanplus sdr list all;
ipmitool -H 192.168.0.28 -U admin -P admin -I lanplus sdr list all;
ipmitool -H 192.168.0.28 -U admin -P admin -I lanplus sdr list all;
ipmitool -H 192.168.0.28 -U admin -P admin -I lanplus sdr list all;
ipmitool -H 192.168.0.28 -U admin -P admin -I lanplus sdr list all;
ipmitool -H 192.168.0.28 -U admin -P admin -I lanplus sdr list all;


