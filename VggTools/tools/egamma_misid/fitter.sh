#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/tools/egamma_misid
cd $WORKDIR

NUMBERS="1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20"

YEAR=$1

ISQCD=$2

FITFUNC=$3

SYST=$4

if [ -z "$1" ]; then
  echo "ERROR: missing year !!"
  exit
fi
if [ -z "$2" ]; then
  ISQCD=false
  echo "Will analyse signal region."
fi
if [ -z "$3" ]; then
  FITFUNC="CB"
  echo "Will fit with Crystal Ball."
fi
if [ -z "$4" ]; then
  SYST="reference"
  echo "Will analyse the reference."
fi

if [ ! -d "../../macros/html/egamma_v5" ]; then
  mkdir ../../macros/html/egamma_v5
fi
if [ ! -d "../../macros/html/egamma_v5/$SYST" ]; then
  mkdir ../../macros/html/egamma_v5/$SYST
fi
if [ ! -d "../../macros/html/egamma_v5/$SYST/plot" ]; then
  mkdir ../../macros/html/egamma_v5/$SYST/plot
fi

if $ISQCD; then
  rm ${SYST}/sf_data_${FITFUNC}_qcd_${YEAR}.txt 
  rm ${SYST}/sf_xsec_${FITFUNC}_qcd_${YEAR}.txt 
else
  rm ${SYST}/sf_data_${FITFUNC}_${YEAR}.txt 
  rm ${SYST}/sf_xsec_${FITFUNC}_${YEAR}.txt 
fi

for NUMBER in $NUMBERS; do

   root.exe -l -q -b fitter${FITFUNC}.C+\($NUMBER,$YEAR,$ISQCD,\"$SYST\"\)

done

root.exe -l -q -b draw.C\($YEAR,$ISQCD,\"data\",\"$FITFUNC\",\"$SYST\"\)
root.exe -l -q -b draw.C\($YEAR,$ISQCD,\"xsec\",\"$FITFUNC\",\"$SYST\"\)

exit
