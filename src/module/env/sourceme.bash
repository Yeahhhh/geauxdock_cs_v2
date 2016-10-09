
APPROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
#echo $APPROOT

APPROOT=$APPROOT/..

if [ -d $APPROOT ]; then
    export PATH=$APPROOT/bin:$PATH

    export CPATH=$APPROOT:$CPATH

    export C_INCLUDE_PATH=$APPROOT:$C_INCLUDE_PATH
    export C_INCLUDE_PATH=$APPROOT/nvidia/cuda7example:$C_INCLUDE_PATH
    #export C_INCLUDE_PATH=$APPROOT/opencl:$C_INCLUDE_PATH

    export CPLUS_INCLUDE_PATH=$APPROOT:$CPLUS_INCLUDE_PATH
    export CPLUS_INCLUDE_PATH=$APPROOT/nvidia/cuda7example:$CPLUS_INCLUDE_PATH
    #export CPLUS_INCLUDE_PATH=$APPROOT/opencl:$CPLUS_INCLUDE_PATH

    export LIBRARY_PATH=$APPROOT/lib:$LIBRARY_PATH
    export LD_LIBRARY_PATH=$APPROOT/lib:$LD_LIBRARY_PATH


    #. $APPROOT/brendangregg/sourceme.bash
fi

unset APPROOT
