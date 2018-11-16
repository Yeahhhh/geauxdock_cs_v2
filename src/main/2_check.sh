#!/bin/sh

# tee does not capture the return status of the 1st command
#./2_check data1.csv | tee $mytmp





mytmp=$(mktemp ./tmp_XXXXXXX)


./2_check > $mytmp
rv=$?                           # capture the return status of the 1st command

cat $mytmp
grep magicnumber_a4a6b25c $mytmp > data2.csv
rm $mytmp




exit $rv

