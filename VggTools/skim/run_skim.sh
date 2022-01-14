#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/skim
cd $WORKDIR

echo
echo -n 'condor_q | grep 02Apr2020 -> '
condor_q -nobatch 2>&1 | grep 02Apr2020 | wc -l
echo
echo -n '/eos/infnts/cms/store/data/ | grep 02Apr2020 -> '
eos find -f /eos/infnts/cms/store/data/ | grep 02Apr2020 | wc -l
echo -n '/eos/infnts/cms/store/data/ | grep 02Apr2020 -> '
eos find -f -0 /eos/infnts/cms/store/data/ | grep 02Apr2020 | wc -l
echo -n '/eos/infnts/cms/store/user/dellaric/data/ | grep 02Apr2020 -> '
eos find -f /eos/infnts/cms/store/user/dellaric/data/ | grep 02Apr2020 | wc -l
echo -n './logs/ -> '
find ./logs/ -type f -name '*_Skim.log' | wc -l
echo
./sub_data_skim.sh
echo
./check_logs.sh

exit
