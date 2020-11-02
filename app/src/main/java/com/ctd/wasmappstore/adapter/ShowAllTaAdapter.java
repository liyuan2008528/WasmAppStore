package com.ctd.wasmappstore.adapter;

import android.content.Context;
import android.graphics.drawable.Icon;
import android.util.Base64;
import android.widget.ImageView;

import androidx.annotation.Nullable;

import com.bumptech.glide.Glide;
import com.chad.library.adapter.base.BaseQuickAdapter;
import com.chad.library.adapter.base.viewholder.BaseViewHolder;
import com.ctd.teeagent.model.WasmTaBean;
import com.ctd.wasmappstore.R;

import java.util.List;

public class ShowAllTaAdapter extends BaseQuickAdapter<WasmTaBean, BaseViewHolder> {



    private Context mContext;


    public ShowAllTaAdapter(Context context, int layoutResId, @Nullable List<WasmTaBean> data) {
        super(layoutResId, data);
        mContext = context;


    }

    @Override
    protected void convert(BaseViewHolder helper, WasmTaBean item) {
        byte[] desc = Base64.decode(item.getSpecDesc(), Base64.NO_WRAP);
        byte[] name = Base64.decode(item.getName(), Base64.NO_WRAP);

        helper.setText(R.id.tv_ta_name,new String(name));
        helper.setText(R.id.tv_ta_code,item.getTaCode());
        helper.setText(R.id.tv_ta_spec, new String(desc));
        ImageView iv_ta_icon = helper.getView(R.id.iv_ta_icon);

        Glide.with(mContext).load("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1600860674472&di=80552c1128af95993420c69b42f0c6e0&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201603%2F06%2F20160306204517_i4Se8.jpeg").into(iv_ta_icon);

       


    }
}