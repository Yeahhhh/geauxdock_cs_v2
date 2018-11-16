#!/bin/sh

this_file=$(readlink -f "$0")
this_dir=$(dirname "${this_file}")
cd $this_dir

func_exit()
{
    rv=$1
    echo "Detect a failture exit status. rv=$rv"
    echo "Exit"
    exit $rv
}

func_wrapper()
{
    echo "##############################################"
    echo "$@"
    echo ""
    $@ || func_exit $?
    echo ""
}


# Preparing The Input Data in CSV format.
func_wrapper ./1_mklist.py.sh_astex_1a07C1


# Loading and check the input data without further computations.
# THIS STEP IS OPTIONAL
#   You should run this step if you are feeding Geauxdock with a big multi-line CSV input
#   and prevent a row bad parameter crash your whole simulation
# IF YOU SKIP THIS STEP
#   "data2.csv" will not be generated
#   you can feed "3_geauxdock" with "data1.csv"
func_wrapper ./2_check.sh


# Running Geauxdock.
func_wrapper ./3_geauxdock data2.csv

