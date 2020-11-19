package com.ctd.teeagent.agent;

import com.ctd.teeagent.model.WasmTaBean;

import java.util.List;

public interface OtrpInterface {

    void getTaListBySp(OtrpAgent.OtrpRequestCallback otrpRequestCallback);

    void getTeeDeviceStateRequest();

    String getTeeDeviceStateResponse(String deviceStateRequest);

    void getTeeSDList(String deviceStateResponse, OtrpAgent.OtrpRequestCallback otrpRequestCallback);

    void getCreateSDRequest(String deviceStateResponse);
}
