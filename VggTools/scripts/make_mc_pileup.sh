#!/bin/sh

cd $CMS_PATH/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_2_0/
eval `scramv1 runtime -sh`
cd - > /dev/null

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

echo "preparing pileup file for RunIISummer16"
python create_mc_pileup_2016.py 
echo "preparing pileup file for RunIIFall17"
python create_mc_pileup_2017.py 
echo "preparing pileup file for RunIIFall18"
python create_mc_pileup_2018.py 

exit
