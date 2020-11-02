package com.ctd.teeagent.util;

import com.ctd.teeagent.Constant;

import org.xutils.common.Callback;
import org.xutils.http.RequestParams;
import org.xutils.x;

import java.util.Map;

import static com.ctd.teeagent.Constant.APP_DOMAIN;

public class HttpUtils {




    public static void agentPostRequest(Map<String,String> requestMap, final HandleResult handleResult){

        RequestParams params = new RequestParams(APP_DOMAIN + requestMap.get(Constant.REQUEST_URL));
        // params.setSslSocketFactory(...); // 如果需要自定义SSL
        params.setAsJsonContent(true);
        params.addBodyParameter("agent", "1.0.0");
        params.setSslSocketFactory(TrustAllCerts.createSSLSocketFactory());
        params.setHostnameVerifier(new TrustAllCerts.TrustAllHostnameVerifier());
        params.addHeader("X-TAM-Protocol", "GDP.TEE.1.0.0.0");

        requestMap.remove(Constant.REQUEST_URL);
        for(String key:requestMap.keySet()){//keySet获取map集合key的集合  然后在遍历key即可
            params.addBodyParameter(key,requestMap.get(key));
        }



        x.http().post(params, new Callback.CommonCallback<String>() {
            @Override
            public void onSuccess(String result) {
                handleResult.onSuccess(result);


            }

            @Override
            public void onError(Throwable ex, boolean isOnCallback) {
//                Toast.makeText(x.app(), ex.getMessage(), Toast.LENGTH_LONG).show();
            }

            @Override
            public void onCancelled(CancelledException cex) {
//                Toast.makeText(x.app(), "cancelled", Toast.LENGTH_LONG).show();
            }

            @Override
            public void onFinished() {

            }
        });
    }


    public static void agentGetRequest(Map<String,String> requestMap, final HandleResult handleResult){
        RequestParams params = new RequestParams(APP_DOMAIN + "/test/file/download?file=hello_world.wta");
        // params.setSslSocketFactory(...); // 如果需要自定义SSL
//        params.addParameter("agent", "1.0.0");
        params.setSslSocketFactory(TrustAllCerts.createSSLSocketFactory());
        params.setHostnameVerifier(new TrustAllCerts.TrustAllHostnameVerifier());
        params.addHeader("X-TAM-Protocol", "GDP.TEE.1.0.0.0");

        for(String key:requestMap.keySet()){//keySet获取map集合key的集合  然后在遍历key即可
            params.addBodyParameter(key,requestMap.get(key));
        }

        x.http().get(params, new Callback.CommonCallback<String>() {
            @Override
            public void onSuccess(String result) {

                handleResult.onSuccess(result);


            }

            @Override
            public void onError(Throwable ex, boolean isOnCallback) {
//                Toast.makeText(x.app(), ex.getMessage(), Toast.LENGTH_LONG).show();
            }

            @Override
            public void onCancelled(CancelledException cex) {
//                Toast.makeText(x.app(), "cancelled", Toast.LENGTH_LONG).show();
            }

            @Override
            public void onFinished() {

            }
        });
    }


   public interface HandleResult{
       void onSuccess(String result);
    }


}
