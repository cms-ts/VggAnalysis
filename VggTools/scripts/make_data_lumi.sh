#!/bin/sh

export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH
# pip install --install-option="--prefix=$HOME/.local" brilws

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

for F in `ls logs/Run2016*.json`; do
  echo "checking $F"
  G=`basename $F .json`
  echo $G > logs/$G.lumi
  brilcalc lumi \
  -c /cvmfs/cms.cern.ch/SITECONF/local/JobConfig/site-local-config.xml \
  --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json \
  -u /fb -i $F >> logs/$G.lumi
  grep -A 5 Summary logs/$G.lumi | grep [0-9] | awk '{print "lumi = "$12" /fb"}'
done

for F in `ls logs/Run2017*.json`; do
  echo "checking $F"
  G=`basename $F .json`
  echo $G > logs/$G.lumi
  brilcalc lumi \
  -c /cvmfs/cms.cern.ch/SITECONF/local/JobConfig/site-local-config.xml \
  --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json \
  -u /fb -i $F >> logs/$G.lumi
  grep -A 5 Summary logs/$G.lumi | grep [0-9] | awk '{print "lumi = "$12" /fb"}'
done

# FIXME: to be updated using 'PHYSICS' normtag when available

for F in `ls logs/Run2018*.json`; do
  echo "checking $F"
  G=`basename $F .json`
  echo $G > logs/$G.lumi
  brilcalc lumi \
  -c /cvmfs/cms.cern.ch/SITECONF/local/JobConfig/site-local-config.xml \
  --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json \
  -u /fb -i $F >> logs/$G.lumi
  grep -A 5 Summary logs/$G.lumi | grep [0-9] | awk '{print "lumi = "$12" /fb"}'
done

exit
