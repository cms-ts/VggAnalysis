#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/skim
cd $WORKDIR

DATADIR=/eos/infnts/cms/store/data

rm -f logs/condor_data_skim.run

echo "executable = job_data_skim.sh"       >> logs/condor_data_skim.run
echo "rank = TARGET.KFlops"                >> logs/condor_data_skim.run
echo "requirements = TARGET.TotalCpus > 2" >> logs/condor_data_skim.run
echo "getenv = TRUE"                       >> logs/condor_data_skim.run
echo "queue arguments from ("              >> logs/condor_data_skim.run

for F in `eos find -f $DATADIR/ | grep NANOAOD | grep 02Apr2020`; do
  if [ -s $F ]; then
    if [ ! -e logs/`basename $F .root`_Skim.log ]; then
      touch logs/`basename $F .root`_Skim.log
      eos mkdir -p `dirname $F | sed -e 's;data;user/dellaric/data;'`
      echo "  $F"                          >> logs/condor_data_skim.run
    fi
  fi
done

echo ")"                                   >> logs/condor_data_skim.run

echo
echo "Submit jobs with: condor_submit logs/condor_data_skim.run"
echo

exit
