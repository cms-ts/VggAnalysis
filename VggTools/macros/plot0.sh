#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

export ROOT_HIST=0

root-6.12 -l -q -b plot0.C+\(\"Zgg2016_ele.dat\",\"h_Z_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2016_muo.dat\",\"h_Z_muo\"\)

root-6.12 -l -q -b plot0.C+\(\"Zgg2016_ele.dat\",\"h_npvs_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2016_muo.dat\",\"h_npvs_muo\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2016_ele.dat\",\"h_npvs_ele_w\"\)
root-6.12 -l -q -b plot0.C+\(\"Zgg2016_muo.dat\",\"h_npvs_muo_w\"\)

#root-6.12 -l -q -b plot0.C+\(\"Zgg2017_ele.dat\",\"h_Z_ele\"\)
#root-6.12 -l -q -b plot0.C+\(\"Zgg2017_muo.dat\",\"h_Z_muo\"\)

#root-6.12 -l -q -b plot0.C+\(\"Zgg2017_ele.dat\",\"h_npvs_ele\"\)
#root-6.12 -l -q -b plot0.C+\(\"Zgg2017_muo.dat\",\"h_npvs_muo\"\)
#root-6.12 -l -q -b plot0.C+\(\"Zgg2017_ele.dat\",\"h_npvs_ele_w\"\)
#root-6.12 -l -q -b plot0.C+\(\"Zgg2017_muo.dat\",\"h_npvs_muo_w\"\)

exit
