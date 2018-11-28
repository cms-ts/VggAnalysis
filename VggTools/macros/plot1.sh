#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_2_5 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_2_5
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

export ROOT_HIST=0

YEARS="2016 2017 2018"

if [ ! -z "$1" ]; then
  if [ "$1" == "all" ]; then
    YEARS="2016 2017 2018"
  else
    YEARS=$1
  fi
fi

VERSION="v03"

if [ ! -z "$2" ]; then
  VERSION=$2
fi

FLAGS=""

if [ ! -z "$3" ]; then
  FLAGS=$3
fi

for YEAR in $YEARS; do

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$FLAGS,nofit\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$FLAGS,nofit\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$FLAGS,qcd,nofit\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$FLAGS,qcd,nofit\"\)
 
  root-6.12 -l -q -b plot1.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot1.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$FLAGS\"\)

done

exit
