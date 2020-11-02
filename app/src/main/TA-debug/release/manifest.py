import string
import struct
import uuid
import os

PRODUCT_TA_IMAGE        = 1
PRODUCT_DYN_LIB         = 2
PRODUCT_SERVICE_IMAGE   = 3

class TEE_UUID:
    # Structure object to align and package the TEE_UUID
    s = struct.Struct('IHH8b')

    def __init__(self, data):
        unpacked_data       = (TEE_UUID.s).unpack(data)
        self.unpacked_data  = unpacked_data
        self.timeLow        = unpacked_data[0]
        self.timeMid        = unpacked_data[1]
        self.timeHiAndVersion = unpacked_data[2]
        self.clockSeqAndNode  = unpacked_data[3]

    def printValues(self):
        print "ATTRIBUTE / VALUE"
        for attr, value in self.__dict__.iteritems():
            print attr, value

    def getPackedData(self):
        values = [self.timeLow,
                self.timeMid,
                self.timeHiAndVersion,
                self.clockSeqAndNode,
                ]

        return (TEE_UUID.s).pack(*values)


#----------------------------------------------------------------------------
# Manifest
#----------------------------------------------------------------------------
class Manifest:

    # Structure object to align and package the Manifest
    s = struct.Struct('I' * 6)

    def __init__(self, data):
        unpacked_data       = (Manifest.s).unpack(data)
        self.unpacked_data  = unpacked_data
        self.single_instance = unpacked_data[0]
        self.multi_session  = unpacked_data[1]
        self.multi_command  = unpacked_data[2]
        self.heap_size      = unpacked_data[3]
        self.stack_size     = unpacked_data[4]
        self.instancekeepalive = unpacked_data[5]

    def printValues(self):
        print "ATTRIBUTE / VALUE"
        for attr, value in self.__dict__.iteritems():
            print attr, value

    def getPackedData(self):
        values = [self.single_instance,
                self.multi_session,
                self.multi_command,
                self.heap_size,
                self.stack_size,
                self.instancekeepalive,
                ]

        return (Manifest.s).pack(*values)

#----------------------------------------------------------------------------
# verify property name in manifest file
#----------------------------------------------------------------------------
def verify_property_name(strLine):
    print 'verify property name'
    alphas = string.letters + string.digits
    cont = alphas + '-' + '_' + '.'
    if len(strLine) > 1:
        if strLine[0] not in alphas:
            print 'invalid first letter in property name'
            return False
        else:
            for otherchar in strLine[1:]:
                if otherchar not in cont:
                    print 'invalid char in property name'
                    return False
    else:
        print 'invalid property name'
        return False

    return True

#----------------------------------------------------------------------------
# verify property value in manifest file
#----------------------------------------------------------------------------
def verify_property_value(strLine):
    print 'verify property value'
    filt_letter = chr(0) + chr(10) +chr(13)
    for thechar in strLine:
        if thechar in filt_letter:
            print 'invalid letter in prop value'
            return False
    return True

#----------------------------------------------------------------------------
# remove tabs and space in property value
#----------------------------------------------------------------------------
def trailing_space_tabs(strLine):
    print 'trailing space tabs in value head and trail'
    space_tabs = chr(9) + chr(32) +chr(160)
    space_tabs_newlines = space_tabs + chr(10) +chr(13)
    print 'tab:'+space_tabs

    print 'str in: '+strLine
    index = 0
    for thechar in strLine:
        if thechar in space_tabs:
            index += 1
        else:
            break
    headvalue = strLine[index:]

    strlen = len(headvalue)

    strlen -= 1

    while strlen > 0:
        if headvalue[strlen] in space_tabs_newlines:
            strlen -= 1
        else:
            break

    #print 'str len: '+str(strlen)
    strRet = headvalue[0:strlen+1] + chr(10)
    print 'str ret: '+strRet

    return strRet

#----------------------------------------------------------------------------
# verify manifest file, parse manifest file, generate a new manfiest file
#----------------------------------------------------------------------------
def parserManifest(manifestFilePath, manifestDataPath, manifestExtPath):
    print 'verify manifest'
    targetType = PRODUCT_TA_IMAGE

    uuid_val_flag = 1
    uuid_val = TEE_UUID('\0' * 16)

    #manifest default
    manifest_val = Manifest('\0'*24)

    manifest_val.single_instance = 1
    manifest_val.multi_session = 0
    manifest_val.multi_command = 0
    manifest_val.instancekeepalive = 0
    manifest_val.heap_size = 16384
    manifest_val.stack_size = 2048

    service_name = 'external_service'

    manif_fp = open(manifestFilePath, 'r')

    string_mani_fp = open(manifestExtPath, 'wb')
    for eachLine in manif_fp:
        print eachLine
        if eachLine.startswith("#") or not len(eachLine.strip()):
            continue
        index = eachLine.find(':', 1, len(eachLine))
        #print 'index name : value is ' + str(index)

        prop_name = eachLine[0:index] #no ':'
        prop_name_t = eachLine[0:index+1] #with ':'
        prop_value_t = eachLine[index+1:]
        print 'name is :'+str(prop_name) + '; value is :'+str(prop_value_t)

        prop_value = trailing_space_tabs(prop_value_t)
        prop_len = len(prop_value)
        prop_value_v = prop_value[0:prop_len-1]# mv last letter
        print 'prop value_v: ' + prop_value_v

        if verify_property_name(prop_name) is False:
            print 'manifest format invalid, please check it'
            return (False, 0, 0, 0)

        if verify_property_value(prop_value_v) is False:
            print 'manifest format invalid, please check it'
            return (False, 0, 0, 0)

        # name:value to lowcase, and parse manifest
        prop_name_low = prop_name.lower()
        print "name lower: "+prop_name_low
        if cmp('gpd.ta.appid', prop_name_low) == 0:
            print "compare name is srv id"
            uuid_val = uuid.UUID(prop_value_v)
            uuid_val_flag = 0
            print 'uuid str'+ str(uuid_val)
            print 'val fields'+ str(uuid_val.fields)

        elif cmp('gpd.ta.singleinstance', prop_name_low) == 0:
            prop_value_low = prop_value_v.lower()
            if cmp('true', prop_value_low) == 0:
                manifest_val.single_instance = 1;
            elif cmp('false', prop_value_low) == 0:
                manifest_val.single_instance = 0;
            else:
                print 'single_instance value error!'

        elif cmp('gpd.ta.multisession', prop_name_low) == 0:
            prop_value_low = prop_value_v.lower()
            if cmp('true', prop_value_low) == 0:
                manifest_val.multi_session = 1;
            elif cmp('false', prop_value_low) == 0:
                manifest_val.multi_session = 0;
            else:
                print 'multi_session value error!'

        elif cmp('gpd.ta.multicommand', prop_name_low) == 0:
            prop_value_low = prop_value_v.lower()
            if cmp('true', prop_value_low) == 0:
                manifest_val.multi_command = 1;
            elif cmp('false', prop_value_low) == 0:
                manifest_val.multi_command = 0;
            else:
                print 'multi_command value error!'

        elif cmp('gpd.ta.instancekeepalive', prop_name_low) == 0:
            prop_value_low = prop_value_v.lower()
            if cmp('true', prop_value_low) == 0:
                manifest_val.instancekeepalive = 1;
            elif cmp('false', prop_value_low) == 0:
                manifest_val.instancekeepalive = 0;
            else:
                print 'instancekeepalive value error!'

        elif cmp('gpd.ta.datasize', prop_name_low) == 0:
            #manifest_val.heap_size = prop_value_v.atoi()
            manifest_val.heap_size = int(prop_value_v)
            print 'b'

        elif cmp('gpd.ta.stacksize', prop_name_low) == 0:
            #manifest_val.stack_size = prop_value_v.atoi()
            manifest_val.stack_size = int(prop_value_v)
            print 'b'

        elif cmp('gpd.ta.service_name', prop_name_low) == 0:
            #manifest_val.stack_size = prop_value_v.atoi()
            service_name = prop_value_v
            print 'b'

        else:
            print 'b'
            #write have not paresed manifest into sample.manifest file
            string_mani_fp.write(prop_name_t)
            string_mani_fp.write(prop_value)
            if cmp('gpd.ta.is_tee_service', prop_name_low) == 0:
                prop_value_low = prop_value_v.lower()
                if cmp('true', prop_value_low) == 0:
                     targetType = PRODUCT_SERVICE_IMAGE
            elif cmp('gpd.ta.is_lib', prop_name_low) == 0:
                prop_value_low = prop_value_v.lower()
                if cmp('true', prop_value_low) == 0:
                    targetType = PRODUCT_DYN_LIB

        #write the whole parsed manifest into sample.manifest file

    manif_fp.close()
    string_mani_fp.close()

    service_name_len = len(service_name)
    print 'service name: ' + service_name
    print 'service name len: ' + str(service_name_len)
    if service_name_len > 64:
        print "service name len exceed MAX value 27"
        raise RuntimeError

    # get manifest string file len
    manifest_str_size = os.path.getsize(manifestExtPath)
    if manifest_str_size > 152:
        print "extra manifest string exceed MAX len 152"
        raise RuntimeError
    print 'manifest str size' + str(manifest_str_size)

    # 2> manifest + service_name
    print "bytes len %d" % len(uuid_val.bytes_le)
    print "bytes len %d" % len(manifest_val.getPackedData())
    print "bytes len %d" % len(service_name)

    # 3> unparsed manifest, string manifest
    string_mani_fp = open(manifestExtPath, 'rb')
    print "read manifest string size %d" % manifest_str_size
    manifest_string_buf = string_mani_fp.read(manifest_str_size)
    print "manifest strint: %s" % manifest_string_buf
    string_mani_fp.close()

    #---- write manifest parse context to manifest file
    out_manifest_fp = open(manifestDataPath, 'wb')
    out_manifest_fp.write(uuid_val.bytes_le)
    out_manifest_fp.write(service_name)
    out_manifest_fp.write(manifest_val.getPackedData())
    out_manifest_fp.close()

    productName = str(uuid_val)
    if targetType == PRODUCT_TA_IMAGE:
        print "product type is ta image"
        productName = productName + ".sec"
    elif targetType == PRODUCT_SERVICE_IMAGE:
        print "product type is service"
        productName = productName + service_name + "_svr.sec"
    elif targetType == PRODUCT_DYN_LIB:
        print "product type is dyn lib"
        productName = productName + service_name + ".so.sec"
    else:
        print "invalid product type!"
        raise RuntimeError

    return (True, productName, uuid_val_flag)
