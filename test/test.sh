#!/bin/bash
# File: test.sh
# Date: Sat Mar 30 10:40:38 2013 +0800

PROG=$1
DIR=$(dirname $0)
OUT=/tmp/out
for i in `ls $DIR/*.in`; do
	time $PROG $i $OUT
done

