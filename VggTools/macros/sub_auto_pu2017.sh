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

check=0
for L in $LISTS; do
  FILE_ELE=data/auto_pu2017/pileup_ele_`basename $L .list`.root
  FILE_MUO=data/auto_pu2017/pileup_muo_`basename $L .list`.root
  [ $L -ot $FILE_MUO ] && [ $L -ot $FILE_ELE ] && continue
  check=1
done

if [ $check -eq 0 ]; then
  echo
  echo "all pileup files are up-to-date"
  echo
  exit
fi

./compile.sh force

mkdir -p data/auto_pu2017

for L in $LISTS; do
  L=`basename $L .list`.list
  if [ ! -e lists/$L ]; then
    echo "ERROR: missing file "lists/$L
    continue
  fi
  bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_auto_pu2017.sh lists/$L
done

exit
