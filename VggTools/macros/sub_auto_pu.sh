#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

LISTS=`ls lists/ | grep RunIIFall17NanoAOD`

alias SKIP=$SKIP

SKIP ./compile.sh auto_pu

mkdir -p data/auto_pu

rm -f data/auto_pu/condor_auto_pu.run

echo "universe = vanilla"                  >> data/auto_pu/condor_auto_pu.run
echo "executable = job_auto_pu.sh"         >> data/auto_pu/condor_auto_pu.run
echo "rank = TARGET.KFlops"                >> data/auto_pu/condor_auto_pu.run
echo "requirements = TARGET.TotalCpus > 2" >> data/auto_pu/condor_auto_pu.run
echo "getenv = TRUE"                       >> data/auto_pu/condor_auto_pu.run
echo "queue arguments from ("              >> data/auto_pu/condor_auto_pu.run

check=0
for L in $LISTS; do
  L=`basename $L .list`.list
  if [ ! -e lists/$L ]; then
    echo "ERROR: missing file "lists/$L
    continue
  fi
  FILE_ELE=data/auto_pu/pileup_ele_`basename $L .list`.root
  if [ lists/$L -nt $FILE_ELE ]; then
    echo "  lists/$L $FILE_ELE"            >> data/auto_pu/condor_auto_pu.run
    check=1
  fi
  FILE_ELE=data/auto_pu/pileup_ele_up_`basename $L .list`.root
  if [ lists/$L -nt $FILE_ELE ]; then
    echo "  lists/$L $FILE_ELE"            >> data/auto_pu/condor_auto_pu.run
    check=1
  fi
  FILE_ELE=data/auto_pu/pileup_ele_down_`basename $L .list`.root
  if [ lists/$L -nt $FILE_ELE ]; then
    echo "  lists/$L $FILE_ELE"            >> data/auto_pu/condor_auto_pu.run
    check=1
  fi
  FILE_MUO=data/auto_pu/pileup_muo_`basename $L .list`.root
  if [ lists/$L -nt $FILE_MUO ]; then
    echo "  lists/$L $FILE_MUO"            >> data/auto_pu/condor_auto_pu.run
    check=1
  fi
  FILE_MUO=data/auto_pu/pileup_muo_up_`basename $L .list`.root
  if [ lists/$L -nt $FILE_MUO ]; then
    echo "  lists/$L $FILE_MUO"            >> data/auto_pu/condor_auto_pu.run
    check=1
  fi
  FILE_MUO=data/auto_pu/pileup_muo_down_`basename $L .list`.root
  if [ lists/$L -nt $FILE_MUO ]; then
    echo "  lists/$L $FILE_MUO"            >> data/auto_pu/condor_auto_pu.run
    check=1
  fi
done

echo ")"                                   >> data/auto_pu/condor_auto_pu.run

if [ $check -eq 0 ]; then
  echo
  echo "all pileup files are up-to-date"
  echo
  exit
else
  echo
  echo "Submit jobs with: condor_submit data/auto_pu/condor_auto_pu.run"
  echo
fi

exit
