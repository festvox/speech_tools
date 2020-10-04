#!/bin/sh

TESTNAME="$1" # e.g.: hash_example
shift
TESTBIN="$1"
shift
CORRECTDIR="$1"
shift
TESTARGS=$@

mkdir -p "tmp"
if $TESTBIN $TESTARGS > $TESTNAME.out; then
    echo $TESTNAME completed
    if [ ! -f $TESTNAME.out ] || diff $CORRECTDIR/$TESTNAME.out $TESTNAME.out; then
        echo "$TESTNAME status: CORRECT"
        exit 0
    else
        echo "$TESTNAME status: INCORRECT"
        exit 1
    fi
else
    echo $TESTNAME status: FAILED
    exit 1
fi

