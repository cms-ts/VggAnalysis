#!/bin/sh

QUEUE=normal
export USE_LSF_STARTER=no

EXCLUDED_HOSTS=""
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm003 && hname!=farm004 && hname!=farm005 && hname!=farm006 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm019 && hname!=farm020 && hname!=farm021 && hname!=farm022 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm025 && hname!=farm026 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm045 && hname!=farm046 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm061 && hname!=farm062 && hname!=farm063 && hname!=farm064 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm073 && hname!=farm074 && hname!=farm075 && hname!=farm076"

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION="v00"

if [ ! -z "$1" ]; then
  VERSION=$1
fi

YEARS="2016"

if [ ! -z "$2" ]; then
  if [ "$2" == "all" ]; then
    YEARS="2016 2017 2018"
  else
    YEARS=$2
  fi
fi

OPTIONS="default,nolog"

if [ ! -z "$3" ]; then
  OPTIONS=$3
fi

FLAGS="reference"

if [ ! -z "$4" ]; then
  if [ "$4" == "all" ]; then
    FLAGS="reference"
    FLAGS=$FLAGS" bkg_stat"
    FLAGS=$FLAGS" jet_misid_stat"
    FLAGS=$FLAGS" pileup_up"
    FLAGS=$FLAGS" pileup_down"
    FLAGS=$FLAGS" jec_up_2016"
    FLAGS=$FLAGS" jec_up_2017"
    FLAGS=$FLAGS" jec_up_2018"
    FLAGS=$FLAGS" jec_down_2016"
    FLAGS=$FLAGS" jec_down_2017"
    FLAGS=$FLAGS" jec_down_2018"
    FLAGS=$FLAGS" jer_up_2016"
    FLAGS=$FLAGS" jer_up_2017"
    FLAGS=$FLAGS" jer_up_2018"
    FLAGS=$FLAGS" jer_down_2016"
    FLAGS=$FLAGS" jer_down_2017"
    FLAGS=$FLAGS" jer_down_2018"
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
    FLAGS=$FLAGS" jet_misid_iso1"
    FLAGS=$FLAGS" jet_misid_iso2"
    FLAGS=$FLAGS" jet_misid_mc"
    FLAGS=$FLAGS" jet_bkg_mc"
#    FLAGS=$FLAGS" qcd_fit"
  else
    FLAGS=$4
  fi
fi

alias SKIP=$SKIP

SKIP ./compile.sh plot

for YEAR in $YEARS; do
  for OPTION in $OPTIONS; do
    for FLAG in $FLAGS; do
      bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $VERSION/$OPTION/$YEAR/$FLAG -e /dev/null -o /dev/null $WORKDIR/process.sh $VERSION $YEAR $OPTION $FLAG
    done
  done
done

exit
