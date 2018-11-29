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

VERSION="v04"

if [ ! -z "$2" ]; then
  VERSION=$2
fi

FLAGS=""

if [ ! -z "$3" ]; then
  FLAGS=$3
fi

for YEAR in $YEARS; do

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_npvs\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_npvs\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_npvs_w\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_npvs_w\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_sieie\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_met_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_met_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_met_sign\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_met_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_met_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_met_sign\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_mva\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_njets\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_jet0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_jet0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_jet0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_njets\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_jet0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_jet0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_jet0_phi\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_nphotons\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho0_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho0_sieie\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho1_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho1_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho1_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho1_sieie\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_nphotons\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho0_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho0_sieie\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho1_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho1_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho1_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho1_sieie\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho0_mva\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho1_mva\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho0_mva\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho1_mva\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_W_ele_pho0_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_W_ele_pho0_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_W_ele_pho1_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_W_ele_pho1_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_W_muo_pho0_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_W_muo_pho0_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_W_muo_pho1_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_W_muo_pho1_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho0_dR\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho0_dR\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho1_dR\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho1_dR\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho0\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho0\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_pho0_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_ele0_pho0\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_ele0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_ele0_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_pho0_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_muo0_pho0\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_muo0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_muo0_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)


  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_npvs\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_npvs\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_npvs_w\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_npvs_w\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_sieie\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_sieie\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_met_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_met_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_met_sign\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_met_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_met_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_met_sign\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_mva\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_mva\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_njets\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_jet0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_jet0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_jet0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_njets\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_jet0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_jet0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_jet0_phi\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_nphotons\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_sieie\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho1_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho1_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho1_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho1_sieie\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_nphotons\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_sieie\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho1_eta\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho1_phi\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho1_r9\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho1_sieie\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_mva\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho1_mva\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_mva\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho1_mva\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho1_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho1_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho1_pf_iso_all\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho1_pf_iso_chg\",\"$VERSION\",\"$FLAGS\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_dR\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_dR\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho1_dR\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho1_dR\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_pho0_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_ele0_pho0\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_ele0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_ele1_pho0\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_ele1_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_ele0_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_ele1_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_ele0_ele1_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_pho0_pho1_pt\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_muo0_pho0\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_muo0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_muo1_pho0\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_muo1_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_muo0_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_muo1_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_muo0_muo1_pho0_pho1\",\"$VERSION\",\"$FLAGS\"\)

done

exit
