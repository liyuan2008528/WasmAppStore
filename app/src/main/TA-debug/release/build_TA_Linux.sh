#!/bin/bash
basepath=$(cd "$(dirname "$0")"; pwd)
cd ${basepath}
python signtool_v3.py 1 2 ./input ./output “” “” “” ./config/Config ./ta_cert/ta_key.pem
