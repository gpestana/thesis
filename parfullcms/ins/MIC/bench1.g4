#
#/random/resetEngineFrom start.rndm
#
/control/getEnv NT
/control/getEnv NEVTS
/run/numberOfThreads {NT} 
/run/verbose 1 
/event/verbose 0 
/tracking/verbose 0
#
#/mydet/setField 4.0 tesla
#
/run/beamOn {NEVTS}
