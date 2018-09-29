#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

rm -f ../macros/lumi.dat

for F in `ls logs/*.lumi`; do
  G=`basename $F .lumi`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  [ -z "${L##*DoubleEG_22Aug2018*}"       ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*DoubleMuon_22Aug2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*SingleElectron_22Aug2018*}" ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*SingleMuon_22Aug2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*MuonEG_22Aug2018*}"         ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
done

for F in `ls logs/*.lumi`; do
  G=`basename $F .lumi`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  [ -z "${L##*DoubleEG_31Mar2018*}"       ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*DoubleMuon_31Mar2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*SingleElectron_31Mar2018*}" ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*SingleMuon_31Mar2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*MuonEG_31Mar2018*}"         ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
done

for F in `ls logs/*.lumi`; do
  [ -z "${L##*DoubleEG_14Sep2018*}"       ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*DoubleMuon_14Sep2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*SingleElectron_14Sep2018*}" ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*SingleMuon_14Sep2018*}"     ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*MuonEG_14Sep2018*}"         ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
done

for F in `ls logs/*.lumi`; do
  [ -z "${L##*RunIISummer16*}"            ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*RunIIFall17*}"              ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
  [ -z "${L##*RunIIFall18*}"              ] && printf "%s\t%6.3f\n" $G $L >> ../macros/lumi.dat
done

exit
