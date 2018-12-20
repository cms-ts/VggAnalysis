#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

LISTS=`ls lists/`

for L in $LISTS; do
  [ -z "${L##*Run2016[A-Z]_DoubleEG*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016[A-Z]_DoubleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016[A-Z]_SingleElectron*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016[A-Z]_SingleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2016[A-Z]_MuonEG*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*Run2017[A-Z]_DoubleEG*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017[A-Z]_DoubleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017[A-Z]_SingleElectron*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017[A-Z]_SingleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2017[A-Z]_MuonEG*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*Run2018[A-Z]_EGamma*}"         ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2018[A-Z]_DoubleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2018[A-Z]_SingleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*Run2018[A-Z]_MuonEG*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in $LISTS; do
  [ -z "${L##*RunIISummer16*}"            ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*RunIIFall17*}"              ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*RunIIFall18*}"              ] && cp -p lists/$L ../macros/lists/
  [ -z "${L##*RunIIAutumn18*}"            ] && cp -p lists/$L ../macros/lists/
done

exit
