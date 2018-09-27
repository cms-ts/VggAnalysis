#!/bin/sh

WORKDIR=/home/dellaric/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

for F in `ls lumi/Run2016*.lumi | grep Run2016[A-Z]`; do
  G=`basename $F .lumi`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

echo

for F in `ls lumi/Run2017*.lumi | grep Run2017[A-Z]_`; do
  G=`basename $F .lumi`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

echo

for F in `ls lumi/Run2016*.lumi | grep -v Run2016[A-Z]_`; do
  G=`basename $F .lumi`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

echo

for F in `ls lumi/Run2017*.lumi | grep -v Run2017[A-Z]_`; do
  G=`basename $F .lumi`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

exit
