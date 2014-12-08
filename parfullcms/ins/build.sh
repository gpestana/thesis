#!/bin/sh

usage()
{
cat << EOF
usage $0 options
options:
  -h : show this help
  -s : use static libraries
  -t type : set value of CMAKE_BUILD_TYPE option
  -o prefix : output prefix
  -c [gcc|icc|clang] : compiler family
  -f flags : extra compiler flags
  -i tarball : copy specified source installation tarball
  -x : build Xerces-C
  -m : build CMake
  -D : extra CMake options (can be used more than once)
  -j : number of parallel jobs for compilation
EOF
}

#defaults
cpsrc=0
gbasedir=$(dirname $0)
basedir=$(cd $gbasedir > /dev/null ; pwd )
CXX=g++
CC=gcc
COMPILER=gcc
TCXXFLAGS=""
SHARED=1
TYPE=RelWithDebInfo
OUTPUTDIR=x86_64-slc6
bcm=0
bxc=0
pkgs=2
extracmake=""
parj=`grep "processor" /proc/cpuinfo | tail -n1 | awk '{print $3};'`

while getopts "hst:o:c:f:i:xm:j:D:" OPTION

do
     case $OPTION in
         D)
             extracmake="${extracmake} -D${OPTARG}"
	     ;;
         h)
             usage
             exit 1
             ;;
         t)
             TYPE=$OPTARG
             ;;
         s)
	     SHARED=0
	     ;;
         o)
	     OUTPUTDIR=$OPTARG
	     ;;
         c)
             if [ $OPTARG == "gcc" ];then
		export CXX=g++
		export CC=gcc
	     elif [ $OPTARG == "icc" ];then
                COMPILER=icc
		export CXX=icpc
	        export CC=icc
             elif [ $OPTARG == "clang" ];then
	        COMPILER=clang
	        export CXX=clang++
	        export CC=clang
             else
                #Assume gcc variant
                COMPILER=gcc
                export CXX=$OPTARG
                export CC=$OPTARG
             fi
	     ;;
         i)
             cpsrc=1
             src=$OPTARG
             ;;
         f)
             TCXXFLAGS=$OPTARG
	     ;;
         x)
             bxc=1
             pkgs=$(( $pkgs + 1 ))
             ;;
         m)
             bcm=1
             pkgs=$(( $pkgs + 1 ))
             ;;
         j)
	     parj=$OPTARG
	     ;;
     esac
done

#Guess compilerversion
cver=`$CXX --version | cut -d" " -f3 | head -n1 | sed s/"\."//g `
OUTPUTDIR=${OUTPUTDIR}-${COMPILER}-${cver}-${TYPE}
[ $SHARED -eq 0 ] && OUTPUTDIR=${OUTPUTDIR}-static
instarea=${basedir}/${OUTPUTDIR}

echo "Compiler family: "$COMPILER
echo "Shared LIB Option: "$SHARED
echo "Build Type: "$TYPE
echo "Installation Directory: "$instarea

if [ "x"$TCXXFLAGS != "x" ];then 
   export CXXFLAGS="${CXXFLAGS} $TCXXFLAGS "
   export CFLAGS="${CFLAGS} $TCXXFLAGS "
   echo "extra CXX/C Flags: ->"$CXXFLAGS"<->"$CFLAGS"<-"
fi 
mkdir -p ${instarea}
cd $instarea
if [ $cpsrc -eq 1 ];then 
   tar xzf ${src} 
fi

touch compilation.log
pkg=1

#Compile cmake
if [ $bcm -eq 1 ];then
	cd cmake-*
 	echo "[$pkg/$pkgs] Compiling CMake logfile: compilation.log"
	./bootstrap --prefix=$instarea >> ../compilation.log 2>&1
	make -j ${parj} >> ../compilation.log 2>&1
        make install >> ../compilation.log 2>&1
        echo "cmake done"
        pkg=$(( $pkg + 1 ))
        cmakebin=${instarea}/bin/cmake
        cd ..
else
        cmakebin=cmake
fi

#Compile Xercesx-C
if [ $bxc -eq 1 ]; then
	cd xerces*
        echo "[$pkg/$pkgs] Compiling Xerces-C logfile: compilation.log"
	xopts=" --prefix=${instarea} "
	[ $SHARED -eq 0 ] && xopts=" --disable-shared --disable-netaccessor-curl "$xopts
	./configure ${xopts} >> ../compilation.log 2>&1
        make -j ${parj} >> ../compilation.log 2>&1
        make install >> ../compilation.log 2>&1
        echo "xerces-c done"
        pkg=$(( $pkg + 1 ))
        cd ..
fi

#Compile G4
mkdir -p build-G4
cd build-G4
xopts=" -DGEANT4_BUILD_MULTITHREADED=ON -DCMAKE_INSTALL_PREFIX=${instarea} -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_GDML=ON -DXERCESC_ROOT_DIR=${instarea} -DGEANT4_USE_SYSTEM_EXPAT=OFF "
xopts="${xopts} -DCMAKE_BUILD_TYPE=$TYPE "
if [ $SHARED -eq 0 ];then
  xopts="${xopts} -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON "
else
  xopts="${xopts} -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF "
fi
if [ "x"$TCXXFLAGS != "x" ];then
   xopts="${xopts} -DCMAKE_CXX_FLAGS=\"$CXXFLAGS\" -DCMAKE_C_FLAGS=\"$CFLAGS\" "
fi
xopts="${xopts} -DCMAKE_CXX_COMPILER=$CXX -DCMAKE_C_COMPILER=$CC "
if [ "x$extracmake" != "x" ];then 
   xopts="${xopts} ${extracmake} "
fi
echo "CMake options: "$xopts

echo "[$pkg/$pkgs] Compiling Geant4 logfile: compilation.log"
$cmakebin ${xopts} ../geant4-* >> ../compilation.log 2>&1 
make -j ${parj} VERBOSE=1 >> ../compilation.log 2>&1
make install >> ../compilation.log 2>&1
echo "G4 done"
pkg=$(( $pkg + 1 ))
cd ..

#Compile Application
mkdir -p build-CMS
cd build-CMS
xopts=" -DCMAKE_INSTALL_PREFIX=${instarea} -DGeant4_DIR=${instarea}/lib*/Geant4-* -DCMAKE_BUILD_TYPE=$TYPE "
if [ $SHARED -eq 0 ];then
  xopts="${xopts} -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON "
else
  xopts="${xopts} -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF "
fi
if [ "x"$TCXXFLAGS != "x" ];then
   xopts="${xopts} -DCMAKE_CXX_FLAGS=\"$CXXFLAGS\" -DCMAKE_C_FLAGS=\"$CFLAGS\" "
fi
xopts="${xopts} -DCMAKE_CXX_COMPILER=$CXX -DCMAKE_C_COMPILER=$CC "
echo "[$pkg/$pkgs] Compiling application logfile: compilation.log"
$cmakebin ${xopts} ../ParFullCMS >> ../compilation.log 2>&1 
make -j ${parj} VERBOSE=1 >> ../compilation.log 2>&1 
make install >> ../compilation.log 2>&1
echo "Application done"
cd ..
