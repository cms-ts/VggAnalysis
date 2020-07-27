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

export ROOT_HIST=0

for YEAR in $YEARS; do

  root.exe -l -q -b plot8.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_dR\",\"$VERSION\",\"$OPTIONS\",1\)
  root.exe -l -q -b plot8.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_dR\",\"$VERSION\",\"$OPTIONS\",1\)
  root.exe -l -q -b plot8.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele\",\"$VERSION\",\"$OPTIONS\",1\)
  root.exe -l -q -b plot8.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo\",\"$VERSION\",\"$OPTIONS\",1\)

  root.exe -l -q -b plot8.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_dR\",\"$VERSION\",\"$OPTIONS\",2\)
  root.exe -l -q -b plot8.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_dR\",\"$VERSION\",\"$OPTIONS\",2\)
  root.exe -l -q -b plot8.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele\",\"$VERSION\",\"$OPTIONS\",2\)
  root.exe -l -q -b plot8.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo\",\"$VERSION\",\"$OPTIONS\",2\)

  root.exe -l -q -b plot8.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_dR\",\"$VERSION\",\"$OPTIONS\",1\)
  root.exe -l -q -b plot8.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_dR\",\"$VERSION\",\"$OPTIONS\",1\)
  root.exe -l -q -b plot8.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele\",\"$VERSION\",\"$OPTIONS\",1\)
  root.exe -l -q -b plot8.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo\",\"$VERSION\",\"$OPTIONS\",1\)

  root.exe -l -q -b plot8.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_dR\",\"$VERSION\",\"$OPTIONS\",2\)
  root.exe -l -q -b plot8.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_dR\",\"$VERSION\",\"$OPTIONS\",2\)
  root.exe -l -q -b plot8.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele\",\"$VERSION\",\"$OPTIONS\",2\)
  root.exe -l -q -b plot8.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo\",\"$VERSION\",\"$OPTIONS\",2\)

done

exit
