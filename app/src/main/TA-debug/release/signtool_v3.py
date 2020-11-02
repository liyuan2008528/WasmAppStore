#!/usr/bin/env python
# coding:utf-8
#----------------------------------------------------------------------------
# Copyright © Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
# tools for generating a trusted application load image
#----------------------------------------------------------------------------

import struct
import sys
import os
import hashlib
import binascii
import subprocess

from manifest import *

DEBUG      = 0
VERSION     = 3
TA_VERSION     = 3
# TA_TYPE 1 stand for v3.0
# TA_TYPE 2 stand for v3.1(with config and cert)
TA_TYPE    = 0

SERVER_IP  = ""
PASSWORD   = ""
USERNAME   = ""

MAGIC1         = 0xA5A55A5A
MAGIC2         = 0x55AA

# key is derived from root key
KEY_VERSION    = 0x0002

SIGN_ALG_V3    = 0x10002048
SIGN_ALG_V4    = 0x10004096

HASH256_LEN    = 256
HASH512_LEN    = 512

ENCRYPTED_KEYINFO_LEN = 256
SIGNATURE_LEN_256      = 256
SIGNATURE_LEN_512      = 512

SUCCESS = 0

# ELF Definitions
ELF_TYPE                  = 32
ELF_HDR_SIZE              = 52
ELF_PHDR_SIZE             = 32
ELFINFO_MAG0_INDEX        = 0
ELFINFO_MAG1_INDEX        = 1
ELFINFO_MAG2_INDEX        = 2
ELFINFO_MAG3_INDEX        = 3
ELFINFO_MAG0              = '\x7f'
ELFINFO_MAG1              = 'E'
ELFINFO_MAG2              = 'L'
ELFINFO_MAG3              = 'F'
ELFINFO_CLASS_INDEX       = 4
ELFINFO_CLASS             = '\x01'
ELFINFO_VERSION_INDEX     = 6
ELFINFO_VERSION_CURRENT   = '\x01'
ELF_BLOCK_ALIGN           = 0x1000
ELF_HEAD_FORMAT           = ''

# ELF Program Header Types
NULL_TYPE                 = 0x0
LOAD_TYPE                 = 0x1
DYNAMIC_TYPE              = 0x2
INTERP_TYPE               = 0x3
NOTE_TYPE                 = 0x4
SHLIB_TYPE                = 0x5
PHDR_TYPE                 = 0x6
TLS_TYPE                  = 0x7

#----------------------------------------------------------------------------
# ELF Header Class
#----------------------------------------------------------------------------
class Elf_Ehdr:
   def __init__(self, data):
      # Structure object to align and package the ELF Header
      if(ELF_TYPE == 64):
         self.s = struct.Struct('16sHHIQQQIHHHHHH')
      else:
         self.s = struct.Struct('16sHHIIIIIHHHHHH')

      unpacked_data       = (self.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.e_ident        = unpacked_data[0]
      self.e_type         = unpacked_data[1]
      self.e_machine      = unpacked_data[2]
      self.e_version      = unpacked_data[3]
      self.e_entry        = unpacked_data[4]
      self.e_phoff        = unpacked_data[5]
      self.e_shoff        = unpacked_data[6]
      self.e_flags        = unpacked_data[7]
      self.e_ehsize       = unpacked_data[8]
      self.e_phentsize    = unpacked_data[9]
      self.e_phnum        = unpacked_data[10]
      self.e_shentsize    = unpacked_data[11]
      self.e_shnum        = unpacked_data[12]
      self.e_shstrndx     = unpacked_data[13]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.e_ident,
                self.e_type,
                self.e_machine,
                self.e_version,
                self.e_entry,
                self.e_phoff,
                self.e_shoff,
                self.e_flags,
                self.e_ehsize,
                self.e_phentsize,
                self.e_phnum,
                self.e_shentsize,
                self.e_shnum,
                self.e_shstrndx
               ]

      return (self.s).pack(*values)

#----------------------------------------------------------------------------
# Verify ELF header contents from an input ELF file
#----------------------------------------------------------------------------
def verify_elf_header(elf_header):
    if (elf_header.e_ident[ELFINFO_MAG0_INDEX] != ELFINFO_MAG0) or \
        (elf_header.e_ident[ELFINFO_MAG1_INDEX] != ELFINFO_MAG1) or \
        (elf_header.e_ident[ELFINFO_MAG2_INDEX] != ELFINFO_MAG2) or \
        (elf_header.e_ident[ELFINFO_MAG3_INDEX] != ELFINFO_MAG3) or \
        (elf_header.e_ident[ELFINFO_CLASS_INDEX] != ELFINFO_CLASS) or \
        (elf_header.e_ident[ELFINFO_VERSION_INDEX] != ELFINFO_VERSION_CURRENT):

        return False
    else:
        return True

def get_elf_type(elfFile):
    EI_NIDENT = 16
    global ELF_TYPE
    global ELF_HDR_SIZE
    global ELF_HEAD_FORMAT
    global ELFINFO_CLASS

    elfFile.seek(0x0L, 0)
    e_ident = elfFile.read(EI_NIDENT)

    ''' check EI_CLASS, 32-bit or 64-bit'''
    if ord(e_ident[4]) == 2:
        ELF_TYPE = 64
        ELF_HDR_SIZE = 64
        ELF_HEAD_FORMAT = "HHIQQQIHHHHHH"
        ELFINFO_CLASS = "\x02"
    elif ord(e_ident[4]) == 1:
        ELF_TYPE = 32
        ELF_HDR_SIZE = 52
        ELF_HEAD_FORMAT = "HHIIIIIHHHHHH"
        ELFINFO_CLASS = "\x01"
    else:
        raise RuntimeError, "Unknown ELF file type"
    return

def generateHeader(contentLen):
    return struct.pack('IHHII', MAGIC1, MAGIC2, VERSION, contentLen, KEY_VERSION)

def generateAesKeyInfo(ivFilePath, keyFilePath, outFilePath):
    randIVCmd = "openssl rand -out " + ivFilePath + " 16 "
    randKeyCmd = "openssl rand -out " + keyFilePath + " 32 "
    try:
        subprocess.check_output(randIVCmd, shell=True)
        subprocess.check_output(randKeyCmd, shell=True)
    except:
        print "rand operation failed"
        raise RuntimeError

    outFile = open(outFilePath, 'wb')

    outFile.write(struct.pack('I', 32))
    outFile.write(struct.pack('I', 16))
    if DEBUG == 0 or TA_TYPE == 1:
        outFile.write(struct.pack('I', SIGN_ALG_V3))
    elif TA_TYPE == 2:
        outFile.write(struct.pack('I', SIGN_ALG_V4))
    else:
        print "target sign type is not supported: " + str(TA_TYPE)
        raise RuntimeError

    keyFile = open(keyFilePath, 'r')
    outFile.write(keyFile.read(32))

    ivFile = open(ivFilePath, 'r')
    outFile.write(ivFile.read(16))

    outFile.close()
    return

def encryptAesKeyInfo(pubkeyFilePath, inFilePath, outFilePath):
    encCmd = "openssl rsautl -encrypt -pubin -oaep " \
            + " -inkey " + pubkeyFilePath \
            + " -in "    + inFilePath \
            + " -out "   + outFilePath
    try:
        subprocess.check_output(encCmd, shell=True)
    except:
        print "RSA encrypt operation failed"
        raise RuntimeError
    return

def generateHash(hashLen, inFilePath, outFilePath):
    inFileSize = os.path.getsize(inFilePath)
    inFile = open(inFilePath, 'rb')
    # Initialize a SHA256 object from the Python hash library
    if hashLen == HASH256_LEN:
        hashOp = hashlib.sha256()
    elif hashLen == HASH512_LEN:
        hashOp = hashlib.sha512()
    # Set the input buffer and return the output digest
    hashOp.update(inFile.read(inFileSize))
    inFile.close()

    #-----hash file used for ras sign---
    with open(outFilePath, 'wb') as hash_fp:
        # fixed hash prefix value
        hash_fp.write(struct.pack('B'*19, 0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60,
            0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20))
        hash_fp.write(hashOp.digest())
    return

def generateSignature(priKeyPath, inFilePath, outFilePath):
    if DEBUG == 1:
        print "generate dummy signature for DEBUG version"
        f = open(outFilePath, 'wb')
        if TA_TYPE == 1:
            f.write('\0'*256)
        elif TA_TYPE == 2:
            signCmd = "openssl rsautl -sign" \
                    + " -inkey " + priKeyPath \
                    + " -in "    + inFilePath \
                    + " -out "   + outFilePath
            try:
                subprocess.check_output(signCmd, shell=True)
            except:
                print "sign operation failed"
                raise RuntimeError
        f.close()
    else :
        privKeyName = '/root/Key-TA/TA_privatekey'
        signCmd = 'java -jar tool/NativeCASign.jar %s %s %s %s %s %s' \
                %(SERVER_IP, USERNAME, PASSWORD, privKeyName, inFilePath, outFilePath)
        try:
            print "signing..."
            subprocess.check_output(signCmd, shell=True)
        except:
            print "sign operation failed"
            raise RuntimeError
    return

def generateRawData(manifestDataPath, manifestExtFilePath, elfFilePath, configFilePath, rawFilePath):
    manifestDataSize = os.path.getsize(manifestDataPath)
    manifestExtSize = os.path.getsize(manifestExtFilePath)
    elfFileSize = os.path.getsize(elfFilePath)
    configFileSize = 0

    f = open(rawFilePath, 'wb')
    header  = ""
    if TA_TYPE == 2:
        configFileSize = os.path.getsize(configFilePath)
    header = struct.pack('IIIII', TA_VERSION, manifestDataSize, manifestExtSize, elfFileSize, configFileSize)
    f.write(header)

    manifestData = open(manifestDataPath, 'rb')
    f.write(manifestData.read(manifestDataSize))
    manifestData.close()

    manifestExt = open(manifestExtFilePath, 'rb')
    f.write(manifestExt.read(manifestExtSize))
    manifestExt.close()

    elfFile = open(elfFilePath, 'rb')
    get_elf_type(elfFile)
    elfFile.seek(0x0L, 0)
    elfFileHaderBuf = elfFile.read(ELF_HDR_SIZE)
    elfFileHader = Elf_Ehdr(elfFileHaderBuf)
    if verify_elf_header(elfFileHader) is False:
        print "verify elf header failed"
        raise RuntimeError
    elfFile.seek(0x0L, 0)
    f.write(elfFile.read(elfFileSize))
    elfFile.close()

    if TA_TYPE == 2:
        configFile = open(configFilePath, 'rb')
        f.write(configFile.read(configFileSize))
        configFile.close()
    f.close()
    return

def aesEncrypt(keyPath, ivPath, inFilePath, outfilePath):
    keySize = os.path.getsize(keyPath)
    key = open(keyPath, 'rb')
    keyData = struct.unpack("s"*32, key.read(keySize))
    keyStr = ''
    for chr in keyData:
        keyStr = keyStr + chr
    hexKeyStr = binascii.b2a_hex(keyStr)

    ivSize = os.path.getsize(ivPath)
    iv = open(ivPath, 'rb')
    ivData = struct.unpack("s"*16, iv.read(ivSize))
    ivStr = ''
    for chr in ivData:
        ivStr = ivStr + chr
    hexIvStr = binascii.b2a_hex(ivStr)

    encCmd = "openssl enc -aes-256-cbc" \
            + " -in "  + inFilePath \
            + " -out " + outfilePath \
            + " -K "   + hexKeyStr \
            + " -iv "  + hexIvStr
    key.close()
    iv.close()
    try:
        subprocess.check_output(encCmd, shell=True)
    except:
        print "AES encrypt operation failed"
        raise RuntimeError

    return

def ParseTaApiLevel(taMakeConfig):
    defaultApiLevel = 1
    if not os.path.exists(taMakeConfig):
        print("TA Make Config doesn't exist, ignore it")
        return defaultApiLevel
    with open(taMakeConfig) as f:
        for line in f:
            if line.startswith("#") or not "-DAPI_LEVEL" in line:
                continue
            key, value = line.strip().split("-DAPI_LEVEL=")
            print("ta_api_level = {}".format(value))
            return value
    return defaultApiLevel

def updateManifestTaApiLevel(taMakeConfig, manifest):
    data = ''
    with open(manifest, 'r') as f:
        for line in f:
            if line.startswith("#") or not "gpd.ta.api_level" in line:
                data += line
    line = "\ngpd.ta.api_level:{}\n".format(ParseTaApiLevel(taMakeConfig))
    data += line
    with open(manifest, "wb") as f:
        f.writelines(data)

def generateDataForSign(contentLen, keyInfoFilePath, rawFilePath, dataForSignPath):
    keyInfoLen = os.path.getsize(keyInfoFilePath)
    keyInfo = open(keyInfoFilePath, 'rb')

    rawFileLen = os.path.getsize(rawFilePath)
    rawFile = open(rawFilePath, 'rb')

    with open(dataForSignPath, 'wb') as dataForSign:
        dataForSign.write(generateHeader(contentLen))
        dataForSign.write(keyInfo.read(keyInfoLen))
        dataForSign.write(rawFile.read(rawFileLen))

    keyInfo.close()
    rawFile.close()

def  generateSecImage(inPath, outPath, priKeyPath, configFilePath):
    #temp files
    ivFilePath = inPath + "/iv.bin"
    keyFilePath = inPath + "/aeskey.bin"
    keyInfoFilePath = inPath + "/KeyInfo"
    encKeyInfoFilePath = inPath + "/KeyInfo.enc"
    rawFilePath = inPath + "/rawData"
    encRawFilePath = inPath + "/rawData.enc"
    manifestDataPath = inPath + "/manifestData.bin"
    manifestExtPath = inPath + "/manifestExt.bin"
    dataForSignPath = inPath + "/dataForSign.bin"
    signatureFilePath = inPath + "/signature.bin"
    rawDataHashPath = inPath + "/rawDataHash.bin"

    #mandentory input files
    manifestFilePath = inPath + "/manifest.txt"
    elfFilePath = inPath + "/combine.o"
    apiConfigFilePath = inPath + "/config.mk"

    #preload files
    pubkeyFilePath = os.getcwd() + "/rsa_public_key.pem"

    (ret, productName, flag) = parserManifest(manifestFilePath, manifestDataPath, manifestExtPath)
    updateManifestTaApiLevel(apiConfigFilePath, manifestExtPath)

    generateRawData(manifestDataPath, manifestExtPath, elfFilePath, configFilePath, rawFilePath)

    #generate AES key info to encrypt raw data
    generateAesKeyInfo(ivFilePath, keyFilePath, keyInfoFilePath)
    encryptAesKeyInfo(pubkeyFilePath, keyInfoFilePath, encKeyInfoFilePath)

    aesEncrypt(keyFilePath, ivFilePath, rawFilePath, encRawFilePath)

    contentLen = 0
    if DEBUG == 0 or TA_TYPE == 1:
        contentLen = ENCRYPTED_KEYINFO_LEN + SIGNATURE_LEN_256 + os.path.getsize(encRawFilePath)
    elif TA_TYPE == 2:
        contentLen = ENCRYPTED_KEYINFO_LEN + SIGNATURE_LEN_512 + os.path.getsize(encRawFilePath)
    else:
        print "target sign type is not supported: " + str(TA_TYPE)
        raise RuntimeError

    generateDataForSign(contentLen, keyInfoFilePath, rawFilePath, dataForSignPath)

    generateHash(HASH256_LEN, dataForSignPath, rawDataHashPath)

    generateSignature(priKeyPath, rawDataHashPath, signatureFilePath)

    secImagePath = outPath + "/" + productName
    secImage = open(secImagePath, 'wb')
    # write to sec file [1.header info]
    secImage.write(generateHeader(contentLen))
    # write to sec file [2.AES key info]
    encKeyInfoSize = os.path.getsize(encKeyInfoFilePath)
    encKeyInfo = open(encKeyInfoFilePath, 'rb')
    secImage.write(encKeyInfo.read(encKeyInfoSize))
    encKeyInfo.close()
    # write to sec file [3.signature]
    signatureSize = os.path.getsize(signatureFilePath)
    signatureFile = open(signatureFilePath, 'rb')
    secImage.write(signatureFile.read(signatureSize))
    signatureFile.close()
    # write to sec file [4.encrypted raw data]
    encRawDataSize = os.path.getsize(encRawFilePath)
    encRawData = open(encRawFilePath, 'rb')
    secImage.write(encRawData.read(encRawDataSize))
    encRawData.close()
    secImage.close()

    print "=========================SUCCESS============================"
    print "generate TA(V3) load image success: "
    print secImagePath
    print "============================================================"

    #remove temp files
    os.remove(ivFilePath)
    os.remove(keyFilePath)
    os.remove(keyInfoFilePath)
    os.remove(encKeyInfoFilePath)
    os.remove(rawFilePath)
    os.remove(encRawFilePath)
    os.remove(manifestDataPath)
    os.remove(manifestExtPath)
    os.remove(signatureFilePath)
    os.remove(dataForSignPath)
    os.remove(rawDataHashPath)
    return

if __name__ == '__main__':
    argvs = sys.argv
    priKeyPath = ""
    configFilePath = ""
    DEBUG = int(argvs[1])
    TA_TYPE = int(argvs[2])
    inPath = argvs[3]
    outPath = argvs[4]
    SERVER_IP = argvs[5]
    USERNAME = argvs[6]
    PASSWORD = argvs[7]
    if TA_TYPE == 2:
        configFilePath = argvs[8]
        if DEBUG == 1:
            priKeyPath = argvs[9]

    generateSecImage(inPath, outPath, priKeyPath, configFilePath)
