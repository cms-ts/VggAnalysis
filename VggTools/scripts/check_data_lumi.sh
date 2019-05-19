#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for F in `ls logs/Run2016*.log | grep Run2016[A-Z]`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

echo

for F in `ls logs/Run2017*.log | grep Run2017[A-Z]_`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

echo

for F in `ls logs/Run2018*.log | grep Run2018[A-Z]_`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

echo

for F in `ls logs/Run2016*.log | grep -v Run2016[A-Z]_`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

echo

for F in `ls logs/Run2017*.log | grep -v Run2017[A-Z]_`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

echo

for F in `ls logs/Run2018*.log | grep -v Run2018[A-Z]_`; do
  G=`basename $F .log`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "dataset %-35s - lumi = %6.3f /fb\n" $G $L
done

exit
