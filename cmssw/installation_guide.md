### CMSSW installation
- - -

This guide is intended to install CMSSW 6.2.0 framework.


> This guide worked a for:
> **Ditro: ** [Scientific Linux][1] release 6.5 (Carbon) x86 [Linux ws-152 3.11.0-19-generic x86_64 GNU/Linux] 
> **CPU**: Intel Atom & Intel Core2 Quad



**1. Pre-installation** *(if not installed by default)*

i) sudo yum install gcc; sudo yum install tcl; sudo yum install tk; sudo yum install compat-readline5; sudo yum install perl-ExtUtils-Embed; sudo yum install zsh; sudo yum install compat-libstdc++; sudo yum install libXpm;


ii) Install also the following packages *(not included in yum repos by default)*
mesa-libGLU-xx, mesa-libGLU-devel-xx, libXpm-xx, libXpm-devel-xx, zlib-devel-xx


**2. Set apt-get env and download framework**

i) Download prepare_installare.sh: https://twiki.cern.ch/twiki/pub/Main/CMSUniandesGroupLaptop/prepare_installarea.sh

ii) change SCRAM_ARCH to SCRAM_ARCH=slc6_amd64_gcc472 in prepare_installare.sh

iii) source prepare_installarea.sh *install_dir* (create desired *install_dir* beforehand)


iv) Download set-aptget-env.sh: https://twiki.cern.ch/twiki/pub/Main/CMSUniandesGroupLaptop/set-aptget-env.sh

v) change SCRAM_ARCH to SCRAM_ARCH=slc6_amd64_gcc472 in set-aptget-env.sh

vi) change export VO_CMS_SW_DIR to VO_CMS_SW_DIR=*install_dir*

vii) change source \$VO_CMS_SW_DIR/$SCRAM_ARCH/external/apt/*/etc/profile.d/init.sh
(How ? use find tool to search for “/external/apt/*/etc/profile.d/init.sh” in the *install_dir*)

vi) source set-aptget-env.sh

viii) apt-get update; apt-get install cms+cmssw+CMSSW_6_2_0


**3. PATHS**
Important: edit environment macros on .bashrc before compilation. Some of them will be useful during the compilation proccess.

```sh
#CMSSW
export CMSSW_SEARCH_PATH=<install_dir>/slc6_amd64_gcc472/cms/cmssw/CMSSW_6_2_0/src
export CMSSW_BASE=<install_dir>/slc6_amd64_gcc472/cms
export CMSSW_DATA_PATH=<install_dir>/slc6_amd64_gcc472/cms/cmssw/CMSSW_6_2_0/src

#SCRAM:
SCRAM_ARCH=slc6_amd64_gcc472; export SCRAM_ARCH
export PATH=$PATH:<install_dir>/slc6_amd64_gcc472/lcg/SCRAMV1/V2_2_5_pre3/bin/

#external GLIBCC
export LD_LIBRARY_PATH=<install_dir>/slc6_amd64_gcc472/external/gcc/4.7.2-cms/lib64:<install_dir>/workbench/cms/slc6_amd64_gcc472/cms/cmssw/CMSSW_6_2_0/lib/slc6_amd64_gcc472/

#External Python
export PYTHONPATH=<install_dir>/slc6_amd64_gcc472/cms/cmssw/CMSSW_6_2_0/python
export PYTHONHOME=<install_dir>/slc6_amd64_gcc472/external/python/2.7.3-cms5/
```

**4.Compilation**
i) cd *install_dir*/slc6_amd64_gcc472/cms/cmssw/CMSSW_6_2_0/
ii) scram build 

**5. cmsRun is ready to use**


Main documentation: 
https://twiki.cern.ch/twiki/bin/view/Main/CMSUniandesGroupLaptop#CMSSW_installation_on_your_lapto

Others:
https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuide
https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBook
https://github.com/cms-sw/cmssw/


  [1]: http://ftp1.scientificlinux.org/linux/scientific/6x/x86_64/iso/
