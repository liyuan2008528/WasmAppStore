package com.ctd.wasmappstore.ui;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.chad.library.adapter.base.BaseQuickAdapter;
import com.chad.library.adapter.base.listener.OnItemChildClickListener;
import com.chad.library.adapter.base.viewholder.BaseViewHolder;
import com.ctd.teeagent.agent.OtrpAgent;
import com.ctd.teeagent.model.WasmTaBean;
import com.ctd.wasmappstore.R;
import com.ctd.wasmappstore.adapter.ShowAllTaAdapter;
import com.huawei.ide.TeeManager;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private RecyclerView recyclerView;
    private List<WasmTaBean> list = new ArrayList<>();
    private ShowAllTaAdapter allTaAdapter;
    private OtrpAgent otrpAgent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final TextView tv1 = findViewById(R.id.tv1);
        Button bt1 = findViewById(R.id.bt1);
        Button bt2 = findViewById(R.id.bt2);
        Button bt3 = findViewById(R.id.bt3);
        recyclerView = findViewById(R.id.rv_show_app);
        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(MainActivity.this);
        recyclerView.setLayoutManager(layoutManager);
        allTaAdapter = new ShowAllTaAdapter(this,R.layout.item_ta,list);
        recyclerView.setAdapter(allTaAdapter);
        allTaAdapter.setOnItemChildClickListener(new OnItemChildClickListener() {
            @Override
            public void onItemChildClick(@NonNull BaseQuickAdapter adapter, @NonNull View view, int position) {

            }
        });

         otrpAgent = new OtrpAgent();

        final TeeManager teeManager = TeeManager.getInstance(MainActivity.this);

//        String taResult = teeManager.getTaResult();
//        tv1.setText(taResult);

        tv1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                OtrpAgent.getHttp();
            }
        });

        bt1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//              OtrpAgent.getGetHttp(teeManager,tv1);
//                tv1.setText(taResult);

                otrpAgent.getTaListBySp(new OtrpAgent.OtrpRequestCallback() {
                    @Override
                    public void otrpRequestSuccess(List<WasmTaBean> wasmTaBeans) {
                        list.clear();
                        list.addAll(wasmTaBeans);
                        allTaAdapter.notifyDataSetChanged();
                    }
                });

            }
        });


        bt2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                OtrpAgent.getGetHttp1(teeManager,tv1);
                otrpAgent.getDeviceState();
//                tv1.setText(taResult);

            }
        });

        bt3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                OtrpAgent.getGetHttp(teeManager,tv1);
            }
        });






    }
}
