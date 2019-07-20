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

[ -z "${OPTIONS##*qcd*}" ] && SKIP1=":"

[ "$FLAG" != "reference" ] && SKIP2=":"

[ "$YEAR" == "Run2" ] && SKIP2=":"

for YEAR in $YEARS; do

                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_npvs\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_npvs_w\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_npvs\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_npvs_w\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_met_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_met_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_met_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_met_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_npvs\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_npvs_w\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_npvs\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_npvs_w\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_met_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_met_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_met_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_met_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_njets\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_jet0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_jet0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_jet0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_njets\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_jet0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_jet0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_jet0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_njets\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_jet0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_jet0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_jet0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_njets\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_jet0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_jet0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_jet0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele_nphotons\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_ele0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_jet0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_jet0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_ele0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_pho1_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo_nphotons\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_muo0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_jet0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_jet0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_muo0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_pho1_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele_nphotons\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_ele0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_jet0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_jet0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_ele0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_ele1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_pho1_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo_nphotons\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_muo0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_jet0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_eta\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_phi\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_r9\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_sieie\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_jet0_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_pf_iso_all\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_pf_iso_chg\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_muo0_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_muo1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_pho1_dR\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_ele0_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_ele0_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_ele0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_ele0_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_ele0_pho0_fake\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_muo0_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_muo_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_muo0_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_muo0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
                root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_muo0_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_muo0_pho0_fake\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_ele0_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_ele1_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_ele0_ele1_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_ele0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_ele1_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_ele0_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_ele1_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_ele0_ele1_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_muo0_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_muo0_muo1_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_muo1_pho0\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_pho1_pt\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1        root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_muo0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_muo1_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_muo0_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_muo1_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_muo0_muo1_pho0_pho1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho0_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WGG_ele_pho1_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho0_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WGG_muo_pho1_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho0_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZGG_ele_pho1_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho0_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZGG_muo_pho1_noiso_mva\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_W_ele0_trig\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_W_muo0_trig\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele0_trig\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_Z_ele1_trig\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo0_trig\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_Z_muo1_trig\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_pt_cat1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_pt_cat1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_pt_cat1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_pt_cat1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_muo0_muo1_pho0_cat1\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_pt_cat2\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_pt_cat2\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_pt_cat2\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_pt_cat2\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_muo0_muo1_pho0_cat2\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele\",\"h_WG_ele_pho0_pt_cat3\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
         $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo\",\"h_WG_muo_pho0_pt_cat3\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele\",\"h_ZG_ele_pho0_pt_cat3\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_pho0_pt_cat3\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)
  $SKIP1 $SKIP2 root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo\",\"h_ZG_muo_muo0_muo1_pho0_cat3\",\"$VERSION\",\"$OPTIONS\",\"$FLAG\"\)

done

exit
