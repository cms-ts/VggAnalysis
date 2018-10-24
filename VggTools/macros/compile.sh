#!/bin/sh

export ROOT_HIST=0

if [ -z "$1" ]; then
  root-6.12 -l -q -b compile.C\(\"kcO\"\)
else
  root-6.12 -l -q -b compile.C\(\"kcOf\"\)
fi

exit
