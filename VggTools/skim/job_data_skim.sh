#!/bin/sh

cd $HOME/work/cms/CMSSW_10_2_22/
eval `scramv1 runtime -sh`
cd $OLDPWD

F=`echo $1 | sed -e 's;/eos/infnts;root://eosinfnts.ts.infn.it//eos/infnts;'`
G=`basename $1 .root`_Skim
D=`dirname $1 | sed -e 's;data;user/dellaric/data;'`

if [ -e $D/$G.root ]; then
  exit
fi

if [ -z "${1##*Run2016*02Apr2020*}" ]; then
  python nano_postproc.py \
  -J /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt \
  . $F > logs/$G.log 2>&1
  eos cp $G.root $D/$G.root >> logs/$G.log 2>&1
  rm $G.root >> logs/$G.log 2>&1
fi

if [ -z "${1##*Run2017*02Apr2020*}" ]; then
  python nano_postproc.py \
  -J /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt \
  . $F > logs/$G.log 2>&1
  eos cp $G.root $D/$G.root >> logs/$G.log 2>&1
  rm $G.root >> logs/$G.log 2>&1
fi

if [ -z "${1##*Run2018*02Apr2020*}" ]; then
  python nano_postproc.py \
  -J /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt \
  . $F > logs/$G.log 2>&1
  eos cp $G.root $D/$G.root >> logs/$G.log 2>&1
  rm $G.root >> logs/$G.log 2>&1
fi

exit
