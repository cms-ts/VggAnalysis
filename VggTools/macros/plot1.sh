#!/bin/sh

if [ -r $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0 ]; then
  cd $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

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

FLAG="reference"

if [ ! -z "$4" ]; then
  FLAG=$4
fi

export ROOT_HIST=0

for YEAR in $YEARS; do

  root.exe -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$OPTIONS,nofit\",\"$FLAG\"\)
  root.exe -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$OPTIONS,nofit\",\"$FLAG\"\)

  root.exe -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$OPTIONS,qcd,nofit\",\"$FLAG\"\)
  root.exe -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$OPTIONS,qcd,nofit\",\"$FLAG\"\)

  root.exe -l -q -b plot1.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root.exe -l -q -b plot1.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  root.exe -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele\",\"$VERSION\",\"$OPTIONS,nofit\",\"$FLAG\"\)
  root.exe -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo\",\"$VERSION\",\"$OPTIONS,nofit\",\"$FLAG\"\)

  root.exe -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele\",\"$VERSION\",\"$OPTIONS,qcd,nofit\",\"$FLAG\"\)
  root.exe -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo\",\"$VERSION\",\"$OPTIONS,qcd,nofit\",\"$FLAG\"\)

  root.exe -l -q -b plot1.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root.exe -l -q -b plot1.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

done

exit
