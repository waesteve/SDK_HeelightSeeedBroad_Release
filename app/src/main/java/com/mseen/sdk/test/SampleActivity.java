package com.mseen.sdk.test;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.mseen.heelightble.audio.R;
import com.mseen.tools.IAudioCommandPlayerListener;
import com.mseen.tools.TonecorPlayerManager;

public class SampleActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.findViewById(R.id.s9bits_Btn).setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                TonecorPlayerManager.getTonecorPlayerManager(SampleActivity.this).playShortAudioCommand(0x1FF);
            }
        });

        this.findViewById(R.id.s36bits_Btn).setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                long tempData = Long.parseLong("7FFFFFFFF",16); //注意，不允许直接使用0x7FFFFFFFF，默认情况下0x？只支持32bit的int.
                TonecorPlayerManager.getTonecorPlayerManager(SampleActivity.this).playLongAudioCommand(tempData);
            }
        });
        TonecorPlayerManager.getTonecorPlayerManager(SampleActivity.this).setPlayerListener(new IAudioCommandPlayerListener() {
            @Override
            public void noticeAudioTooSmall() {
                Toast.makeText(SampleActivity.this, "声音过小", Toast.LENGTH_SHORT).show();
            }
        });

    }
}
