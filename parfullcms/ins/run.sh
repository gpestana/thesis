#!/bin/bash
source bin/geant4.sh
export LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH
cd ParFullCMS
export G4FORCENUMBEROFTHREADS=max
echo "Running ParFullCMS with macro file mt.g4 in directory: "$PWD
ParFullCMS mt.g4

