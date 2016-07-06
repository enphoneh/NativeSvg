package com.aven.nativesvg;

import android.graphics.Bitmap;

/**
 **/
public class NativeSvgUtils {

    public static native Bitmap getNativeBitmap(String source);
    static {
        System.loadLibrary("libskia");
    }
    static {
        System.loadLibrary("libbase");
    }
    static {
        System.loadLibrary("NativeSvg");
    }
}
