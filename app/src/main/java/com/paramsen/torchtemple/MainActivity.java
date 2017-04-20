package com.paramsen.torchtemple;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.paramsen.torchtemple.torch.JNIBridge;

import java.util.Arrays;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {
    private float[] data;
    private JNIBridge bridge;

    private TextView torchResult;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        bridge = new JNIBridge();
        boolean deviceSupportsARM = bridge.setup(this);
        data = new float[128];
        Arrays.fill(data, 1f);

        torchResult = (TextView) findViewById(R.id.torchResult);
        TextView torchCompatible = (TextView) findViewById(R.id.torchCompatible);

        torchCompatible.setText(deviceSupportsARM ? "Torch can run on this system (ARM)" : "Torch cannot run on x86");
    }

    @Override
    protected void onDestroy() {
        bridge.dispose();
        super.onDestroy();
    }

    public void onClickRunTorch(View v) {
        float result = bridge.call(data);
        String formatted = String.format(Locale.GERMANY, "%s: Torch returned %.2f", result > Float.MIN_VALUE ? "Success" : "Failure", result);
        torchResult.setText(formatted);
    }
}
