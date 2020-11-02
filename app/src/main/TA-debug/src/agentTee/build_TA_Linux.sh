#!/bin/bash
basepath=$(cd "$(dirname "$0")"; pwd)
cd ${basepath}
make clean
make -f makefile TOOL_CHAIN=1 ARM_GCC_TOOL_PATH=${1} 2>&1 | tee make_result.log