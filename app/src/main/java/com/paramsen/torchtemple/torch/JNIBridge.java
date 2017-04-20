package com.paramsen.torchtemple.torch;

import android.content.Context;
import android.content.res.AssetManager;
import android.os.Build;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;

/**
 * Interface for our native source. Most of the methods should not be called from main thread, but
 * I'm keeping the api simple.
 *
 * @author Pär Amsen 04/2017
 */
public class JNIBridge {
    static {
        System.loadLibrary("native");
    }

    public boolean setup(Context c) {
        if (isTorchSupported()) {
            nSetup(c.getAssets(), c.getApplicationInfo().nativeLibraryDir, exportTorchNet(c));
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

    /**
     * I never got the torch net loading from assets/apk working (apkascii, apkbinary), so this is
     * my workaround. The net is exported to the private files directory. The returned path is
     * dynamically used when loading the torch model in lua.
     *
     * Hint; This should not be performed on the main thread, just keeping the api simple.
     */
    private String exportTorchNet(Context c) {
        File output = new File(c.getFilesDir(), "mockAsciiNet.net");

        if (!output.exists()) {
            try {
                BufferedInputStream source = new BufferedInputStream(c.getAssets().open("mockAsciiNet.net"));
                BufferedOutputStream sink = new BufferedOutputStream(new FileOutputStream(output));

                byte[] buf = new byte[512];
                int read = 0;
                while (read != -1) {
                    read = source.read(buf, 0, 512);

                    if (read != -1)
                        sink.write(buf, 0, read);
                }

                sink.flush();
                sink.close();
                source.close();
            } catch (Exception e) {
                throw new RuntimeException("Failed to export .net", e);
            }
        }

        return output.getAbsolutePath();
    }

    private native void nSetup(AssetManager assetManager, String nativeSourcePath, String torchNetPath);

    private native float nCall(float[] data);

    private native void nDispose();
}
