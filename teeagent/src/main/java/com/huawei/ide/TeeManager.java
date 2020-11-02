package com.huawei.ide;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import com.payneteasy.tlv.BerTag;
import com.payneteasy.tlv.BerTlvBuilder;
import com.payneteasy.tlv.HexUtil;

import org.xutils.BuildConfig;
import org.xutils.DbManager;
import org.xutils.db.table.TableEntity;
import org.xutils.ex.DbException;
import org.xutils.x;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class TeeManager {

    //    private static final String secFileName = "98263abc-4138-4b59-9fe9-3c263c6e4e8b.sec";
    private static final String secFileName = "2c0af0e7-eda6-4839-bfee-c9167dd58a1b.sec";

    private static TeeManager teeManager;
    private static Context applicationContext;
    public static DbManager wasm_db;

    public TeeManager() {
    }

    public static TeeManager getInstance(Activity activity) {
        if (teeManager == null) {
            teeManager = new TeeManager();
        }
        applicationContext = activity.getApplicationContext();
        x.Ext.init(activity.getApplication());
        x.Ext.setDebug(BuildConfig.DEBUG); // 是否输出debug日志, 开启debug会影响性能.


        initDB();


        return teeManager;
    }

    private static void initDB() {

/**
 * 初始化DaoConfig配置
 */
        DbManager.DaoConfig daoConfig = new DbManager.DaoConfig()
                //设置数据库名，默认xutils.db
                .setDbName("wasmTA.db")
                //设置数据库路径，默认存储在app的私有目录
                .setDbDir(new File(applicationContext.getFilesDir().getAbsolutePath()))
                //设置数据库的版本号
                .setDbVersion(1)
                //设置数据库打开的监听
                .setDbOpenListener(new DbManager.DbOpenListener() {
                    @Override
                    public void onDbOpened(DbManager db) {
                        //开启数据库支持多线程操作，提升性能，对写入加速提升巨大
                        db.getDatabase().enableWriteAheadLogging();
                    }
                })
                //设置数据库更新的监听
                .setDbUpgradeListener(new DbManager.DbUpgradeListener() {
                    @Override
                    public void onUpgrade(DbManager db, int oldVersion, int newVersion) {
                    }
                })
                //设置表创建的监听
                .setTableCreateListener(new DbManager.TableCreateListener() {
                    @Override
                    public void onTableCreated(DbManager db, TableEntity<?> table) {
                        Log.i("JAVA_DB", "onTableCreated：" + table.getName());
                    }
                });
        //设置是否允许事务，默认true
        //.setAllowTransaction(true)

        try {

            wasm_db = x.getDb(daoConfig);
        } catch (DbException e) {
            e.printStackTrace();
        }
    }


    public String getTaResult() {
//        copyAssetsFile2Phone(applicationContext, secFileName);
//        String TAPath = applicationContext.getFilesDir().getAbsolutePath();
//        TAPath += ("/" + secFileName);
//        Tee tee = new Tee();
//        InputStream inputStream = null;
//        byte[] bytes = null;
//        try {
//            inputStream = applicationContext.getAssets().open("hello_world");
//            bytes = toByteArray(inputStream);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        String commond = "";
//        byte[] bytesCommond =  new BerTlvBuilder()
//                .addHex(new BerTag(0x3C), "56495341")
////                .addHex(new BerTag(0x3d), HexUtil.toHexString(bytes))
//                .buildArray();
//
//        Log.d("16进制", HexUtil.toHexString(bytesCommond)) ;
//
//        commond = HexUtil.toHexString(bytesCommond);


        return null;
    }

    public String getTaResult(byte[] wasm) {
        copyAssetsFile2Phone(applicationContext, secFileName);
        String TAPath = applicationContext.getFilesDir().getAbsolutePath();
        TAPath += ("/" + secFileName);
        Tee tee = new Tee();
//        InputStream inputStream = null;
//        byte[] bytes = null;
//        try {
//            inputStream = applicationContext.getAssets().open("hello_world");
//            bytes = toByteArray(inputStream);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
        String commond = "";
        byte[] bytesCommond = new BerTlvBuilder()
                .addHex(new BerTag(0x3C), "00000110AA0002bbcc")
//                .addHex(new BerTag(0x3d), HexUtil.toHexString(bytes))
                .buildArray();

        Log.d("16进制", HexUtil.toHexString(bytesCommond));

        commond = HexUtil.toHexString(bytesCommond);


        return tee.Run(TAPath, wasm, bytesCommond);
    }


    /**
     * Move the file from the assets directory to the /data/data/package name/files/ directory.
     * The files in the assets directory will be packaged into the APK package without compression.
     * They should also be exported from the apk package.
     *
     * @param fileName file name, such as aaa.txt
     */
    private static void copyAssetsFile2Phone(Context context, String fileName) {
        try {
            InputStream inputStream = context.getAssets().open(fileName);
            //getFilesDir() Get the current APP installation path:/data/data/package name/files directory
            File file = new File(context.getFilesDir().getAbsolutePath() + File.separator + fileName);
            if (!file.exists() || file.length() == 0) {
                //If the file does not exist, FileOutputStream will automatically create the file
                FileOutputStream fos = new FileOutputStream(file);
                int len = -1;
                byte[] buffer = new byte[1024];
                while ((len = inputStream.read(buffer)) != -1) {
                    fos.write(buffer, 0, len);
                }
                //Refresh buffer
                fos.flush();
                inputStream.close();
                fos.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static byte[] toByteArray(InputStream input) throws IOException {
        ByteArrayOutputStream output = new ByteArrayOutputStream();
        byte[] buffer = new byte[4096];
        int n = 0;
        while (-1 != (n = input.read(buffer))) {
            output.write(buffer, 0, n);
        }
        return output.toByteArray();
    }


}
