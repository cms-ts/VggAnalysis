#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION="v11"

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

OPTIONS="nolog,amcatnlo"

if [ ! -z "$3" ]; then
  OPTIONS=$3
fi

FLAGS="reference"

if [ ! -z "$4" ]; then
  FLAGS=$4
fi

export ROOT_HIST=0

for YEAR in $YEARS; do

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$OPTIONS,nofit\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$OPTIONS,nofit\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$OPTIONS,qcd,nofit\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$OPTIONS,qcd,nofit\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot1.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot1.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele\",\"$VERSION\",\"$OPTIONS,nofit\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo\",\"$VERSION\",\"$OPTIONS,nofit\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele\",\"$VERSION\",\"$OPTIONS,qcd,nofit\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo\",\"$VERSION\",\"$OPTIONS,qcd,nofit\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot1.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot1.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAGS\"\)

done

exit
