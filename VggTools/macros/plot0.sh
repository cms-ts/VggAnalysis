#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

export ROOT_HIST=0

root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_W_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_muo.dat\",\"h_W_muo\"\)

root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_W_npvs_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_muo.dat\",\"h_W_npvs_muo\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_W_npvs_ele_w\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_muo.dat\",\"h_W_npvs_muo_w\"\)

root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_W_ele0_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_W_ele_met_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_W_muo0_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_W_muo_met_pt\"\)

root-6.12 -l -q -b plot0.C+\(\"Zgg2016_ele.dat\",\"h_Z_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2016_muo.dat\",\"h_Z_muo\"\)

root-6.12 -l -q -b plot0.C+\(\"Zgg2016_ele.dat\",\"h_Z_npvs_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2016_muo.dat\",\"h_Z_npvs_muo\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2016_ele.dat\",\"h_Z_npvs_ele_w\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2016_muo.dat\",\"h_Z_npvs_muo_w\"\)

root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_Z_ele0_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_Z_ele1_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_Z_muo0_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2016_ele.dat\",\"h_Z_muo1_pt\"\)


root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_W_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_muo.dat\",\"h_W_muo\"\)

root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_W_npvs_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_muo.dat\",\"h_W_npvs_muo\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_W_npvs_ele_w\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_muo.dat\",\"h_W_npvs_muo_w\"\)

root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_W_ele0_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_W_ele_met_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_W_muo0_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_W_muo_met_pt\"\)

root-6.12 -l -q -b plot0.C+\(\"Zgg2017_ele.dat\",\"h_Z_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2017_muo.dat\",\"h_Z_muo\"\)

root-6.12 -l -q -b plot0.C+\(\"Zgg2017_ele.dat\",\"h_Z_npvs_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2017_muo.dat\",\"h_Z_npvs_muo\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2017_ele.dat\",\"h_Z_npvs_ele_w\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2017_muo.dat\",\"h_Z_npvs_muo_w\"\)

root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_Z_ele0_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_Z_ele1_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_Z_muo0_pt\"\)
root-6.12 -l -q -b plot0.C+\(\"Wgg2017_ele.dat\",\"h_Z_muo1_pt\"\)

exit
