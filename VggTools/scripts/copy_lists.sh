#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

LISTS=`ls lists/`

for L in $LISTS; do
  [ -z "${L##*Run2016_DoubleEG_05Feb2018*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016_DoubleMuon_05Feb2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016_SingleElectron_05Feb2018*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016_SingleMuon_05Feb2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016_MuonEG_05Feb2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*Run2016_DoubleEG_22Aug2018*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016_DoubleMuon_22Aug2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016_SingleElectron_22Aug2018*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016_SingleMuon_22Aug2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016_MuonEG_22Aug2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*Run2017_DoubleEG_31Mar2018*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017_DoubleMuon_31Mar2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017_SingleElectron_31Mar2018*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017_SingleMuon_31Mar2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017_MuonEG_31Mar2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*Run2018_EGamma_14Sep2018*}"         ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2018_DoubleMuon_14Sep2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2018_SingleMuon_14Sep2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2018_MuonEG_14Sep2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*RunIISummer16*}"            ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*RunIIFall17*}"              ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*RunIIFall18*}"              ] && cp -p lists/$L ../macros/lists/
done

exit
