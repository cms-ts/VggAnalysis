#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION="v09"

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

FLAGS="nolog,amcatnlo"

if [ ! -z "$3" ]; then
  FLAGS=$3
fi

export ROOT_HIST=0

for YEAR in $YEARS; do

  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_ele0_ele1_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_muo0_muo1_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_ele0_ele1_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_muo0_muo1_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot4.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)

done

exit
