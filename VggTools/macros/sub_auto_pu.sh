#!/bin/sh

QUEUE=normal
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

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

LISTS=`ls lists/ | grep RunIIFall17NanoAOD`

alias SKIP=$SKIP

SKIP ./compile.sh auto_pu

mkdir -p data/auto_pu

check=0
for L in $LISTS; do
  L=`basename $L .list`.list
  if [ ! -e lists/$L ]; then
    echo "ERROR: missing file "lists/$L
    continue
  fi
  FILE_ELE=data/auto_pu/pileup_ele_`basename $L .list`.root
  if [ lists/$L -nt $FILE_ELE ]; then
    bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_auto_pu.sh lists/$L $FILE_ELE
    check=1
  fi
  FILE_ELE=data/auto_pu/pileup_ele_up_`basename $L .list`.root
  if [ lists/$L -nt $FILE_ELE ]; then
    bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_auto_pu.sh lists/$L $FILE_ELE
    check=1
  fi
  FILE_ELE=data/auto_pu/pileup_ele_down_`basename $L .list`.root
  if [ lists/$L -nt $FILE_ELE ]; then
    bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_auto_pu.sh lists/$L $FILE_ELE
    check=1
  fi
  FILE_MUO=data/auto_pu/pileup_muo_`basename $L .list`.root
  if [ lists/$L -nt $FILE_MUO ]; then
    bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_auto_pu.sh lists/$L $FILE_MUO
    check=1
  fi
  FILE_MUO=data/auto_pu/pileup_muo_up_`basename $L .list`.root
  if [ lists/$L -nt $FILE_MUO ]; then
    bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_auto_pu.sh lists/$L $FILE_MUO
    check=1
  fi
  FILE_MUO=data/auto_pu/pileup_muo_down_`basename $L .list`.root
  if [ lists/$L -nt $FILE_MUO ]; then
    bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_auto_pu.sh lists/$L $FILE_MUO
    check=1
  fi
done

if [ $check -eq 0 ]; then
  echo
  echo "all pileup files are up-to-date"
  echo
  exit
fi

exit
