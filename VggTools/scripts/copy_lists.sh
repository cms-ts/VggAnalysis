#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

LISTS=`ls lists/`

for L in $LISTS; do
  [ -z "${L##*DoubleEG_22Aug2018*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*DoubleMuon_22Aug2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*SingleElectron_22Aug2018*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*SingleMuon_22Aug2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*MuonEG_22Aug2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*DoubleEG_31Mar2018*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*DoubleMuon_31Mar2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*SingleElectron_31Mar2018*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*SingleMuon_31Mar2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*MuonEG_31Mar2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*EGamma_14Sep2018*}"         ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*DoubleMuon_14Sep2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*SingleMuon_14Sep2018*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*MuonEG_14Sep2018*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*RunIISummer16*}"            ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*RunIIFall17*}"              ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*RunIIFall18*}"              ] && cp -p lists/$L ../macros/lists/
done

exit
