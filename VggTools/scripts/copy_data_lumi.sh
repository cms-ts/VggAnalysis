#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

rm -f ../macros/lumi.dat

for F in `ls logs/Run2016*.log | grep 1June2019`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  [ -z "${F##*DoubleEG*}"       ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*DoubleMuon*}"     ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleElectron*}" ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleMuon*}"     ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
done

for F in `ls logs/Run2017*.log | grep 1June2019`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  [ -z "${F##*DoubleEG*}"       ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*DoubleMuon*}"     ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleElectron*}" ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleMuon*}"     ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
done

for F in `ls logs/Run2018*.log | grep 1June2019`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  [ -z "${F##*EGamma*}"         ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*DoubleMuon*}"     ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleMuon*}"     ] && printf "%-40s%6.3f\n" $G $L >> ../macros/lumi.dat
done

exit
