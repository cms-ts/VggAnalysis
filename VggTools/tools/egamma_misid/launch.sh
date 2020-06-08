#!/bin/sh

if [ -r $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0 ]; then
  cd $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/tools/egamma_misid
cd $WORKDIR

YEARS="2016 2017 2018"

SYST="reference"

mkdir -p ../../macros/html/egamma_v6/$SYST
mkdir -p ../../macros/html/egamma_v6/$SYST/plot

for YEAR in $YEARS; do
  ./fitter.sh $YEAR false TP $SYST &
  ./fitter.sh $YEAR true TP $SYST &
done

wait

for YEAR in $YEARS; do
  ./fitter.sh $YEAR false DCB $SYST &
  ./fitter.sh $YEAR true DCB $SYST &
done

wait

for YEAR in $YEARS; do
  root-6.12 -l -b -q compare.C\($YEAR,false,\"data\",\"$SYST\",\"TP\",\"DCB\"\)
  root-6.12 -l -b -q compare.C\($YEAR,true,\"data\",\"$SYST\",\"TP\",\"DCB\"\)
done
