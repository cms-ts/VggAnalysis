#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

export ROOT_HIST=0

OPTION="kcO"

if [ ! -z "$1" ]; then
  OPTION="kcOf"
fi

root-6.12 -l -q -b compile.C\(\"mainSelectorDT16.C\",\"$OPTION\"\)
root-6.12 -l -q -b compile.C\(\"mainSelectorDT16H.C\",\"$OPTION\"\)
root-6.12 -l -q -b compile.C\(\"mainSelectorMC16.C\",\"$OPTION\"\)

root-6.12 -l -q -b compile.C\(\"mainSelectorDT17.C\",\"$OPTION\"\)
root-6.12 -l -q -b compile.C\(\"mainSelectorDT17B.C\",\"$OPTION\"\)
root-6.12 -l -q -b compile.C\(\"mainSelectorMC17.C\",\"$OPTION\"\)

root-6.12 -l -q -b compile.C\(\"mainSelectorDT18.C\",\"$OPTION\"\)
root-6.12 -l -q -b compile.C\(\"mainSelectorMC18.C\",\"$OPTION\"\)

root-6.12 -l -q -b compile.C\(\"plot0.C\",\"$OPTION\"\)
root-6.12 -l -q -b compile.C\(\"plot1.C\",\"$OPTION\"\)
root-6.12 -l -q -b compile.C\(\"plot2.C\",\"$OPTION\"\)
root-6.12 -l -q -b compile.C\(\"plot3.C\",\"$OPTION\"\)

#g++ -O2 -pthread -std=c++1z -m64 -I$ROOTSYS/include -L$ROOTSYS/lib \
#-lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad \
#-lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore \
#-lThread -lMultiProc -pthread -lm -ldl -rdynamic -lASImage plot0.C -o plot0.exe

#g++ -O2 -pthread -std=c++1z -m64 -I$ROOTSYS/include -L$ROOTSYS/lib \
#-lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad \
#-lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore \
#-lThread -lMultiProc -pthread -lm -ldl -rdynamic -lASImage plot1.C -o plot1.exe

#g++ -O2 -pthread -std=c++1z -m64 -I$ROOTSYS/include -L$ROOTSYS/lib \
#-lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad \
#-lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore \
#-lThread -lMultiProc -pthread -lm -ldl -rdynamic -lASImage plot2.C -o plot2.exe

#g++ -O2 -pthread -std=c++1z -m64 -I$ROOTSYS/include -L$ROOTSYS/lib \
#-lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad \
#-lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore \
#-lThread -lMultiProc -pthread -lm -ldl -rdynamic -lASImage plot3.C -o plot3.exe

exit
