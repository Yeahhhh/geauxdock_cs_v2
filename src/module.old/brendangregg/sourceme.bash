
APPROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
#echo $APPROOT


if [ -d $APPROOT ]; then
    export PATH=$APPROOT/FlameGraph:$PATH
    export PATH=$APPROOT/HeatMap:$PATH
    export PATH=$APPROOT/perf-tools:$PATH
    export PATH=$APPROOT/systemtap-lwtools:$PATH
fi

unset APPROOT



