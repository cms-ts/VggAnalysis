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

VERSION="v04"

if [ ! -z "$1" ]; then
  VERSION=$1
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

mkdir -p data/$VERSION

LISTS=`ls lists/`

if [ ! -z "$2" ]; then
  if [ "$2" == "DT16" ]; then
    LISTS=`ls lists/ | grep Run2016`
  elif [ "$2" == "DT17" ]; then
    LISTS=`ls lists/ | grep Run2017`
  elif [ "$2" == "DT18" ]; then
    LISTS=`ls lists/ | grep Run2018`
  elif [ "$2" == "MC16" ]; then
    LISTS=`ls lists/ | grep RunIISummer16NanoAOD`
  elif [ "$2" == "MC17" ]; then
    LISTS=`ls lists/ | grep RunIIFall17NanoAOD`
  elif [ "$2" == "MC18" ]; then
    LISTS=`ls lists/ | grep 'RunIIFall18NanoAOD\|RunIIAutumn18NanoAOD'`
  elif [ "$2" == "2016" ]; then
    LISTS=`ls lists/ | grep 'Run2016\|RunIISummer16NanoAOD'`
  elif [ "$2" == "2017" ]; then
    LISTS=`ls lists/ | grep 'Run2017\|RunIIFall17NanoAOD'`
  elif [ "$2" == "2018" ]; then
    LISTS=`ls lists/ | grep 'Run2018\|RunIIFall18NanoAOD\|RunIIAutumn18NanoAOD'`
  else
    LISTS=$2
  fi
fi

./compile.sh force

for L in $LISTS; do
  L=`basename $L .list`.list
  if [ ! -e lists/$L ]; then
    echo "ERROR: missing file "lists/$L
    continue
  fi
  bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_selector.sh $VERSION lists/$L
done

exit
