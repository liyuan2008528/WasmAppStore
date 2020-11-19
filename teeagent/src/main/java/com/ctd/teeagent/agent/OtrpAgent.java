package com.ctd.teeagent.agent;

import android.util.Base64;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import com.ctd.teeagent.Constant;
import com.ctd.teeagent.model.TeeDeviceResponseBean;
import com.ctd.teeagent.model.WasmTaBean;
import com.ctd.teeagent.util.GsonUtil;
import com.ctd.teeagent.util.HttpUtils;
import com.huawei.ide.TeeManager;

import org.xutils.common.util.MD5;
import org.xutils.ex.DbException;
import org.xutils.x;

import java.util.HashMap;
import java.util.List;

public class OtrpAgent implements OtrpInterface {


    public static void getHttp() {


    }


    public static void getGetHttp(final TeeManager teeManager, final TextView tv1) {
        HashMap<String, String> requestMap = new HashMap();
        HttpUtils.agentGetRequest(requestMap, new HttpUtils.HandleResult() {

            @Override
            public void onSuccess(String result) {
                String aa = "AGFzbQEAAAABIwZgA39_fwF_YAF_AX9gAn9_AX9gAX8AYAABf2AEf39_fwF_AlkHA2VudgZtZW1zZXQAAANlbnYEcHV0cwABA2VudgZtYWxsb2MAAQNlbnYHc3RybmNweQAAA2VudgZwcmludGYAAgNlbnYGc3RybGVuAAEDZW52BGZyZWUAAwMIBwQEBAQABQMEBQFwAQEBBQMBAAEGEwN_AUHwKwt_AEHsCwt_AEHwKwsHegcGbWVtb3J5AgASV0FfT25Jbml0VEFTZXNzaW9uAAcSV0FfT25PcGVuVEFTZXNzaW9uAAgSV0FfT25JbnZva2VDb21tYW5kAAkTV0FfT25DbG9zZVRBU2Vzc2lvbgAKCl9fZGF0YV9lbmQDAQtfX2hlYXBfYmFzZQMCCpMFBxMAQZSLgIAAQQBB2AAQgICAgAALLAEBf0EAQQAoApiLgIAAQZyLgIAAQZSLgIAAEIuAgIAAIgA2AsCLgIAAIAALOAEBf0EAQQAoApSLgIAAQQAoAryLgIAAQQAoApiLgIAAQZyLgIAAEIyAgIAAIgA2AsCLgIAAIAALEwBBACgClIuAgAAQjYCAgABBAAuEAQECfyOAgICAAEEQayIDJICAgIAAQbGKgIAAEIGAgIAAGiACQeQAEIKAgIAAIgQ2AgACQAJAIARFDQAgBEGAiICAAEHkABCDgICAABogAyACKAIANgIAQYuIgIAAIAMQhICAgAAaDAELQeGKgIAAEIGAgIAAGgsgA0EQaiSAgICAAEEAC7UCAQF_I4CAgIAAQdAAayIEJICAgIAAIAQgADYCQEGoiICAACAEQcAAahCEgICAABoCQCAARQ0AIAQgADYCMEHbiICAACAEQTBqEISAgIAAGgsCQAJAIAFBAUcNAAJAIAJBgMABRg0AQfaKgIAAEIGAgIAAGkGGgHwhAAwCCwJAAkAgAygCGCIARQ0AIANBHGooAgAiAUH_AUsNAQsgBEGGgHw2AhBB-oiAgAAgBEEQahCEgICAABogA0EcaigCACEBIAMoAhghAAsgA0EcaiAAQZ-KgIAAIAFBf2oQg4CAgAAQhYCAgAA2AgAgBEEBNgIAQaOJgIAAIAQQhICAgAAaQQAhAAwBCyAEIAE2AiBBzomAgAAgBEEgahCEgICAABpBgqB9IQALIARB0ABqJICAgIAAIAALRgEBfyOAgICAAEEQayIBJICAgIAAIAEgADYCAEHniYCAACABEISAgIAAGgJAIABFDQAgABCGgICAAAsgAUEQaiSAgICAAAsLmwMBAEGACAuTA2hlbGxvIHdhc20Ad2FzbTogY3JlYXRlZCBzZXNzaW9uIFsldV0uCgBXYXNtVEE6IEludm9rZUNvbW1hbmRFbnRyeVBvaW50IC0tLS0tU2Vzc2lvbjogJXUgCgBIZWxsbzogbXkgc2Vzc2lvbiBjb250ZXh0OiAlcwoAV0FTTTpJbnZva2VDb21tYW5kIGJhZCBwYXJhbWV0ZXJzOjB4JXguCgBXQVNNOkludm9rZUNvbW1hbmQgU3VjY2Vzc2VkLCBDbWRJZCA9ICVkLgoAV0FTTTpVbmtub3duIENNRCBJRDogJWQKAFdBU00gVEE6LS0tLSBUQV9DbG9zZVNlc3Npb25FbnRyeVBvaW50IC0tIHNlc3Npb246ICV1IAoAY3RkX1YxXzIwMjAtMDktMTQAV0FTTSBUQTotLS0tIFRBX09wZW5TZXNzaW9uRW50cnlQb2ludCAtLS0tLS0tLSAAd2FzbTogbWFsbG9jIGZhaWxlZC4AQmFkIGV4cGVjdGVkIHBhcmFtZXRlciB0eXBlcwA";
//              String aa = "AGFzbQEAAAABIwZgA39_fwF_YAF_AX9gAn9_AX9gAX8AYAABf2AEf39_fwF_AlkHA2VudgZtZW1zZXQAAANlbnYEcHV0cwABA2VudgZtYWxsb2MAAQNlbnYHc3RybmNweQAAA2VudgZwcmludGYAAgNlbnYGc3RybGVuAAEDZW52BGZyZWUAAwMIBwQEBAQABQMEBQFwAQEBBQMBAAEGEwN_AUHwKwt_AEHkCwt_AEHwKwsHegcGbWVtb3J5AgASV0FfT25Jbml0VEFTZXNzaW9uAAcSV0FfT25PcGVuVEFTZXNzaW9uAAgSV0FfT25JbnZva2VDb21tYW5kAAkTV0FfT25DbG9zZVRBU2Vzc2lvbgAKCl9fZGF0YV9lbmQDAQtfX2hlYXBfYmFzZQMCCpMFBxMAQYyLgIAAQQBB2AAQgICAgAALLAEBf0EAQQAoApCLgIAAQZSLgIAAQYyLgIAAEIuAgIAAIgA2AriLgIAAIAALOAEBf0EAQQAoAoyLgIAAQQAoArSLgIAAQQAoApCLgIAAQZSLgIAAEIyAgIAAIgA2AriLgIAAIAALEwBBACgCjIuAgAAQjYCAgABBAAuEAQECfyOAgICAAEEQayIDJICAgIAAQamKgIAAEIGAgIAAGiACQeQAEIKAgIAAIgQ2AgACQAJAIARFDQAgBEGAiICAAEHkABCDgICAABogAyACKAIANgIAQYuIgIAAIAMQhICAgAAaDAELQdmKgIAAEIGAgIAAGgsgA0EQaiSAgICAAEEAC7UCAQF_I4CAgIAAQdAAayIEJICAgIAAIAQgADYCQEGoiICAACAEQcAAahCEgICAABoCQCAARQ0AIAQgADYCMEHbiICAACAEQTBqEISAgIAAGgsCQAJAIAFBAUcNAAJAIAJBgMABRg0AQe6KgIAAEIGAgIAAGkGGgHwhAAwCCwJAAkAgAygCGCIARQ0AIANBHGooAgAiAUH_AUsNAQsgBEGGgHw2AhBB-oiAgAAgBEEQahCEgICAABogA0EcaigCACEBIAMoAhghAAsgA0EcaiAAQZ-KgIAAIAFBf2oQg4CAgAAQhYCAgAA2AgAgBEEBNgIAQaOJgIAAIAQQhICAgAAaQQAhAAwBCyAEIAE2AiBBzomAgAAgBEEgahCEgICAABpBgqB9IQALIARB0ABqJICAgIAAIAALRgEBfyOAgICAAEEQayIBJICAgIAAIAEgADYCAEHniYCAACABEISAgIAAGgJAIABFDQAgABCGgICAAAsgAUEQaiSAgICAAAsLkwMBAEGACAuLA2hlbGxvIHdhc20Ad2FzbTogY3JlYXRlZCBzZXNzaW9uIFsldV0uCgBXYXNtVEE6IEludm9rZUNvbW1hbmRFbnRyeVBvaW50IC0tLS0tU2Vzc2lvbjogJXUgCgBIZWxsbzogbXkgc2Vzc2lvbiBjb250ZXh0OiAlcwoAV0FTTTpJbnZva2VDb21tYW5kIGJhZCBwYXJhbWV0ZXJzOjB4JXguCgBXQVNNOkludm9rZUNvbW1hbmQgU3VjY2Vzc2VkLCBDbWRJZCA9ICVkLgoAV0FTTTpVbmtub3duIENNRCBJRDogJWQKAFdBU00gVEE6LS0tLSBUQV9DbG9zZVNlc3Npb25FbnRyeVBvaW50IC0tIHNlc3Npb246ICV1IAoAaGVsbG8gY3RkAFdBU00gVEE6LS0tLSBUQV9PcGVuU2Vzc2lvbkVudHJ5UG9pbnQgLS0tLS0tLS0gAHdhc206IG1hbGxvYyBmYWlsZWQuAEJhZCBleHBlY3RlZCBwYXJhbWV0ZXIgdHlwZXMA-oiAgAAgBEEQahCEgICAABogA0EcaigCACEBIAMoAhghAAsgA0EcaiAAQZ-KgIAAIAFBf2oQg4CAgAAQhYCAgAA2AgAgBEEBNgIAQaOJgIAAIAQQhICAgAAaQQAhAAwBCyAEIAE2AiBBzomAgAAgBEEgahCEgICAABpBgqB9IQALIARB0ABqJICAgIAAIAALRgEBfyOAgICAAEEQayIBJICAgIAAIAEgADYCAEHniYCAACABEISAgIAAGgJAIABFDQAgABCGgICAAAsgAUEQaiSAgICAAAsLkwMBAEGACAuLA2hlbGxvIHdhc20Ad2FzbTogY3JlYXRlZCBzZXNzaW9uIFsldV0uCgBXYXNtVEE6IEludm9rZUNvbW1hbmRFbnRyeVBvaW50IC0tLS0tU2Vzc2lvbjogJXUgCgBIZWxsbzogbXkgc2Vzc2lvbiBjb250ZXh0OiAlcwoAV0FTTTpJbnZva2VDb21tYW5kIGJhZCBwYXJhbWV0ZXJzOjB4JXguCgBXQVNNOkludm9rZUNvbW1hbmQgU3VjY2Vzc2VkLCBDbWRJZCA9ICVkLgoAV0FTTTpVbmtub3duIENNRCBJRDogJWQKAFdBU00gVEE6LS0tLSBUQV9DbG9zZVNlc3Npb25FbnRyeVBvaW50IC0tIHNlc3Npb246ICV1IAoAaGVsbG8gY3RkAFdBU00gVEE6LS0tLSBUQV9PcGVuU2Vzc2lvbkVudHJ5UG9pbnQgLS0tLS0tLS0gAHdhc206IG1hbGxvYyBmYWlsZWQuAEJhZCBleHBlY3RlZCBwYXJhbWV0ZXIgdHlwZXMA";
                byte[] decodeWasm = Base64.decode(aa, Base64.URL_SAFE);
//                String algorithm = new String(decode);
                Log.d("wasm字节码", result);
                Log.d("MD5字节码", MD5.md5(new String(decodeWasm)));

//                InputStream inputStream = null;
//                byte[] bytes = null;
//                try {
//                    inputStream = x.app().getAssets().open("hello_world");
//                    bytes = toByteArray(inputStream);
//                    Log.d("MD5字节码",MD5.md5(new String(bytes))) ;
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }


//                String taResult = teeManager.getTaResult(decodeWasm);
                String taResult = teeManager.getTaResult(decodeWasm);
                tv1.setText(taResult);


            }
        });


    }


    public static void getGetHttp1(final TeeManager teeManager, final TextView tv1) {
        HashMap<String, String> requestMap = new HashMap();
        HttpUtils.agentGetRequest(requestMap, new HttpUtils.HandleResult() {

            @Override
            public void onSuccess(String result) {
                String aa = "AGFzbQEAAAABIwZgA39_fwF_YAF_AX9gAn9_AX9gAX8AYAABf2AEf39_fwF_AlkHA2VudgZtZW1zZXQAAANlbnYEcHV0cwABA2VudgZtYWxsb2MAAQNlbnYHc3RybmNweQAAA2VudgZwcmludGYAAgNlbnYGc3RybGVuAAEDZW52BGZyZWUAAwMIBwQEBAQABQMEBQFwAQEBBQMBAAEGEwN_AUHwKwt_AEHkCwt_AEHwKwsHegcGbWVtb3J5AgASV0FfT25Jbml0VEFTZXNzaW9uAAcSV0FfT25PcGVuVEFTZXNzaW9uAAgSV0FfT25JbnZva2VDb21tYW5kAAkTV0FfT25DbG9zZVRBU2Vzc2lvbgAKCl9fZGF0YV9lbmQDAQtfX2hlYXBfYmFzZQMCCpMFBxMAQYyLgIAAQQBB2AAQgICAgAALLAEBf0EAQQAoApCLgIAAQZSLgIAAQYyLgIAAEIuAgIAAIgA2AriLgIAAIAALOAEBf0EAQQAoAoyLgIAAQQAoArSLgIAAQQAoApCLgIAAQZSLgIAAEIyAgIAAIgA2AriLgIAAIAALEwBBACgCjIuAgAAQjYCAgABBAAuEAQECfyOAgICAAEEQayIDJICAgIAAQamKgIAAEIGAgIAAGiACQeQAEIKAgIAAIgQ2AgACQAJAIARFDQAgBEGAiICAAEHkABCDgICAABogAyACKAIANgIAQYuIgIAAIAMQhICAgAAaDAELQdmKgIAAEIGAgIAAGgsgA0EQaiSAgICAAEEAC7UCAQF_I4CAgIAAQdAAayIEJICAgIAAIAQgADYCQEGoiICAACAEQcAAahCEgICAABoCQCAARQ0AIAQgADYCMEHbiICAACAEQTBqEISAgIAAGgsCQAJAIAFBAUcNAAJAIAJBgMABRg0AQe6KgIAAEIGAgIAAGkGGgHwhAAwCCwJAAkAgAygCGCIARQ0AIANBHGooAgAiAUH_AUsNAQsgBEGGgHw2AhBB-oiAgAAgBEEQahCEgICAABogA0EcaigCACEBIAMoAhghAAsgA0EcaiAAQZ-KgIAAIAFBf2oQg4CAgAAQhYCAgAA2AgAgBEEBNgIAQaOJgIAAIAQQhICAgAAaQQAhAAwBCyAEIAE2AiBBzomAgAAgBEEgahCEgICAABpBgqB9IQALIARB0ABqJICAgIAAIAALRgEBfyOAgICAAEEQayIBJICAgIAAIAEgADYCAEHniYCAACABEISAgIAAGgJAIABFDQAgABCGgICAAAsgAUEQaiSAgICAAAsLkwMBAEGACAuLA2hlbGxvIHdhc20Ad2FzbTogY3JlYXRlZCBzZXNzaW9uIFsldV0uCgBXYXNtVEE6IEludm9rZUNvbW1hbmRFbnRyeVBvaW50IC0tLS0tU2Vzc2lvbjogJXUgCgBIZWxsbzogbXkgc2Vzc2lvbiBjb250ZXh0OiAlcwoAV0FTTTpJbnZva2VDb21tYW5kIGJhZCBwYXJhbWV0ZXJzOjB4JXguCgBXQVNNOkludm9rZUNvbW1hbmQgU3VjY2Vzc2VkLCBDbWRJZCA9ICVkLgoAV0FTTTpVbmtub3duIENNRCBJRDogJWQKAFdBU00gVEE6LS0tLSBUQV9DbG9zZVNlc3Npb25FbnRyeVBvaW50IC0tIHNlc3Npb246ICV1IAoAaGVsbG8gY3RkAFdBU00gVEE6LS0tLSBUQV9PcGVuU2Vzc2lvbkVudHJ5UG9pbnQgLS0tLS0tLS0gAHdhc206IG1hbGxvYyBmYWlsZWQuAEJhZCBleHBlY3RlZCBwYXJhbWV0ZXIgdHlwZXMA";
//                String aa = "AGFzbQEAAAABIwZgA39_fwF_YAF_AX9gAn9_AX9gAX8AYAABf2AEf39_fwF_AlkHA2VudgZtZW1zZXQAAANlbnYEcHV0cwABA2VudgZtYWxsb2MAAQNlbnYHc3RybmNweQAAA2VudgZwcmludGYAAgNlbnYGc3RybGVuAAEDZW52BGZyZWUAAwMIBwQEBAQABQMEBQFwAQEBBQMBAAEGEwN_AUHwKwt_AEHkCwt_AEHwKwsHegcGbWVtb3J5AgASV0FfT25Jbml0VEFTZXNzaW9uAAcSV0FfT25PcGVuVEFTZXNzaW9uAAgSV0FfT25JbnZva2VDb21tYW5kAAkTV0FfT25DbG9zZVRBU2Vzc2lvbgAKCl9fZGF0YV9lbmQDAQtfX2hlYXBfYmFzZQMCCpMFBxMAQYyLgIAAQQBB2AAQgICAgAALLAEBf0EAQQAoApCLgIAAQZSLgIAAQYyLgIAAEIuAgIAAIgA2AriLgIAAIAALOAEBf0EAQQAoAoyLgIAAQQAoArSLgIAAQQAoApCLgIAAQZSLgIAAEIyAgIAAIgA2AriLgIAAIAALEwBBACgCjIuAgAAQjYCAgABBAAuEAQECfyOAgICAAEEQayIDJICAgIAAQamKgIAAEIGAgIAAGiACQeQAEIKAgIAAIgQ2AgACQAJAIARFDQAgBEGAiICAAEHkABCDgICAABogAyACKAIANgIAQYuIgIAAIAMQhICAgAAaDAELQdmKgIAAEIGAgIAAGgsgA0EQaiSAgICAAEEAC7UCAQF_I4CAgIAAQdAAayIEJICAgIAAIAQgADYCQEGoiICAACAEQcAAahCEgICAABoCQCAARQ0AIAQgADYCMEHbiICAACAEQTBqEISAgIAAGgsCQAJAIAFBAUcNAAJAIAJBgMABRg0AQe6KgIAAEIGAgIAAGkGGgHwhAAwCCwJAAkAgAygCGCIARQ0AIANBHGooAgAiAUH_AUsNAQsgBEGGgHw2AhBB-oiAgAAgBEEQahCEgICAABogA0EcaigCACEBIAMoAhghAAsgA0EcaiAAQZ-KgIAAIAFBf2oQg4CAgAAQhYCAgAA2AgAgBEEBNgIAQaOJgIAAIAQQhICAgAAaQQAhAAwBCyAEIAE2AiBBzomAgAAgBEEgahCEgICAABpBgqB9IQALIARB0ABqJICAgIAAIAALRgEBfyOAgICAAEEQayIBJICAgIAAIAEgADYCAEHniYCAACABEISAgIAAGgJAIABFDQAgABCGgICAAAsgAUEQaiSAgICAAAsLkwMBAEGACAuLA2hlbGxvIHdhc20Ad2FzbTogY3JlYXRlZCBzZXNzaW9uIFsldV0uCgBXYXNtVEE6IEludm9rZUNvbW1hbmRFbnRyeVBvaW50IC0tLS0tU2Vzc2lvbjogJXUgCgBIZWxsbzogbXkgc2Vzc2lvbiBjb250ZXh0OiAlcwoAV0FTTTpJbnZva2VDb21tYW5kIGJhZCBwYXJhbWV0ZXJzOjB4JXguCgBXQVNNOkludm9rZUNvbW1hbmQgU3VjY2Vzc2VkLCBDbWRJZCA9ICVkLgoAV0FTTTpVbmtub3duIENNRCBJRDogJWQKAFdBU00gVEE6LS0tLSBUQV9DbG9zZVNlc3Npb25FbnRyeVBvaW50IC0tIHNlc3Npb246ICV1IAoAaGVsbG8gY3RkAFdBU00gVEE6LS0tLSBUQV9PcGVuU2Vzc2lvbkVudHJ5UG9pbnQgLS0tLS0tLS0gAHdhc206IG1hbGxvYyBmYWlsZWQuAEJhZCBleHBlY3RlZCBwYXJhbWV0ZXIgdHlwZXMA-oiAgAAgBEEQahCEgICAABogA0EcaigCACEBIAMoAhghAAsgA0EcaiAAQZ-KgIAAIAFBf2oQg4CAgAAQhYCAgAA2AgAgBEEBNgIAQaOJgIAAIAQQhICAgAAaQQAhAAwBCyAEIAE2AiBBzomAgAAgBEEgahCEgICAABpBgqB9IQALIARB0ABqJICAgIAAIAALRgEBfyOAgICAAEEQayIBJICAgIAAIAEgADYCAEHniYCAACABEISAgIAAGgJAIABFDQAgABCGgICAAAsgAUEQaiSAgICAAAsLkwMBAEGACAuLA2hlbGxvIHdhc20Ad2FzbTogY3JlYXRlZCBzZXNzaW9uIFsldV0uCgBXYXNtVEE6IEludm9rZUNvbW1hbmRFbnRyeVBvaW50IC0tLS0tU2Vzc2lvbjogJXUgCgBIZWxsbzogbXkgc2Vzc2lvbiBjb250ZXh0OiAlcwoAV0FTTTpJbnZva2VDb21tYW5kIGJhZCBwYXJhbWV0ZXJzOjB4JXguCgBXQVNNOkludm9rZUNvbW1hbmQgU3VjY2Vzc2VkLCBDbWRJZCA9ICVkLgoAV0FTTTpVbmtub3duIENNRCBJRDogJWQKAFdBU00gVEE6LS0tLSBUQV9DbG9zZVNlc3Npb25FbnRyeVBvaW50IC0tIHNlc3Npb246ICV1IAoAaGVsbG8gY3RkAFdBU00gVEE6LS0tLSBUQV9PcGVuU2Vzc2lvbkVudHJ5UG9pbnQgLS0tLS0tLS0gAHdhc206IG1hbGxvYyBmYWlsZWQuAEJhZCBleHBlY3RlZCBwYXJhbWV0ZXIgdHlwZXMA";
                byte[] decodeWasm = Base64.decode(aa, Base64.URL_SAFE);
//                String algorithm = new String(decode);
                Log.d("wasm字节码", result);
                Log.d("MD5字节码", MD5.md5(new String(decodeWasm)));

//                InputStream inputStream = null;
//                byte[] bytes = null;
//                try {
//                    inputStream = x.app().getAssets().open("hello_world");
//                    bytes = toByteArray(inputStream);
//                    Log.d("MD5字节码",MD5.md5(new String(bytes))) ;
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }


//                String taResult = teeManager.getTaResult(decodeWasm);
                String taResult = teeManager.getTaResult(decodeWasm);
                tv1.setText(taResult);


            }
        });


    }


    @Override
    public void getTaListBySp(final OtrpRequestCallback otrpRequestCallback) {
        HashMap<String, String> requestMap = new HashMap();
        requestMap.put(Constant.REQUEST_URL, "/tam-ta/list-by-sp");
        requestMap.put("spCode", "CIB");
        HttpUtils.agentPostRequest(requestMap, new HttpUtils.HandleResult() {
            @Override
            public void onSuccess(String result) {
                List<WasmTaBean> wasmTaBeans = GsonUtil.jsonToList(result, WasmTaBean.class);
                try {
                    TeeManager.wasm_db.dropTable(WasmTaBean.class);
                    TeeManager.wasm_db.saveOrUpdate(wasmTaBeans);
                    List<WasmTaBean> dbWasmBeans = TeeManager.wasm_db.selector(WasmTaBean.class).findAll();
                    otrpRequestCallback.otrpRequestSuccess(dbWasmBeans);
                } catch (DbException e) {
                    e.printStackTrace();
                }


            }
        });


    }

    @Override
    public  void getTeeDeviceStateRequest() {
        HashMap<String, String> requestMap = new HashMap();
        requestMap.put(Constant.REQUEST_URL, "/tam/get-device-tee-state/request");
        HttpUtils.agentPostRequest(requestMap, new HttpUtils.HandleResult() {
            @Override
            public void onSuccess(String result) {

                getTeeDeviceStateResponse(result);


                String createSD = "{\n" +
                        "  \"CreateSDRequest\": {\n" +
                        "  \"payload\":\"ewoJIkNyZWF0ZVNEVEJTUmVxdWVzdCI6IHsKCQkidmVyIjogIjEuMCIsCgkJInJpZCI6ICJyZXEtMDEiLAoJCSJ0aWQiOiAidHJhbi0wMSIsCgkJInRlZSI6ICJTZWN1cmlURUUiLAoJCSJuZXh0ZHNpIjogImZhbHNlIiwKCQkiZHNpaGFzaCI6ICJJdS1jMC1mR3JwTW16YmJ0aVdJMVU4dTd3TUpFN0lLOHdrSnBzVnVmMmpzIiwKCQkiY29udGVudCI6IHsKCQkJInNwaWQiOiAiYmFuay5jb20iLAoJCQkic2RuYW1lIjogInNkLmJhbmsuY29tIiwKCQkJInNwY2VydCI6ICJNSUlERmpDQ0FuLSIsCgkJCSJ0YW1pZCI6ICJUQU1feC5hY21lLmNvbSIsCgkJCSJkaWQiOiAiekFIa2IwLVNRaDlVX09UOG1SNWRCLXR5Z2NxcFVKOV94MDdwSWl3OFdvTSIKCQl9Cgl9Cn0=\",\n" +
                        "  \"protected\":\"e-KAnGFsZ-KAnTrigJxSUzI1NuKAnX0\",    \n" +
                        "  \"header\": {\n" +
                        "    \"kid\":\"e9bc097a-ce51-4036-9562-d2ade882db0d\",\n" +
                        "      \"signer\":\"FFF\"\n" +
                        "        },\n" +
                        "     \"signature\":\"BBB\"\n" +
                        "  }\n" +
                        "}";

                String deleteSD = "{\n" +
                        "\t\"DeleteSDRequest\": {\n" +
                        "\t\t\"payload\": \"ewoJIkRlbGV0ZVNEVEJTUmVxdWVzdCI6IHsKCQkidmVyIjogIjEuMCIsCgkJInJpZCI6ICJ7NzEyNTUxRjUtREZCMy00M2YwLTlBNjMtNjYzNDQwQjkxRDQ5fSIsCgkJInRpZCI6ICJ7NEY0NTRBN0YtMDAyRC00MTU3LTg4NEUtQjBERDFBMDZBOEFFfSIsCgkJInRlZSI6ICJQcmltYXJ5IFRFRSIsCgkJIm5leHRkc2kiOiAiZmFsc2UiLAoJCSJkc2loYXNoIjogIkFBRUNBd1FGQmdjSUNRb0xEQTBPRHdBQkFnTUVCUVlIQ0FrS0N3d05EZzg9IiwKCQkiY29udGVudCI6IHsKCQkJInByb3RlY3RlZCI6ICJleUpsYm1NaU9pSkJNVEk0UTBKRExVaFRNalUySW4wIiwKCQkJInJlY2lwaWVudHMiOiBbewoJCQkJImhlYWRlciI6IHsKCQkJCQkiYWxnIjogIlJTQTFfNSIKCQkJCX0sCgkJCQkiZW5jcnlwdGVkX2tleSI6ICJkc2Fkc2EiCgkJCX1dLAoJCQkiaXYiOiAicldPNURWbVFYOW9nZWxNTEJJb2dJQSIsCgkJCSJjaXBoZXJ0ZXh0IjogImRzYWRzYSIsCgkJCSJ0YWciOiAiYzJGdGNHeGxJR0YxZEdobGJuUnBZMkYwYVc5dUlIUmhadyIKCQl9Cgl9Cn0=\",\n" +
                        "\t\t\"protected\": \"eyJhbGciOiJSUzI1NiJ9\",\n" +
                        "\t\t\"header\": {\n" +
                        "\t\t\t\"x5c\": [\"ZXhhbXBsZSBBU04xIHNpZ25lciBjZXJ0aWZpY2F0ZQ==\",\n" +
                        "\t\t\t\t\"ZXhhbXBsZSBBU04xIENBIGNlcnRpZmljYXRl\"\n" +
                        "\t\t\t]\n" +
                        "\t\t},\n" +
                        "\t\t\"signature\": \"c2FtcGxlIHNpZ25hdHVyZQ\"\n" +
                        "\t}\n" +
                        "}";




            }
//                Toast.makeText(x.app(), result, Toast.LENGTH_LONG).show();
//                ACBean acBean = GsonUtil.GsonToBean(result, ACBean.class);
//                ACBean.GetDeviceStateRequestBean getDeviceStateRequest = acBean.getGetDeviceStateRequest();
////                Log.d("XXXXXXXX",getDeviceStateRequest.getPayload());
//
//                List<String> x5c = getDeviceStateRequest.getHeader().getX5c();
//                String x5c1 = x5c.get(0);
//                try {
//                    byte[] certificateBytes = Base64.decode(x5c1, Base64.URL_SAFE);
//                    Security.removeProvider(BouncyCastleProvider.PROVIDER_NAME);
//                    if (Security.getProvider(BouncyCastleProvider.PROVIDER_NAME) == null) {
//                        Security.addProvider(new BouncyCastleProvider());
//                    }
//                    CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509", "BC");
//                    X509Certificate certificate = (X509Certificate) (certificateFactory.generateCertificate(
//                            new ByteArrayInputStream(certificateBytes)
//                    ));
//
//                    PublicKey publicKey = certificate.getPublicKey();
//
//                    String protectedX = getDeviceStateRequest.getProtectedX();
//                    String payload = getDeviceStateRequest.getPayload();
//                    String signature = getDeviceStateRequest.getSignature();
//
//                    byte[] decode = Base64.decode(protectedX, Base64.URL_SAFE);
//                    String algorithm = new String(decode);
//
//                    if (algorithm.contains("ES256")) {
//
//                        boolean b = CertificateUtils.es256ValidationSign(publicKey, protectedX + "." + payload,
//                                Base64.decode(signature, Base64.URL_SAFE));
//                        System.out.println(b);
//
////                        System.out.println();
//
//                        String payLoad = new String(Base64.decode(payload, Base64.URL_SAFE));
//                        RequestTeeStatePayload requestTeeStatePayload = GsonUtil.GsonToBean(
//                                payLoad, RequestTeeStatePayload.class);
//
////                        IBerTlvLogger tag = new IBerTlvLogger() {
////
////                            @Override
////                            public boolean isDebugEnabled() {
////                                return false;
////                            }
////
////                            @Override
////                            public void debug(String aFormat, Object... args) {
////
////
////                            }
////                        };
////
////                        BerTlvParser parser = new BerTlvParser(tag);
////                        BerTlvs tlvs = parser.parse(bytes, 0, bytes.length);
////
////                        BerTlvLogger.log("    ", tlvs, tag);
//
//                        byte[] bytes1 = new BerTlvBuilder()
//                                .addHex(new BerTag(0x50), "56495341")
//                                .addHex(new BerTag(0x57), "1000023100000033D44122011003400000481F")
//                                .buildArray();
//
//                        Log.d("16进制", HexUtil.toHexString(bytes1));
//
//                        byte[] bytes2 = new BerTlvBuilder()
//                                .addHex(new BerTag(0x50), HexUtil.toHexString(bytes1))
//                                .buildArray();
//                        Log.d("16进制", HexUtil.toHexString(bytes2));
//
//
//                    } else if (algorithm.contains("RS256")) {
//
//                    }
//
//
//                } catch (CertificateException | NoSuchProviderException e) {
//                    e.printStackTrace();
//                }
//
//            }
        });
    }

    @Override
    public String getTeeDeviceStateResponse(String deviceStateRequestResult) {
        final TeeManager teeManager = TeeManager.getInstance();
        String deviceStateResponse = teeManager.getTeeResponse(deviceStateRequestResult);
//        getTeeSDList(deviceStateResponse);
        return deviceStateResponse;

    }


    @Override
    public void getTeeSDList(String deviceStateRequestResult, final OtrpRequestCallback otrpRequestCallback) {
        HashMap<String, String> requestMap = new HashMap();
        requestMap.put(Constant.REQUEST_URL, "/tam/get-device-tee-state/response");
        requestMap.put("body",deviceStateRequestResult);
        HttpUtils.agentPostRequest(requestMap, new HttpUtils.HandleResult() {
            @Override
            public void onSuccess(String result) {

                TeeDeviceResponseBean teeDeviceResponseBean = GsonUtil.GsonToBean(
                        result, TeeDeviceResponseBean.class);
                TeeDeviceResponseBean.GetDeviceTEEStateResponseBean getDeviceTEEStateResponse =
                        teeDeviceResponseBean.getGetDeviceTEEStateResponse();
                String payload = getDeviceTEEStateResponse.getPayload();
                String sdList  = new String(Base64.decode(payload, Base64.URL_SAFE));

                otrpRequestCallback.getSdListSuccess(sdList);
//                Toast.makeText(x.app(),sdList,Toast.LENGTH_LONG).show();


            }
        });

    }





    @Override
    public void getCreateSDRequest(String deviceStateResponse) {
        HashMap<String, String> requestMap = new HashMap();
        requestMap.put(Constant.REQUEST_URL, "/tam/get-device-tee-state/response");
        requestMap.put("body",deviceStateResponse);
        HttpUtils.agentPostRequest(requestMap, new HttpUtils.HandleResult() {
            @Override
            public void onSuccess(String result) {

//                Toast.makeText(x.app(),result,Toast.LENGTH_LONG).show();


            }
        });








        final TeeManager teeManager = TeeManager.getInstance();
        String taResponse = teeManager.getTeeResponse(deviceStateResponse);
//                Toast.makeText(x.app(), taResponse, Toast.LENGTH_LONG).show();
//        HashMap<String, String> requestMap = new HashMap();
//        requestMap.put(Constant.REQUEST_URL, "/tam/get-device-tee-state/response");
//        requestMap.put("body",taResponse);
//        HttpUtils.agentPostRequest(requestMap, new HttpUtils.HandleResult() {
//            @Override
//            public void onSuccess(String result) {
//
//                Toast.makeText(x.app(),result,Toast.LENGTH_LONG).show();
//
//            }
//        });
    }


    public interface OtrpRequestCallback{
        void otrpRequestSuccess(List<WasmTaBean> wasmTaBeans);
        void getSdListSuccess(String sdList);
    }
}
