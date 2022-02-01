#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

export PYTHONUSERBASE=$WORKDIR/.local
# pip install brilws
export PATH=$WORKDIR/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH

for F in `ls json/Run2016*.json | grep 02Apr2020`; do
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

for F in `ls json/Run2017*.json | grep 02Apr2020`; do
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

for F in `ls json/Run2018*.json | grep 02Apr2020`; do
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

exit
