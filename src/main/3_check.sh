#!/bin/sh

#./3_check a2.csv \
#| grep -v -E "skip loading|done loading|done checking" \
#> a3.csv

./3_check a2.csv | grep magicnumber_a4a6b25c | tee a3.csv
#./3_check a2.csv | grep magicnumber_a4a6b25c | head -n 1 > a3.csv
