#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/tools/
cd $WORKDIR

FLAGS="kcO"

if [ ! -z "$1" ]; then
  FLAGS="kcOf"
  if [ "$1" == "treeMaker" ]; then
    OPTION="$1"
  else
    OPTION="force"
  fi
fi

export ROOT_HIST=0

make_lib() {
  FILES=$1
  for F in $FILES; do
    root-6.12 -l -b -q -e 'cout << "Checking '$F' ..." << endl ; gSystem->Exit(gSystem->CompileMacro("'$F'","'$FLAGS'"))'
  done
}

if [ -z "$OPTION" ] || [ "$OPTION" == "force" ] || [ "$OPTION" == "treeMaker" ]; then
  make_lib "treeMakerDT16.C treeMakerDT16H.C treeMakerMC16.C"
  make_lib "treeMakerDT17.C treeMakerDT17B.C treeMakerMC17.C"
  make_lib "treeMakerDT18.C treeMakerMC18.C"
fi

exit