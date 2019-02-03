#!/bin/sh

QUEUE=normal
export USE_LSF_STARTER=no

EXCLUDED_HOSTS=""
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm003 && hname!=farm004 && hname!=farm005 && hname!=farm006 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm019 && hname!=farm020 && hname!=farm021 && hname!=farm022 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm045 && hname!=farm046 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm025 && hname!=farm026 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm073 && hname!=farm074 && hname!=farm075 && hname!=farm076 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm061 && hname!=farm062 && hname!=farm063 && hname!=farm064"

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

LISTS=`ls lists/ | grep RunIIFall17NanoAOD`

./compile.sh auto_pu2017

mkdir -p data/auto_pu2017

check=0
for L in $LISTS; do
  L=`basename $L .list`.list
  if [ ! -e lists/$L ]; then
    echo "ERROR: missing file "lists/$L
    continue
  fi
  FILE_ELE=data/auto_pu2017/pileup_ele_`basename $L .list`.root
  if [ ! -e $FILE_ELE ] || [ lists/$L -ot $FILE_ELE ]; then
    bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_auto_pu2017.sh lists/$L $FILE_ELE
    check=1
  fi
  FILE_MUO=data/auto_pu2017/pileup_muo_`basename $L .list`.root
  if [ ! -e $FILE_MUO ] || [ $L -ot $FILE_MUO ]; then
    bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_auto_pu2017.sh lists/$L $FILE_MUO
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
