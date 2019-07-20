#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
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

FLAG="reference"

if [ ! -z "$4" ]; then
  FLAG=$4
fi

export ROOT_HIST=0

for YEAR in $YEARS; do

  root-6.12 -l -q -b plot5.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_nphotons\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_nphotons\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  root-6.12 -l -q -b plot5.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_nphotons\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_nphotons\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  root-6.12 -l -q -b plot5.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  root-6.12 -l -q -b plot5.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  root-6.12 -l -q -b plot5.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

done

exit
