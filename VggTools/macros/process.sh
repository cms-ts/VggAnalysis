#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION="v10"

if [ ! -z "$1" ]; then
  VERSION=$1
fi

if [ -z "$1" ]; then
  echo "ERROR: missing version !!"
  exit
fi

YEARS="2016"

if [ ! -z "$2" ]; then
  if [ "$2" == "all" ]; then
    YEARS="2016 2017 2018"
  else
    YEARS=$2
  fi
fi

OPTIONS="nolog,default"

if [ ! -z "$3" ]; then
  OPTIONS=$3
fi

FLAGS="reference"

if [ ! -z "$4" ]; then
  FLAGS=$4
fi

for YEAR in $YEARS; do

  for OPTION in $OPTIONS; do

    for FLAG in $FLAGS; do

      ( \
        ./plot1.sh $VERSION $YEAR $OPTION $FLAGS ; \
        ./plot0.sh $VERSION $YEAR $OPTION",qcd,nofit" $FLAGS ; \
        ./plot0.sh $VERSION $YEAR $OPTION $FLAGS ; \
        ./plot2.sh $VERSION $YEAR $OPTION $FLAGS ; \
        ./plot3.sh $VERSION $YEAR $OPTION $FLAGS ; \
        ./plot4.sh $VERSION $YEAR $OPTION $FLAGS ; \
        ./plot5.sh $VERSION $YEAR $OPTION $FLAGS \
      ) &

    done

  done

done

exit
