#!/bin/sh

#cd /gpfs/cms/users/darold/work/rivet/CMSSW_10_2_7/
cd /gpfs/cms/users/fvazzole/work/RIVET_TO_COMMIT/CMSSW_10_2_7/
eval `scramv1 runtime -sh`
cd -

cp /home/dellaric/work/cms/VggAnalysis/test/CMSSW_10_2_13_patch1/rivet_cfg_Z.py jobZ.py

echo "fileList = cms.untracked.vstring()" >> jobZ.py
i=1
while [ $i -le $# ]; do
  file=`echo file:${!i}`
  #file=`echo ${!i} | sed -e 's;/eos/infnts/cms;;'`
  echo "fileList.extend(['"$file"'])" >> jobZ.py
  i=$((i+1))
done
echo "process.source.fileNames = fileList" >> jobZ.py

(time cmsRun -j jobZ.xml jobZ.py) > jobZ.log 2>&1

exit
