#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for F in `ls root/ratio_pileup_*.root | grep Run2016 | grep 1June2019`; do
  [ -z "${F##*SingleElectron*}" ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon*}"     ] && cp -p $F ../macros/root/
done

for F in `ls root/ratio_pileup_*.root | grep Run2017 | grep 1June2019`; do
  [ -z "${F##*SingleElectron*}" ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon*}"     ] && cp -p $F ../macros/root/
done

for F in `ls root/ratio_pileup_*.root | grep Run2018 | grep 1June2019`; do
  [ -z "${F##*EGamma*}"         ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon*}"     ] && cp -p $F ../macros/root/
done

exit
