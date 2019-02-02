#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

VERSION=$1
LIST=$2

FILE=data/$VERSION/`basename $LIST .list`.root
LOG=data/$VERSION/`basename $LIST .list`.log

export ROOT_HIST=0

rm -f $LOG

if [ -z "${LIST##*RunIIFall17NanoAOD*}" ]; then
  [ ! -e data/auto_pu2017 ] && mkdir -p data/auto_pu2017
  PILEUP_ELE_FILE=data/auto_pu2017/pileup_ele_`basename $LIST .list`.root
  PILEUP_MUO_FILE=data/auto_pu2017/pileup_muo_`basename $LIST .list`.root
  if [ $LIST -nt $PILEUP_ELE_FILE ] || [ $LIST -nt $PILEUP_MUO_FILE ] ; then
    root-6.12 -l -b -q auto_pu2017.C\(\"$LIST\"\,\"$PILEUP_ELE_FILE\"\) >> $LOG 2>&1
    root-6.12 -l -b -q auto_pu2017.C\(\"$LIST\"\,\"$PILEUP_MUO_FILE\"\) >> $LOG 2>&1
  fi
fi

root-6.12 -l -b -q run.C\(\"$LIST\",\"$FILE\"\) >> $LOG 2>&1

exit
