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

#FLAG="passingMedium94X"
FLAG="passingHLT"

python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $FLAG --createBins
python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $FLAG --createHists
python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $FLAG --doFit
python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $FLAG --doFit --mcSig --altSig
python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $FLAG --doFit --altSig
python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $FLAG --doFit --altBkg
python tnpEGM_fitter.py settings_ele_$YEAR.py --flag $FLAG --sumUp

exit
