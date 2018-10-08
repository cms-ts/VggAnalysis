#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

rm -f ../macros/lumi.dat

for F in `ls logs/*.log`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  [ -z "${F##*DoubleEG_05Feb2018*}"       ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*DoubleMuon_05Feb2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleElectron_05Feb2018*}" ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleMuon_05Feb2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*MuonEG_05Feb2018*}"         ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
done

for F in `ls logs/*.log`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  [ -z "${F##*DoubleEG_22Aug2018*}"       ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*DoubleMuon_22Aug2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleElectron_22Aug2018*}" ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleMuon_22Aug2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*MuonEG_22Aug2018*}"         ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
done

for F in `ls logs/*.log`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  [ -z "${F##*DoubleEG_31Mar2018*}"       ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*DoubleMuon_31Mar2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleElectron_31Mar2018*}" ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleMuon_31Mar2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*MuonEG_31Mar2018*}"         ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
done

for F in `ls logs/*.log`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  [ -z "${F##*EGamma_14Sep2018*}"         ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*DoubleMuon_14Sep2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*SingleMuon_14Sep2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${F##*MuonEG_14Sep2018*}"         ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
done

exit
