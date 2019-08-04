#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION="v12"

if [ ! -z "$1" ]; then
  if [ "$1" == "list" ]; then
    echo
    echo "Available versions:"
    echo
    find -L ./data/ -mindepth 2 -maxdepth 2 -type d -printf "%P\n" | grep -v archive | grep -v auto_pu | sort | column
    echo
    exit
  elif [ "$1" == "short" ]; then
    echo
    printf "%s\n" "============================================"
    printf "%-30s\t%4s\t%4s\n" "versions" " log" "root"
    printf "%s\n" "============================================"
    VERSION=`ls -tr ./data/ | grep -v archive | grep -v auto_pu`
    for V in $VERSION; do
      LISTS=`find -L ./data/$V -mindepth 1 -maxdepth 1 -type d -printf "%P\n" | grep -v archive | grep -v auto_pu | sort`
      for L in $LISTS; do
        printf "%-30s\t%4d\t%4d\n" $V/$L `find -L ./data/$V/$L -type f -name '*.log' | wc -l` `find -L ./data/$V/$L -type f -name '*.root' | wc -l`
      done
      printf "%s\n" "--------------------------------------------"
      printf "%-30s\t%4d\t%4d\n" $V `find -L ./data/$V -type f -name '*.log' | wc -l` `find -L ./data/$V -type f -name '*.root' | wc -l`
      printf "%s\n" "============================================"
    done
    echo
    exit
  elif [ "$1" == "all" ]; then
    VERSION=`ls ./data/ | grep -v archive | grep -v auto_pu | sort`
  elif [ "$1" == "last" ]; then
    VERSION=`ls -tr ./data/ | grep -v archive | grep -v auto_pu | tail -1`
  else
    VERSION=$1
  fi
fi

LISTS=""
for V in $VERSION; do
  LISTS=$LISTS" "`find -L ./data/$V -type f -name '*.log' | sort`
done

if [ -z "${LISTS// }" ]; then
  echo
  echo "ERROR: version "$VERSION" not available !"
  echo
  exit
fi

if [ ! -z "$2" ]; then
  LISTS=`find -L ./data/$VERSION | grep $2.log | sort`
fi

total=0
running=0
errors=0
done=0

echo

for L in $LISTS; do
  total=$((total+1))
  O=`cat $L | \
  grep '[a-z,A-Z]' | \
  grep -v 'Processing' | \
  grep -v 'input list' | \
  grep -v 'Starting PROOF-Lite' | \
  grep -v 'Opening connections to workers:' | \
  grep -v 'Setting up worker servers:' |
  grep -v 'PROOF set to parallel mode' | \
  grep -v 'Info' | \
  grep -v "Looking up for exact location of files:" | \
  grep -v 'Validating files:' | \
  grep -v 'entries' | \
  grep -v 'TProof::Progress' | \
  grep -v 'Query processing time' | \
  grep -v 'Lite-0' | \
  grep -v 'Temporary failure in name resolution' | \
  grep -v '+++' | \
  grep -v '(M)' | \
  grep -v '#'`
  if [ -z "$O" ]; then
    printf "GOOD  - "
    grep -q "processed events" $L
    if [ $? -eq 0 ]; then
      printf "done       "
      done=$((done+1))
    else
      printf "running    "
      running=$((running+1))
    fi
  else
    printf "ERROR - "
    if [ -z "${O##*no files to process*}" ]; then
      printf "(no files) "
    elif [ -z "${O##*unable to open file*}" ]; then
      printf "(bad file) "
    elif [ -z "${O##*does not have a branch*}" ]; then
      printf "(version)  "
    elif [ -z "${O##*unknown flags*}" ]; then
      printf "(flags)    "
    else
      printf "           "
    fi
    errors=$((errors+1))
  fi
  if [ -z "${L##*auto_pu*}" ]; then
    printf ": ./data/%s \n" `basename \`dirname $L\``/`basename $L`
  elif [ -z "${L##*/*}" ]; then
    printf ": ./data/%s/%s \n" ${VERSION%%/*} `basename \`dirname $L\``/`basename $L`
  else
    printf ": ./data/%s/%s \n" $VERSION `basename \`dirname $L\``/`basename $L`
  fi
done

echo
printf "Total: %3d - Running: %3d - Done: %3d - Errors: %3d\n" $total $running $done $errors
echo

exit
