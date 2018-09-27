#!/bin/sh

QUEUE=normal
export USE_LSF_STARTER=no

DATADIR=/eos/infnts/cms/store/data
WORKDIR=/gpfs/cms/users/dellaric/tmp

cd $WORKDIR

for F in `eos find -f $DATADIR/ | grep Run2016 | grep NANOAOD | grep 05Feb2018`; do
  if [ -s $F ]; then
    if [ ! -e $WORKDIR/log/`basename $F .root`_Skim.log ]; then
      eos mkdir -p `dirname $F | sed -e 's;data;user/dellaric/data;'`
      bsub -q $QUEUE -e /dev/null -o /dev/null job_data_skim.sh $F
    fi
  fi
done

for F in `eos find -f $DATADIR/ | grep Run2016 | grep NANOAOD | grep 22Aug2018`; do
  if [ -s $F ]; then
    if [ ! -e $WORKDIR/log/`basename $F .root`_Skim.log ]; then
      eos mkdir -p `dirname $F | sed -e 's;data;user/dellaric/data;'`
      bsub -q $QUEUE -e /dev/null -o /dev/null job_data_skim.sh $F
    fi
  fi
done

for F in `eos find -f $DATADIR/ | grep Run2017 | grep NANOAOD | grep 31Mar2018`; do
  if [ -s $F ]; then
    if [ ! -e $WORKDIR/log/`basename $F .root`_Skim.log ]; then
      eos mkdir -p `dirname $F | sed -e 's;data;user/dellaric/data;'`
      bsub -q $QUEUE -e /dev/null -o /dev/null job_data_skim.sh $F
    fi
  fi
done

for F in `eos find -f $DATADIR/ | grep Run2018 | grep NANOAOD | grep 14Sep2018`; do
  if [ -s $F ]; then
    if [ ! -e $WORKDIR/log/`basename $F .root`_Skim.log ]; then
      eos mkdir -p `dirname $F | sed -e 's;data;user/dellaric/data;'`
      bsub -q $QUEUE -e /dev/null -o /dev/null job_data_skim.sh $F
    fi
  fi
done

exit
