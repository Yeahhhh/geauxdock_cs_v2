#!/bin/sh

#./2_check a1.csv \
#| grep -v -E "skip loading|done loading|done checking" \
#> a2.csv

#./2_check a1.csv | grep magicnumber_a4a6b25c > a2.csv
./2_check a1.csv | grep magicnumber_a4a6b25c | head -n 1 > a2.csv
