#!/bin/sh

export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH
# pip install --install-option="--prefix=$HOME/.local" brilws

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for F in `ls json/Run2016*.json | grep 14Dec2018`; do
  echo "checking $F"
  G=`basename $F .json`
  echo $G > logs/$G.log
  brilcalc lumi \
  -b "STABLE BEAMS" \
  -c /cvmfs/cms.cern.ch/SITECONF/local/JobConfig/site-local-config.xml \
  --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json \
  -u /fb -i $F >> logs/$G.log
  grep -A 5 Summary logs/$G.log | grep [0-9] | awk '{print "lumi = "$12" /fb"}'
done

for F in `ls json/Run2017*.json | grep 14Dec2018`; do
  echo "checking $F"
  G=`basename $F .json`
  echo $G > logs/$G.log
  brilcalc lumi \
  -b "STABLE BEAMS" \
  -c /cvmfs/cms.cern.ch/SITECONF/local/JobConfig/site-local-config.xml \
  --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json \
  -u /fb -i $F >> logs/$G.log
  grep -A 5 Summary logs/$G.log | grep [0-9] | awk '{print "lumi = "$12" /fb"}'
done

# FIXME: to be updated using 'PHYSICS' normtag when available

for F in `ls json/Run2018*.json | grep 14Dec2018`; do
  echo "checking $F"
  G=`basename $F .json`
  echo $G > logs/$G.log
  brilcalc lumi \
  -b "STABLE BEAMS" \
  -c /cvmfs/cms.cern.ch/SITECONF/local/JobConfig/site-local-config.xml \
  --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PREAPPROVED.json \
  -u /fb -i $F >> logs/$G.log
  grep -A 5 Summary logs/$G.log | grep [0-9] | awk '{print "lumi = "$12" /fb"}'
done

exit
