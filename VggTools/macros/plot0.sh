#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

export ROOT_HIST=0

YEARS="2016 2017 2018"

if [ ! -z "$1" ]; then
  YEARS=$1
fi

for Y in $YEARS; do

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_npvs\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_npvs\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_npvs_w\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_npvs_w\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_met_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_met_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_met_sign\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_met_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_met_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_met_sign\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_njets\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_jet0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_jet0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_jet0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_njets\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_jet0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_jet0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_jet0_phi\"\)

  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_nphotons\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_pho0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_pho0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_pho0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_pho1_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_pho1_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_pho1_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_ele.dat\",\"h_W_ele_diphoton_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_nphotons\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_pho0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_pho0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_pho0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_pho1_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_pho1_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_pho1_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Wgg"$Y"_muo.dat\",\"h_W_muo_diphoton_pt\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_npvs\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_npvs\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_npvs_w\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_npvs_w\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele1_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele1_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele1_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo1_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo1_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo1_phi\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_njets\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_jet0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_jet0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_jet0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_njets\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_jet0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_jet0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_jet0_phi\"\)

  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_nphotons\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_pho0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_pho0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_pho0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_pho1_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_pho1_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_pho1_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_ele.dat\",\"h_Z_ele_diphoton_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_nphotons\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_pho0_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_pho0_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_pho0_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_pho1_pt\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_pho1_eta\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_pho1_phi\"\)
  root-6.12 -l -q -b plot0.C+\(\"Zgg"$Y"_muo.dat\",\"h_Z_muo_diphoton_pt\"\)

done

exit
