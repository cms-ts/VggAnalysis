#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/skim
cd $WORKDIR

busers
echo
echo -n '/eos/infnts/cms/store/data/ | grep Nano25Oct2019 -> '
eos find -f /eos/infnts/cms/store/data/ | grep Nano25Oct2019 | wc -l
echo -n '/eos/infnts/cms/store/user/dellaric/data/ | grep Nano25Oct2019 -> '
eos find -f /eos/infnts/cms/store/user/dellaric/data/ | grep Nano25Oct2019 | wc -l
echo -n './logs/ -> '
find logs/ -type f -name '*_Skim.log' | wc -l
echo
./sub_data_skim.sh
echo
./check_logs.sh

exit
