#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for F in `ls lists/Run2016*.list`; do
  [ -z "${F##*DoubleEG*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*DoubleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*SingleElectron*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*SingleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*MuonEG*}"         ] && cp -p lists/$L ../macros/lists/
done

for F in `ls lists/Run2017*.list`; do
  [ -z "${F##*DoubleEG*}"       ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*DoubleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*SingleElectron*}" ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*SingleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*MuonEG*}"         ] && cp -p lists/$L ../macros/lists/
done

for F in `ls lists/Run2018*.list`; do
  [ -z "${F##*EGamma*}"         ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*DoubleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*SingleMuon*}"     ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*MuonEG*}"         ] && cp -p lists/$L ../macros/lists/
done

for L in `ls lists/RunII*.list`; do
  [ -z "${F##*RunIISummer16*}"  ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*RunIIFall17*}"    ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*RunIIFall18*}"    ] && cp -p lists/$L ../macros/lists/
  [ -z "${F##*RunIIAutumn18*}"  ] && cp -p lists/$L ../macros/lists/
done

exit
