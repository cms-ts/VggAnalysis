#!/bin/sh

cd /home/$USER/work/cms/CMSSW_10_2_9/
eval `scramv1 runtime -sh`
cd $OLDPWD

DATADIR=/eos/infnts/cms/store/user/dellaric/data

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for D1 in `ls $DATADIR/ | grep Run2016`; do
  for D2 in `ls $DATADIR/$D1`; do
    N=`find $DATADIR/$D1/$D2 -type f | grep 14Dec2018 | wc -l`
    echo "checking ${D1}/${D2} - $N files"
    python nano_report.py -o json/${D1}_${D2}_14Dec2018.json \
    `find $DATADIR/$D1/$D2 -type f | grep 14Dec2018`
  done
done

for D1 in `ls $DATADIR/ | grep Run2017`; do
  for D2 in `ls $DATADIR/$D1`; do
    N=`find $DATADIR/$D1/$D2 -type f | grep 14Dec2018 | wc -l`
    echo "checking ${D1}/${D2} - $N files"
    python nano_report.py -o json/${D1}_${D2}_14Dec2018.json \
    `find $DATADIR/$D1/$D2 -type f | grep 14Dec2018`
  done
done

for D1 in `ls $DATADIR/ | grep Run2018`; do
  for D2 in `ls $DATADIR/$D1`; do
    N=`find $DATADIR/$D1/$D2 -type f | grep 14Dec2018 | wc -l`
    echo "checking ${D1}/${D2} - $N files"
    python nano_report.py -o json/${D1}_${D2}_14Dec2018.json \
    `find $DATADIR/$D1/$D2 -type f | grep 14Dec2018`
  done
done

for D2 in `ls $DATADIR/Run2016B/`; do
  N=`find $DATADIR/Run2016*/$D2 -type f | grep 14Dec2018 | wc -l`
  echo "checking Run2016/${D2} - $N files"
  python nano_report.py -o json/Run2016_${D2}_14Dec2018.json \
  `find $DATADIR/Run2016*/$D2 -type f | grep 14Dec2018`
done

for D2 in `ls $DATADIR/Run2017B/`; do
  N=`find $DATADIR/Run2017*/$D2 -type f | grep 14Dec2018 | wc -l`
  echo "checking Run2017/${D2} - $N files"
  python nano_report.py -o json/Run2017_${D2}_14Dec2018.json \
  `find $DATADIR/Run2017*/$D2 -type f | grep 14Dec2018`
done

for D2 in `ls $DATADIR/Run2018B/`; do
  N=`find $DATADIR/Run2018*/$D2 -type f | grep 14Dec2018 | wc -l`
  echo "checking Run2018/${D2} - $N files"
  python nano_report.py -o json/Run2018_${D2}_14Dec2018.json \
  `find $DATADIR/Run2018*/$D2 -type f | grep 14Dec2018`
done

exit
