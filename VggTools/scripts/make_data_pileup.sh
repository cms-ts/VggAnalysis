#!/bin/sh

cd $HOME/work/cms/CMSSW_10_2_22/
eval `scramv1 runtime -sh`
cd $OLDPWD

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for F in `ls json/Run2016_*.json | grep 02Apr2020`; do
  echo "preparing pileup file for "`basename $F .json`
  pileupCalc.py -i $F \
                --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt \
                --calcMode true --minBiasXsec 69200 \
                --maxPileupBin 100 --numPileupBins 100 root/pileup_`basename $F .json`.root
  pileupCalc.py -i $F \
                --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt \
                --calcMode true --minBiasXsec 72400 \
                --maxPileupBin 100 --numPileupBins 100 root/pileup_up_`basename $F .json`.root
  pileupCalc.py -i $F \
                --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt \
                --calcMode true --minBiasXsec 66000 \
                --maxPileupBin 100 --numPileupBins 100 root/pileup_down_`basename $F .json`.root
done

for F in `ls json/Run2017_*.json | grep 02Apr2020`; do
  echo "preparing pileup file for "`basename $F .json`
  pileupCalc.py -i $F \
                --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PileUp/pileup_latest.txt \
                --calcMode true --minBiasXsec 69200 \
                --maxPileupBin 100 --numPileupBins 100 root/pileup_`basename $F .json`.root
  pileupCalc.py -i $F \
                --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PileUp/pileup_latest.txt \
                --calcMode true --minBiasXsec 72400 \
                --maxPileupBin 100 --numPileupBins 100 root/pileup_up_`basename $F .json`.root
  pileupCalc.py -i $F \
                --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PileUp/pileup_latest.txt \
                --calcMode true --minBiasXsec 66000 \
                --maxPileupBin 100 --numPileupBins 100 root/pileup_down_`basename $F .json`.root
done

for F in `ls json/Run2018_*.json | grep 02Apr2020`; do
  echo "preparing pileup file for "`basename $F .json`
  pileupCalc.py -i $F \
                --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PileUp/pileup_latest.txt \
                --calcMode true --minBiasXsec 69200 \
                --maxPileupBin 100 --numPileupBins 100 root/pileup_`basename $F .json`.root
  pileupCalc.py -i $F \
                --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PileUp/pileup_latest.txt \
                --calcMode true --minBiasXsec 72400 \
                --maxPileupBin 100 --numPileupBins 100 root/pileup_up_`basename $F .json`.root
  pileupCalc.py -i $F \
                --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PileUp/pileup_latest.txt \
                --calcMode true --minBiasXsec 66000 \
                --maxPileupBin 100 --numPileupBins 100 root/pileup_down_`basename $F .json`.root
done

exit
