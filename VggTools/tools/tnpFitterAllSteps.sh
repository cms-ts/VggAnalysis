#!/bin/bash

cd $HOME/work/cms/CMSSW_9_4_0/
eval `scramv1 runtime -sh`
source src/egm_tnp_analysis/etc/scripts/setup94.sh
cd $OLDPWD

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/tools
cd $WORKDIR

PYTHONPATH=$PYTHONPATH:$WORKDIR

FLAGS="passingMedium94X HLTpath"

for F in $FLAGS; do
    echo $F
    python /home/darold/work/CMSSW_9_4_0/src/egm_tnp_analysis/tnpEGM_fitter.py  settings_ele_2016.py --flag $F --createBins
    python /home/darold/work/CMSSW_9_4_0/src/egm_tnp_analysis/tnpEGM_fitter.py  settings_ele_2016.py --flag $F --createHists
    python /home/darold/work/CMSSW_9_4_0/src/egm_tnp_analysis/tnpEGM_fitter.py  settings_ele_2016.py --flag $F --doFit
    python /home/darold/work/CMSSW_9_4_0/src/egm_tnp_analysis/tnpEGM_fitter.py  settings_ele_2016.py --flag $F --doFit --mcSig --altSig
    python /home/darold/work/CMSSW_9_4_0/src/egm_tnp_analysis/tnpEGM_fitter.py  settings_ele_2016.py --flag $F --doFit --altSig
    python /home/darold/work/CMSSW_9_4_0/src/egm_tnp_analysis/tnpEGM_fitter.py  settings_ele_2016.py --flag $F --doFit --altBkg
    python /home/darold/work/CMSSW_9_4_0/src/egm_tnp_analysis/tnpEGM_fitter.py  settings_ele_2016.py --flag $F --sumUp
done

exit
