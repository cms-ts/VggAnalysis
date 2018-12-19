#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

export ROOT_HIST=0

if [ -z "$1" ]; then
  root-6.12 -l -q -b compile.C\(\"kcO\"\)
else
  root-6.12 -l -q -b compile.C\(\"kcOf\"\)
fi

exit
