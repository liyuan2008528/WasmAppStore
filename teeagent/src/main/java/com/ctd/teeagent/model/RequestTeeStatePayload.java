package com.ctd.teeagent.model;

import java.util.List;

public class RequestTeeStatePayload {


    /**
     * ver : GDP.TEE.1.0.0.0
     * ocspdat : ["待研究ocsp stapling如何提供","待研究ocsp stapling如何提供"]
     * rid : d734515b-a5b9-4c8b-b7fc-827aadcf6e5b
     * supportedsigalgs : ["ES256","ES384","ES512","RS256","RS384","RS512"]
     * tid : 91f30a27-2b81-4863-9172-48e7ba725122
     */

    private String ver;
    private String rid;
    private String tid;
    private List<String> ocspdat;
    private List<String> supportedsigalgs;

    public String getVer() {
        return ver;
    }

    public void setVer(String ver) {
        this.ver = ver;
    }

    public String getRid() {
        return rid;
    }

    public void setRid(String rid) {
        this.rid = rid;
    }

    public String getTid() {
        return tid;
    }

    public void setTid(String tid) {
        this.tid = tid;
    }

    public List<String> getOcspdat() {
        return ocspdat;
    }

    public void setOcspdat(List<String> ocspdat) {
        this.ocspdat = ocspdat;
    }

    public List<String> getSupportedsigalgs() {
        return supportedsigalgs;
    }

    public void setSupportedsigalgs(List<String> supportedsigalgs) {
        this.supportedsigalgs = supportedsigalgs;
    }
}
