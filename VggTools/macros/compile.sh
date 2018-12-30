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

make_lib() {
  FILES=$1
  for F in $FILES; do
    root-6.12 -l -b -q -e 'cout << "Compiling '$F' ..." << endl ; gSystem->Exit(gSystem->CompileMacro("'$F'","'$OPTION'"))'
  done
}

make_lib "mainSelectorDT16.C mainSelectorDT16H.C mainSelectorMC16.C"
make_lib "mainSelectorDT17.C mainSelectorDT17B.C mainSelectorMC17.C"
make_lib "mainSelectorDT18.C mainSelectorMC18.C"
make_lib "plot0.C plot1.C plot2.C plot3.C"

make_exe() {
  FILES=$1
  for F in $FILES; do
    echo ""
    echo "Compiling $F ..."
    g++ -O2 -pthread -std=c++1z -m64 -I$ROOTSYS/include -L$ROOTSYS/lib \
        -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad \
        -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore \
        -lThread -lMultiProc -pthread -lm -ldl -rdynamic -lASImage $F -o `basename $F .C`.exe
  done
}

# make_exe "plot0.C plot1.C plot2.C plot3.C"

exit
