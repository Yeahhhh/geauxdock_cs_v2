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


func_wrapper ./1_mklist.py.sh_jewel
func_wrapper ./2_check.sh
func_wrapper ./3_geauxdock

