#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

LIST=$1

FILE_ELE=data/auto_pu2017/pileup_ele_`basename $LIST .list`.root
LOG_ELE=data/auto_pu2017/pileup_ele_`basename $LIST .list`.log

FILE_MUO=data/auto_pu2017/pileup_muo_`basename $LIST .list`.root
LOG_MUO=data/auto_pu2017/pileup_muo_`basename $LIST .list`.log

export ROOT_HIST=0

if [ $LIST -nt $FILE_MUO ] || [ $LIST -nt $FILE_ELE ] ; then
  root-6.12 -l -b -q auto_pu2017.C+\(\"$LIST\"\,\"$FILE_ELE\"\) > $LOG_ELE 2>&1
  root-6.12 -l -b -q auto_pu2017.C+\(\"$LIST\"\,\"$FILE_MUO\"\) > $LOG_MUO 2>&1
fi

exit
