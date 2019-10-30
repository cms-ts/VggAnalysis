#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

FLAGS="kcO"

if [ ! -z "$1" ]; then
  FLAGS="kcOf"
  if [ "$1" == "mainSelector" ] || [ "$1" == "auto_pu" ] || [ "$1" == "plot" ]; then
    OPTION="$1"
  else
    OPTION="force"
  fi
fi

export ROOT_HIST=0

make_lib() {
  FILES=$1
  for F in $FILES; do
    root.exe -l -b -q -e 'cout << "Checking '$F' ..." << endl ; gSystem->Exit(gSystem->CompileMacro("'$F'","'$FLAGS'"))'
  done
}

if [ -z "$OPTION" ] || [ "$OPTION" == "force" ] || [ "$OPTION" == "mainSelector" ]; then
  make_lib "mainSelectorDT16.C mainSelectorMC16.C"
  make_lib "mainSelectorDT17.C mainSelectorMC17.C"
  make_lib "mainSelectorDT18.C mainSelectorMC18.C"
fi

if [ -z "$OPTION" ] || [ "$OPTION" == "force" ] || [ "$OPTION" == "auto_pu" ]; then
  make_lib "auto_pu.C"
fi

if [ -z "$OPTION" ] || [ "$OPTION" == "force" ] || [ "$OPTION" == "plot" ]; then
  make_lib "plot0.C plot1.C plot2.C plot3.C plot4.C plot5.C plot6.C"
fi

exit

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

make_exe "auto_pu.C"
make_exe "plot0.C plot1.C plot2.C plot3.C plot4.C plot5.C plot6.C"

exit
