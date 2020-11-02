package com.ctd.teeagent.agent;

import com.ctd.teeagent.model.WasmTaBean;

import java.util.List;

public interface OtrpInterface {

    void getTaListBySp(OtrpAgent.OtrpRequestCallback otrpRequestCallback);

    void getDeviceState();
}
