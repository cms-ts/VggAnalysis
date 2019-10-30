#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/tools/egamma_misid
cd $WORKDIR

YEARS="2016 2017 2018"

for YEAR in $YEARS; do

  ./fitter.sh $YEAR false CB reference &
  ./fitter.sh $YEAR false BW reference &
  ./fitter.sh $YEAR false TP reference &
  
  ./fitter.sh $YEAR true CB reference &
  ./fitter.sh $YEAR true BW reference &
  ./fitter.sh $YEAR true TP reference &

done

wait

for YEAR in $YEARS; do

  root.exe -l -b -q compare.C\($YEAR,true,\"data\",\"reference\",\"CB\",\"BW\"\)
  root.exe -l -b -q compare.C\($YEAR,false,\"data\",\"reference\",\"CB\",\"BW\"\)

done
