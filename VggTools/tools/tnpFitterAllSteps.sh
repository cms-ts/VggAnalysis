#!/bin/bash

cd $HOME/work/cms/CMSSW_9_4_0/
eval `scramv1 runtime -sh`
source src/egm_tnp_analysis/etc/scripts/setup94.sh
PYTHONPATH=$PYTHONPATH:$PWD/src/egm_tnp_analysis
cd $OLDPWD

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/tools
cd $WORKDIR

PYTHONPATH=$PYTHONPATH:$WORKDIR

YEAR="2016"

if [ ! -z "$1" ]; then
  YEAR=$1
fi

FLAGS="passingMedium94X passingHLT"

for F in $FLAGS; do

  python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $F --createBins
  python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $F --createHists
  python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $F --doFit
  python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $F --doFit --mcSig --altSig
  python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $F --doFit --altSig
  python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $F --doFit --altBkg
  python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $F --sumUp

done

exit
