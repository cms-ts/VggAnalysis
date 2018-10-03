#!/bin/sh

cd /home/$USER/work/cms/CMSSW_9_4_9/
eval `scramv1 runtime -sh`
cd - > /dev/null

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

for F in `ls json/Run2016_*.json`; do

  echo "preparing pileup file for "`basename $F .json`

  if [ -z "${F##*Run2016*05Feb2018*}" ]; then
    P='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt'
  fi

  if [ -z "${F##*Run2016*22Aug2018*}" ]; then
    P='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt'
  fi

  if [ -z "${F##*Run2031*31Mar2018*}" ]; then
    P='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PileUp/pileup_latest.txt'
  fi

  if [ -z "${F##*Run2018*14Sep2018*}" ]; then
    P='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PileUp/pileup_latest.txt'
  fi

  pileupCalc.py -i $F \
                --inputLumiJSON $P \
                --calcMode true --minBiasXsec 69200 \
                --maxPileupBin 100 --numPileupBins 100 pileup/`basename $F .json`.root

done

exit
