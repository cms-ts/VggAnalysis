#!/bin/sh

QUEUE=normal_io
export USE_LSF_STARTER=no

EXCLUDED_GROUPS="ts-acid_hg cfarmts_hg"

for GROUP in $EXCLUDED_GROUPS; do
  for HOST in `bmgroup -r $GROUP`; do
    if [ -z "${HOST##*farm0*}" ]; then
      EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=$HOST "
    fi
  done
done

EXCLUDED_HOSTS=`echo $EXCLUDED_HOSTS | sed -e 's/ / \&\& /g'`

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/skim
cd $WORKDIR

DATADIR=/eos/infnts/cms/store/data

for F in `eos find -f $DATADIR/ | grep Run2016 | grep NANOAOD | grep 02Apr2020`; do
  if [ -s $F ]; then
    if [ ! -e logs/`basename $F .root`_Skim.log ]; then
      touch logs/`basename $F .root`_Skim.log
      eos mkdir -p `dirname $F | sed -e 's;data;user/dellaric/data;'`
      bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -e /dev/null -o /dev/null job_data_skim.sh $F
    fi
  fi
done

for F in `eos find -f $DATADIR/ | grep Run2017 | grep NANOAOD | grep 02Apr2020`; do
  if [ -s $F ]; then
    if [ ! -e logs/`basename $F .root`_Skim.log ]; then
      touch logs/`basename $F .root`_Skim.log
      eos mkdir -p `dirname $F | sed -e 's;data;user/dellaric/data;'`
      bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -e /dev/null -o /dev/null job_data_skim.sh $F
    fi
  fi
done

for F in `eos find -f $DATADIR/ | grep Run2018 | grep NANOAOD | grep 02Apr2020`; do
  if [ -s $F ]; then
    if [ ! -e logs/`basename $F .root`_Skim.log ]; then
      touch logs/`basename $F .root`_Skim.log
      eos mkdir -p `dirname $F | sed -e 's;data;user/dellaric/data;'`
      bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -e /dev/null -o /dev/null job_data_skim.sh $F
    fi
  fi
done

exit
