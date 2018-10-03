#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

cp -p pileup/ratio_pileup_Run2016_DoubleEG_22Aug2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2016_DoubleMuon_22Aug2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2016_SingleElectron_22Aug2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2016_SingleMuon_22Aug2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2016_MuonEG_22Aug2018.root ../macros/root/

cp -p pileup/ratio_pileup_Run2017_DoubleEG_31Mar2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2017_DoubleMuon_31Mar2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2017_SingleElectron_31Mar2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2017_SingleMuon_31Mar2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2017_MuonEG_31Mar2018.root ../macros/root/

cp -p pileup/ratio_pileup_Run2018_EGamma_14Sep2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2018_DoubleMuon_14Sep2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2018_SingleMuon_14Sep2018.root ../macros/root/
cp -p pileup/ratio_pileup_Run2018_MuonEG_14Sep2018.root ../macros/root/


exit
