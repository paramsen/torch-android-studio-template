package com.paramsen.torchtemple.torch;

import android.os.Build;

/**
 * @author Pär Amsen 04/2017
 */
public class JNIBridge {
    public boolean setup() {
        if(isTorchSupported()) {
            nSetup();
            return true;
        }

        return false;
    }

    public float call(float[] data) {
        return nCall(data);
    }

    public void dispose() {
        nDispose();
    }

    /**
     * Torch is only supported on ARM.
     */
    public boolean isTorchSupported() {
        String[] abis = Build.VERSION.SDK_INT > Build.VERSION_CODES.LOLLIPOP ? Build.SUPPORTED_ABIS : new String[]{Build.CPU_ABI};
        boolean armSupport = false;

        for (String abi : abis) {
            if (abi.matches("armeabi-v7a|arm64-v8a")) {
                armSupport = true;
                break;
            }
        }
        return armSupport;
    }

    private native void nSetup();
    private native float nCall(float[] data);
    private native void nDispose();
}
