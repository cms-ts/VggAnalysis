#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

LISTS=`ls lists/`

for L in $LISTS; do
  [ -z "${L##*Run2016[A-Z]_DoubleEG_22Aug2018*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016[A-Z]_DoubleMuon_22Aug2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016[A-Z]_SingleElectron_22Aug2018*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016[A-Z]_SingleMuon_22Aug2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016[A-Z]_MuonEG_22Aug2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*Run2017[A-Z]_DoubleEG_31Mar2018*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017[A-Z]_DoubleMuon_31Mar2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017[A-Z]_SingleElectron_31Mar2018*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017[A-Z]_SingleMuon_31Mar2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017[A-Z]_MuonEG_31Mar2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*Run2018[A-Z]_EGamma_14Sep2018*}"         ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2018[A-Z]_DoubleMuon_14Sep2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2018[A-Z]_SingleMuon_14Sep2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2018[A-Z]_MuonEG_14Sep2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*RunIISummer16*}"            ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*RunIIFall17*}"              ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*RunIIFall18*}"              ] && cp -p lists/$L ../macros/lists/
done

exit
