package com.huawei.ide;


public class Tee {

    String str = new String();

    static {
      //  System.loadLibrary("teec");
        System.loadLibrary("tee-lib");


    }

    public native String stringFromJNI(String param,byte[] wasmTA,byte[] commandId);


    public String Run(String path,byte[] wasmTA,byte[] commandId) {
        if (path == null)
            return "Failed";
        str = stringFromJNI(path,wasmTA,commandId);
        return str;
    }


}
