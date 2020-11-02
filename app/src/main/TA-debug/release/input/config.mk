#
# Copyright 2017, Huawei Co. Ltd.
#
#
# API_LEVEL indicates the GP internal API version of TA
# API_LEVEL=1 indicates GP internal API version 1.0
# API_LEVEL=2 indicates GP internal API version 1.1.1
# API_LEVEL=3 indicates GP internal API version 1.2
# If no API_LEVEL is specified, GP internal API version 1.0 will be taked
# For Huawei phone that version <= Emui9.0,  only TA of API_LEVEL=1 is support
# For Huawei phone that version >= Emui10.0, TA with any API_LEVEL is support
CFLAGS += -DAPI_LEVEL=2
