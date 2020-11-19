package com.ctd.wasmappstore;

import android.app.Application;

import com.huawei.ide.TeeManager;

public class MyApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        TeeManager.getInstance().initX(this);
    }
}
