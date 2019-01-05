#!/bin/sh

cd /home/$USER/work/cms/CMSSW_10_2_9/
eval `scramv1 runtime -sh`
cd $OLDPWD

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

echo "preparing pileup file for RunIISummer16"
python create_mc_pileup_2016.py 
echo "preparing pileup file for RunIIFall17"
python create_mc_pileup_2017.py 
echo "preparing pileup file for RunIIFall18"
python create_mc_pileup_2018.py 

exit
