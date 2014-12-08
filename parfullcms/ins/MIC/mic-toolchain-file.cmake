# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER /oplashare/sw/linux/x86_64/intel/xe2013/composer_xe_2013.1.117/bin/intel64/icc)
SET(CMAKE_CXX_COMPILER /oplashare/sw/linux/x86_64/intel/xe2013/composer_xe_2013.1.117/bin/intel64/icpc)
SET(CMAKE_LINKER /usr/linux-k1om-4.7/bin/x86_64-k1om-linux-ld)
SET(CMAKE_AR /usr/linux-k1om-4.7/bin/x86_64-k1om-linux-ar)
# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /oplashare/sw/linux/x86_64/intel/xe2013/composer_xe_2013.1.117)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
