#!/bin/sh

DATADIR=/eos/infnts/cms/store/user/dellaric/data

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for D1 in `ls $DATADIR/ | grep Run2016`; do
  for D2 in `ls $DATADIR/$D1`; do
    find $DATADIR/$D1/$D2 -type f | grep 22Aug2018 | \
    awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/${D1}_${D2}_22Aug2018.list
  done
done

for D1 in `ls $DATADIR/ | grep Run2017`; do
  for D2 in `ls $DATADIR/$D1`; do
    find $DATADIR/$D1/$D2 -type f | grep 31Mar2018 | \
    awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/${D1}_${D2}_31Mar2018.list
  done
done

for D1 in `ls $DATADIR/ | grep Run2018`; do
  for D2 in `ls $DATADIR/$D1`; do
    find $DATADIR/$D1/$D2 -type f | grep 14Sep2018 | \
    awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/${D1}_${D2}_14Sep2018.list
  done
done

for D2 in `ls $DATADIR/Run2016C/`; do
  find $DATADIR/Run2016*/$D2 -type f | grep 22Aug2018 | \
  awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/Run2016_${D2}_22Aug2018.list
done

for D2 in `ls $DATADIR/Run2017C/`; do
  find $DATADIR/Run2017*/$D2 -type f | grep 31Mar2018 | \
  awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/Run2017_${D2}_31Mar2018.list
done

for D2 in `ls $DATADIR/Run2018C/`; do
  find $DATADIR/Run2018*/$D2 -type f | grep 14Sep2018 | \
  awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/Run2018_${D2}_14Sep2018.list
done

for D1 in `ls $DATADIR/ | grep Run2016`; do
  for D2 in `ls $DATADIR/$D1`; do
    find $DATADIR/$D1/$D2 -type f | grep 14Dec2018 | \
    awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/`echo $D1 | sed -e 's/_ver1//;s/_ver2//'`_${D2}_14Dec2018.list
  done
done

for D1 in `ls $DATADIR/ | grep Run2017`; do
  for D2 in `ls $DATADIR/$D1`; do
    find $DATADIR/$D1/$D2 -type f | grep 14Dec2018 | \
    awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/${D1}_${D2}_14Dec2018.list
  done
done

for D1 in `ls $DATADIR/ | grep Run2018`; do
  for D2 in `ls $DATADIR/$D1`; do
    find $DATADIR/$D1/$D2 -type f | grep 14Dec2018 | \
    awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/${D1}_${D2}_14Dec2018.list
  done
done

for D2 in `ls $DATADIR/Run2016C/`; do
  find $DATADIR/Run2016*/$D2 -type f | grep 14Dec2018 | \
  awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/Run2016_${D2}_14Dec2018.list
done

for D2 in `ls $DATADIR/Run2017C/`; do
  find $DATADIR/Run2017*/$D2 -type f | grep 14Dec2018 | \
  awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/Run2017_${D2}_14Dec2018.list
done

for D2 in `ls $DATADIR/Run2018C/`; do
  find $DATADIR/Run2018*/$D2 -type f | grep 14Dec2018 | \
  awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/Run2018_${D2}_14Dec2018.list
done

DATADIR=/eos/infnts/cms/store/mc

for D1 in `ls $DATADIR/ | grep RunII.*NanoAOD`; do
  for D2 in `ls $DATADIR/$D1`; do
    find $DATADIR/$D1/$D2 -type f | \
    awk '{print "root://eosinfnts.ts.infn.it/"$1}' > lists/${D1}_${D2}.list
  done
done

exit
