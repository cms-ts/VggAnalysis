#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

rm -f lumi.dat

for F in `ls logs/*.lumi`; do
  G=`basename $F .lumi`
  L=`grep -A 5 Summary $F | grep [0-9] | awk '{print $12}'`
  printf "%s\t%6.3f\n" $G $L >> lumi.dat
done

exit
