#!/bin/sh

NANOAODv6=`grep "#define NANOAODv6" mainSelector.h | head -1 | grep "^#define NANOAODv6"`
NANOAODv7=`grep "#define NANOAODv7" mainSelector.h | head -1 | grep "^#define NANOAODv7"`

[ ! -z "$NANOAODv6" ] && [ -z "$NANOAODv7" ] && echo && echo "Preparing to submit NANOAODv6" && echo
[ ! -z "$NANOAODv7" ] && [ -z "$NANOAODv6" ] && echo && echo "Preparing to submit NANOAODv7" && echo

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

VERSION="v00"

if [ ! -z "$1" ]; then
  VERSION=$1
fi

FLAGS="reference"

if [ ! -z "$2" ]; then
  if [ "$2" == "all" ]; then
    FLAGS=""
    FLAGS=$FLAGS" reference"
    FLAGS=$FLAGS" pileup_up"
    FLAGS=$FLAGS" pileup_down"
#    FLAGS=$FLAGS" jec_up_2016"
#    FLAGS=$FLAGS" jec_up_2017"
#    FLAGS=$FLAGS" jec_up_2018"
#    FLAGS=$FLAGS" jec_down_2016"
#    FLAGS=$FLAGS" jec_down_2017"
#    FLAGS=$FLAGS" jec_down_2018"
#    FLAGS=$FLAGS" jer_up_2016"
#    FLAGS=$FLAGS" jer_up_2017"
#    FLAGS=$FLAGS" jer_up_2018"
#    FLAGS=$FLAGS" jer_down_2016"
#    FLAGS=$FLAGS" jer_down_2017"
#    FLAGS=$FLAGS" jer_down_2018"
    FLAGS=$FLAGS" sf_ele_eff_up"
    FLAGS=$FLAGS" sf_ele_eff_down"
    FLAGS=$FLAGS" sf_ele_reco_up"
    FLAGS=$FLAGS" sf_ele_reco_down"
    FLAGS=$FLAGS" sf_ele_trig_up"
    FLAGS=$FLAGS" sf_ele_trig_down"
    FLAGS=$FLAGS" sf_muo_id_up"
    FLAGS=$FLAGS" sf_muo_id_down"
    FLAGS=$FLAGS" sf_muo_iso_up"
    FLAGS=$FLAGS" sf_muo_iso_down"
    FLAGS=$FLAGS" sf_muo_trig_up"
    FLAGS=$FLAGS" sf_muo_trig_down"
    FLAGS=$FLAGS" sf_pho_eff_up"
    FLAGS=$FLAGS" sf_pho_eff_down"
    FLAGS=$FLAGS" sf_pho_veto_up_2016"
    FLAGS=$FLAGS" sf_pho_veto_up_2017"
    FLAGS=$FLAGS" sf_pho_veto_up_2018"
    FLAGS=$FLAGS" sf_pho_veto_down_2016"
    FLAGS=$FLAGS" sf_pho_veto_down_2017"
    FLAGS=$FLAGS" sf_pho_veto_down_2018"
    FLAGS=$FLAGS" l1prefiring_up"
    FLAGS=$FLAGS" l1prefiring_down"
    FLAGS=$FLAGS" eg_misid_up"
    FLAGS=$FLAGS" eg_misid_down"
    FLAGS=$FLAGS" jet_misid_syst"
    FLAGS=$FLAGS" veto_ele_medium"
    FLAGS=$FLAGS" veto_muo_medium"
  else
    FLAGS=$2
  fi
fi

LISTS=`ls lists/`

if [ ! -z "$3" ]; then
  if [ "$3" == "DT16" ]; then
    LISTS=`ls lists/ | grep Run2016`
  elif [ "$3" == "DT17" ]; then
    LISTS=`ls lists/ | grep Run2017`
  elif [ "$3" == "DT18" ]; then
    LISTS=`ls lists/ | grep Run2018`
  elif [ "$3" == "MC16" ]; then
    LISTS=`ls lists/ | grep RunIISummer16NanoAOD`
  elif [ "$3" == "MC17" ]; then
    LISTS=`ls lists/ | grep RunIIFall17NanoAOD`
  elif [ "$3" == "MC18" ]; then
    LISTS=`ls lists/ | grep 'RunIIAutumn18NanoAOD'`
  elif [ "$3" == "2016" ]; then
    LISTS=`ls lists/ | grep 'Run2016\|RunIISummer16NanoAOD'`
  elif [ "$3" == "2017" ]; then
    LISTS=`ls lists/ | grep 'Run2017\|RunIIFall17NanoAOD'`
  elif [ "$3" == "2018" ]; then
    LISTS=`ls lists/ | grep 'Run2018\|RunIIAutumn18NanoAOD'`
  else
    LISTS=$3
  fi
fi

alias SKIP=$SKIP

SKIP ./compile.sh mainSelector

mkdir -p data/$VERSION

cp -pv mainSelector.[hC] data/$VERSION/

for L in $LISTS; do
  L=`basename $L .list`.list
  ( [ ! -z "$NANOAODv6" ] && [ -z "$NANOAODv7" ] && [ ! -z "${L##*25Oct2019*}" ] && [ ! -z "${L##*AODv6*}" ] ) && continue
  ( [ ! -z "$NANOAODv7" ] && [ -z "$NANOAODv6" ] && [ ! -z "${L##*02Apr2020*}" ] && [ ! -z "${L##*AODv7*}" ] ) && continue
  if [ ! -e lists/$L ]; then
    echo "ERROR: missing file "lists/$L
    continue
  fi
  for FLAG in $FLAGS; do
    mkdir -p data/$VERSION/$FLAG
    bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_selector.sh $VERSION lists/$L $FLAG
  done
done

exit
