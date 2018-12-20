#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

for F in `ls root/ratio_pileup_Run2016_*`; do
  [ -z "${F##*DoubleEG_14Dec2018*}"       ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon_14Dec2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleElectron_14Dec2018*}" ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon_14Dec2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG_14Dec2018*}"         ] && cp -p $F ../macros/root/
done

for F in `ls root/ratio_pileup_Run2017_*`; do
  [ -z "${F##*DoubleEG_14Dec2018*}"       ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon_14Dec2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleElectron_14Dec2018*}" ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon_14Dec2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG_14Dec2018*}"         ] && cp -p $F ../macros/root/
done

for F in `ls root/ratio_pileup_Run2018_*`; do
  [ -z "${F##*EGamma_14Dec2018*}"         ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon_14Dec2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon_14Dec2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG_14Dec2018*}"         ] && cp -p $F ../macros/root/
done

exit
