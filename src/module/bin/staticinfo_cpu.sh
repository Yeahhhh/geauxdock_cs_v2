#!/bin/sh

#
# print CPU info
#
# dependencies
#     /proc/cpuinfo
#
# tested environement
#     Linux 2.6.32
#     Linux 3.16.0
#


CPUFILE=/proc/cpuinfo
test -f $CPUFILE || exit 1

SOCKET=`grep "physical id" $CPUFILE | sort -u | wc -l`
HWTH=`grep "processor" $CPUFILE | wc -l`
CORE=`grep "core id" $CPUFILE | sort -u | wc -l`

echo "`grep "model name" $CPUFILE | sort -u | cut -d : -f 2-`"
echo "cache: `grep "cache size" $CPUFILE | sort -u | cut -d : -f 2-`"
echo "socket(s):             $SOCKET"
echo "core(s) per socket:    $CORE"
echo "hwthread(s):           $HWTH"

