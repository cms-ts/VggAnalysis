#!/bin/bash

QUEUE=normal
export USE_LSF_STARTER=no

EXCLUDED_HOSTS=""
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm003 && hname!=farm004 && hname!=farm005 && hname!=farm006 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm019 && hname!=farm020 && hname!=farm021 && hname!=farm022 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm045 && hname!=farm046 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm025 && hname!=farm026 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm073 && hname!=farm074 && hname!=farm075 && hname!=farm076 && "
EXCLUDED_HOSTS=$EXCLUDED_HOSTS"hname!=farm061 && hname!=farm062 && hname!=farm063 && hname!=farm064"

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/tools
cd $WORKDIR

YEAR=$1

if [ -z "$YEAR" ]; then
  echo "Insert YEAR!"
  echo "USAGE ./start_run.sh [YEAR]"
  exit
fi

./compile.sh treeMaker

LISTS=""

if [ "$YEAR" == "2016" ]; then

  LISTS=$LISTS" ../macros/lists/RunIISummer16NanoAODv4_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.list"
  LISTS=$LISTS" ../macros/lists/RunIISummer16NanoAODv4_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.list"

  LISTS=$LISTS" ../macros/lists/Run2016B_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2016C_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2016D_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2016E_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2016F_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2016G_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2016H_SingleElectron_14Dec2018.list"

fi

if [ "$YEAR" == "2017" ]; then

  LISTS=$LISTS" ../macros/lists/RunIIFall17NanoAODv4_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8.list"
  LISTS=$LISTS" ../macros/lists/RunIIFall17NanoAODv4_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.list"

  LISTS=$LISTS" ../macros/lists/Run2017B_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2017C_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2017D_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2017E_SingleElectron_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2017F_SingleElectron_14Dec2018.list"

fi

if [ "$YEAR" == "2018" ]; then

  LISTS=$LISTS" ../macros/lists/RunIIAutumn18NanoAODv4_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8.list"
  LISTS=$LISTS" ../macros/lists/RunIIAutumn18NanoAODv4_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.list"

  LISTS=$LISTS" ../macros/lists/Run2018A_EGamma_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2018B_EGamma_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2018C_EGamma_14Dec2018.list"
  LISTS=$LISTS" ../macros/lists/Run2018D_EGamma_14Dec2018.list"

fi

for L in $LISTS; do
  L=`basename $L .list`.list
  if [ ! -e ../macros/lists/$L ]; then
    echo "ERROR: missing file "../macros/lists/$L
    continue
  fi
  bsub -q $QUEUE -R "$EXCLUDED_HOSTS" -J $L -e /dev/null -o /dev/null $WORKDIR/job_maker.sh ../macros/lists/$L
done

exit
