package com.example.sd.ndkpractice2;

// JNI를 위한 클래스
public class Store {
    static{
        System.loadLibrary("native-lib");
       //System.loadLibrary("Store");
    }

    //네이티브 함수들!
    public native int add(int a, int b);
    public native int mul(int a, int b);
    public native String getString(int key);
    public native void setString(int key, String str);
}
