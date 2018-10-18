#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

export ROOT_HIST=0

YEARS="2016 2017 2018"

if [ ! -z "$1" ]; then
  YEARS=$1
fi

VERSION="v00"

if [ ! -z "$2" ]; then
  VERSION=$2
fi

for YEAR in $YEARS; do

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_npvs\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_npvs\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_npvs_w\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_npvs_w\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_met_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_met_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_met_sign\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_met_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_met_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_met_sign\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_njets\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_jet0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_jet0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_jet0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_njets\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_jet0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_jet0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_jet0_phi\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_nphotons\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_pho0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_pho0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_pho0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_pho1_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_pho1_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_pho1_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_diphoton_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_nphotons\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_pho0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_pho0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_pho0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_pho1_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_pho1_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_pho1_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_diphoton_pt\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_pho0_dR\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_pho0_dR\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_pho1_dR\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_pho1_dR\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_ele.dat\",\"h_W_ele_pho0\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$YEAR"_muo.dat\",\"h_W_muo_pho0\",\"$VERSION\"\)


  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_npvs\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_npvs\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_npvs_w\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_npvs_w\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele1_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele1_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele1_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo1_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo1_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo1_phi\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_njets\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_jet0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_jet0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_jet0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_njets\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_jet0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_jet0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_jet0_phi\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_nphotons\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_pho0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_pho0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_pho0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_pho1_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_pho1_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_pho1_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_diphoton_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_nphotons\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_pho0_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_pho0_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_pho0_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_pho1_pt\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_pho1_eta\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_pho1_phi\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_diphoton_pt\",\"$VERSION\"\)
 
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_pho0_dR\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_pho0_dR\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_pho1_dR\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_pho1_dR\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_ele.dat\",\"h_Z_ele_pho0\",\"$VERSION\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$YEAR"_muo.dat\",\"h_Z_muo_pho0\",\"$VERSION\"\)

done

exit
