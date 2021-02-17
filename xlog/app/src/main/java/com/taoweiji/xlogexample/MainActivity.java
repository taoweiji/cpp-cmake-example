package com.taoweiji.xlogexample;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.taoweiji.nativelib.NativeLib;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        NativeLib.initXLog(this);
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(new NativeLib().stringFromJNI());
    }
}