#!/bin/sh

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
    FLAGS=""
    FLAGS=$FLAGS" reference"
    FLAGS=$FLAGS" bkg_stat"
    FLAGS=$FLAGS" jet_misid_stat"
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
#    FLAGS=$FLAGS" bkg_syst"
    FLAGS=$FLAGS" xsec_syst_wg"
    FLAGS=$FLAGS" xsec_syst_zg"
    FLAGS=$FLAGS" xsec_syst_others"
    FLAGS=$FLAGS" jet_misid_syst"
    FLAGS=$FLAGS" jet_misid_test"
    FLAGS=$FLAGS" jet_misid_qcd"
    FLAGS=$FLAGS" jet_misid_sherpa"
#    FLAGS=$FLAGS" jet_misid_mc"
    FLAGS=$FLAGS" jet_bkg_mc"
    FLAGS=$FLAGS" qcd_fit"
    FLAGS=$FLAGS" veto_ele_medium"
    FLAGS=$FLAGS" veto_muo_medium"
    FLAGS=$FLAGS" lumi_up"
    FLAGS=$FLAGS" lumi_down"
  else
    FLAGS=$4
  fi
fi

alias SKIP=$SKIP

if [ -z $EXE ]; then
  SKIP ./compile.sh plot

  rm -f data/$VERSION/condor_process.run

  echo "universe = vanilla"                            >> data/$VERSION/condor_process.run
  echo "executable = process.sh"                       >> data/$VERSION/condor_process.run
  echo "rank = TARGET.TotalCpus - TARGET.TotalLoadAvg" >> data/$VERSION/condor_process.run
  echo "requirements = TARGET.TotalCpus > 2"           >> data/$VERSION/condor_process.run
  echo "getenv = TRUE"                                 >> data/$VERSION/condor_process.run
  echo "queue arguments from ("                        >> data/$VERSION/condor_process.run

  for YEAR in $YEARS; do
    for OPTION in $OPTIONS; do
      for FLAG in $FLAGS; do
        echo "  $VERSION $YEAR $OPTION $FLAG"          >> data/$VERSION/condor_process.run
      done
    done
  done

  echo ")"                                             >> data/$VERSION/condor_process.run
else
  SKIP ./compile.sh exe

  rm -f data/$VERSION/condor_process.run

  echo "universe = vanilla"                            >> data/$VERSION/condor_process.run
  echo "executable = process.exe"                      >> data/$VERSION/condor_process.run
  echo "rank = TARGET.TotalCpus - TARGET.TotalLoadAvg" >> data/$VERSION/condor_process.run
  echo "requirements = TARGET.TotalCpus > 2"           >> data/$VERSION/condor_process.run
  echo "getenv = TRUE"                                 >> data/$VERSION/condor_process.run
  echo "queue arguments from ("                        >> data/$VERSION/condor_process.run

  for OPTION in $OPTIONS; do
    for FLAG in $FLAGS; do
      echo "  $VERSION $OPTION $FLAG"                  >> data/$VERSION/condor_process.run
    done
  done

  echo ")"                                             >> data/$VERSION/condor_process.run
fi

echo
echo "Submit jobs with: condor_submit data/$VERSION/condor_process.run"
echo

exit
