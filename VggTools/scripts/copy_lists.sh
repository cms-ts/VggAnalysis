#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for F in `ls lists/Run2016[A-Z]*.list`; do
  [ -z "${F##*DoubleEG*}"       ] && cp -p $F ../macros/lists/
  [ -z "${F##*DoubleMuon*}"     ] && cp -p $F ../macros/lists/
  [ -z "${F##*SingleElectron*}" ] && cp -p $F ../macros/lists/
  [ -z "${F##*SingleMuon*}"     ] && cp -p $F ../macros/lists/
  [ -z "${F##*MuonEG*}"         ] && cp -p $F ../macros/lists/
done

for F in `ls lists/Run2017[A-Z]*.list`; do
  [ -z "${F##*DoubleEG*}"       ] && cp -p $F ../macros/lists/
  [ -z "${F##*DoubleMuon*}"     ] && cp -p $F ../macros/lists/
  [ -z "${F##*SingleElectron*}" ] && cp -p $F ../macros/lists/
  [ -z "${F##*SingleMuon*}"     ] && cp -p $F ../macros/lists/
  [ -z "${F##*MuonEG*}"         ] && cp -p $F ../macros/lists/
done

for F in `ls lists/Run2018[A-Z]*.list`; do
  [ -z "${F##*EGamma*}"         ] && cp -p $F ../macros/lists/
  [ -z "${F##*DoubleMuon*}"     ] && cp -p $F ../macros/lists/
  [ -z "${F##*SingleMuon*}"     ] && cp -p $F ../macros/lists/
  [ -z "${F##*MuonEG*}"         ] && cp -p $F ../macros/lists/
done

for F in `ls lists/RunII*.list`; do
  [ -z "${F##*RunIISummer16*}"  ] && cp -p $F ../macros/lists/
  [ -z "${F##*RunIIFall17*}"    ] && cp -p $F ../macros/lists/
  [ -z "${F##*RunIIFall18*}"    ] && cp -p $F ../macros/lists/
  [ -z "${F##*RunIIAutumn18*}"  ] && cp -p $F ../macros/lists/
done

exit
