package com.aven.nativesvg;

import android.graphics.Bitmap;
import android.util.Log;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 **/
public class NativeSvgUtils {

    static {
        System.loadLibrary("NativeSvg");
    }
    public static Map<String, NativeSvgListener> sObserver;
    public static native void getNativeBitmap(String source);

    public static void onDataCallBack(char cmd, float[] params){
        if (sObserver != null) {
            for(Map.Entry<String, NativeSvgListener> entry : sObserver.entrySet()) {
                entry.getValue().onDataCallBack(cmd, params);
            }
        }
    }

    public static void onPathFinish(String color){
        if (sObserver != null) {
            for(Map.Entry<String, NativeSvgListener> entry : sObserver.entrySet()) {
                entry.getValue().onPathFinish(color);
            }
        }
    }

    public static void onDataFinish() {
        if (sObserver != null) {
            for(Map.Entry<String, NativeSvgListener> entry : sObserver.entrySet()) {
                entry.getValue().onDataFinish();
            }
        }
    }

    public interface NativeSvgListener{
        void onDataCallBack(char cmd, float[] params);
        void onPathFinish(String color);
        void onDataFinish();
    }

    public static void registerNativeSvgListener(String className, NativeSvgListener listener){
        if (sObserver == null) {
            sObserver = new HashMap<String, NativeSvgListener>();
        }
        sObserver.put(className, listener);
    }

    public static void unRegisterNativeSvgListener(String className) {
        if (sObserver == null) {
            return;
        }
        sObserver.remove(className);
    }
}
