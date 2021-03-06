#!/bin/sh

cd $HOME/work/cms/CMSSW_10_2_22/
eval `scramv1 runtime -sh`
cd $OLDPWD

DATADIR=/eos/infnts/cms/store/user/dellaric/data

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

for F in `ls lists/Run2016*.list | grep 02Apr2020`; do
  echo "checking $F - "`cat $F | wc -l`" files"
  python nano_report.py -o json/`basename $F .list`.json \
  `cat $F | sed -e 's;root://eosinfnts.ts.infn.it/;;'`
done

for F in `ls lists/Run2017*.list | grep 02Apr2020`; do
  echo "checking $F - "`cat $F | wc -l`" files"
  python nano_report.py -o json/`basename $F .list`.json \
  `cat $F | sed -e 's;root://eosinfnts.ts.infn.it/;;'`
done

for F in `ls lists/Run2018*.list | grep 02Apr2020`; do
  echo "checking $F - "`cat $F | wc -l`" files"
  python nano_report.py -o json/`basename $F .list`.json \
  `cat $F | sed -e 's;root://eosinfnts.ts.infn.it/;;'`
done

exit
