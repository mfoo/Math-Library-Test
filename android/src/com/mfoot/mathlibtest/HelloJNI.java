package com.mfoot.mathlibtest;

import android.app.Activity;
import android.os.Bundle;

public class HelloJNI extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        System.out.println(test());
    }

//    public native void test();
    public native String test();

    /* this is used to load the 'hello-jni' library on application
     * startup. The library has already been unpacked into
     * /data/data/com.example.HelloJni/lib/libhello-jni.so at
     * installation time by the package manager.
     */
    static {
//    	System.loadLibrary("stdc++");
    	System.loadLibrary("gnustl_shared");
        System.loadLibrary("MathTest");
    	//System.load("/data/data/com.mfoot.mathlibtest/lib/libmathtest.so");
    }
}
