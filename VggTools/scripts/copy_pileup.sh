#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for F in `ls root/ratio_pileup_Run2016_* | grep 14Dec2018`; do
  [ -z "${F##*DoubleEG*}"       ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleElectron*}" ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG*}"         ] && cp -p $F ../macros/root/
done

for F in `ls root/ratio_pileup_Run2017_* | grep 14Dec2018`; do
  [ -z "${F##*DoubleEG*}"       ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleElectron*}" ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG*}"         ] && cp -p $F ../macros/root/
done

for F in `ls root/ratio_pileup_Run2018_* | grep 14Dec2018`; do
  [ -z "${F##*EGamma*}"         ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG*}"         ] && cp -p $F ../macros/root/
done

exit
