package com.ctd.teeagent.model;

import com.google.gson.annotations.SerializedName;

import java.util.List;

/**
 * CA鉴权
 */
public class ACBean {


    /**
     * GetDeviceStateRequest : {"payload":"ewoJIkdldERl......IgoJfQp9","protected":"eyJhbGciOiJSUzI1NiJ9","header":{"x5c":["ZXhhbX....pY2F0ZQ==","ZXhhb....mljYXRl"]},"signature":"c2FtcGxlIHNpZ25hdHVyZQ"}
     */

    private GetDeviceStateRequestBean GetDeviceStateRequest;

    public GetDeviceStateRequestBean getGetDeviceStateRequest() {
        return GetDeviceStateRequest;
    }

    public void setGetDeviceStateRequest(GetDeviceStateRequestBean GetDeviceStateRequest) {
        this.GetDeviceStateRequest = GetDeviceStateRequest;
    }

    public static class GetDeviceStateRequestBean {
        /**
         * payload : ewoJIkdldERl......IgoJfQp9
         * protected : eyJhbGciOiJSUzI1NiJ9
         * header : {"x5c":["ZXhhbX....pY2F0ZQ==","ZXhhb....mljYXRl"]}
         * signature : c2FtcGxlIHNpZ25hdHVyZQ
         */

        private String payload;
        @SerializedName("protected")
        private String protectedX;
        private HeaderBean header;
        private String signature;

        public String getPayload() {
            return payload;
        }

        public void setPayload(String payload) {
            this.payload = payload;
        }

        public String getProtectedX() {
            return protectedX;
        }

        public void setProtectedX(String protectedX) {
            this.protectedX = protectedX;
        }

        public HeaderBean getHeader() {
            return header;
        }

        public void setHeader(HeaderBean header) {
            this.header = header;
        }

        public String getSignature() {
            return signature;
        }

        public void setSignature(String signature) {
            this.signature = signature;
        }

        public static class HeaderBean {
            private List<String> x5c;

            public List<String> getX5c() {
                return x5c;
            }

            public void setX5c(List<String> x5c) {
                this.x5c = x5c;
            }
        }
    }
}
