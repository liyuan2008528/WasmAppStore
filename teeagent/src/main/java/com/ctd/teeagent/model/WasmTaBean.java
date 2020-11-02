package com.ctd.teeagent.model;

import org.xutils.db.annotation.Column;
import org.xutils.db.annotation.Table;


@Table(name = "wasmTa")
public class WasmTaBean {
    /**
     * imageVersion : 2
     * specDesc : MjM0NTY=
     * spId : SP-0KES7EL29-0000-2-72
     * taCode : 1
     * imageMac : 7cf255e0ce46f2077ee51ed02bf3a3788dfeddf7
     * name : 1
     * iconUrl : http://tam-assets.ctd.com/appIcons/2020/09/18/b66ebe4d-0121-4b30-9acc-f13725fff7be.png
     * config : null
     * taId : TA-0KF7U2BHF-0-6-700
     * status : 0
     */

    private int imageVersion;
    @Column(name = "specDesc")
    private String specDesc;
    private String spId;
    @Column(name = "taCode")
    private String taCode;
    private String imageMac;
    @Column(name = "name")
    private String name;
    @Column(name = "iconUrl")
    private String iconUrl;
    private Object config;
    @Column(name = "id", isId = true)
    private String taId;
    private int status;


    public int getImageVersion() {
        return imageVersion;
    }

    public void setImageVersion(int imageVersion) {
        this.imageVersion = imageVersion;
    }

    public String getSpecDesc() {
        return specDesc;
    }

    public void setSpecDesc(String specDesc) {
        this.specDesc = specDesc;
    }

    public String getSpId() {
        return spId;
    }

    public void setSpId(String spId) {
        this.spId = spId;
    }

    public String getTaCode() {
        return taCode;
    }

    public void setTaCode(String taCode) {
        this.taCode = taCode;
    }

    public String getImageMac() {
        return imageMac;
    }

    public void setImageMac(String imageMac) {
        this.imageMac = imageMac;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getIconUrl() {
        return iconUrl;
    }

    public void setIconUrl(String iconUrl) {
        this.iconUrl = iconUrl;
    }

    public Object getConfig() {
        return config;
    }

    public void setConfig(Object config) {
        this.config = config;
    }

    public String getTaId() {
        return taId;
    }

    public void setTaId(String taId) {
        this.taId = taId;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }


}



