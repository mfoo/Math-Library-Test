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

    }

    @Override
    protected void onResume() {
    	super.onResume();
    	
    	// Attempt to run the garbage collector before allocating memory in
    	// the library so it doesn't interrupt the calculations.
    	System.gc();
    	
        System.out.println(test());
    }

    public native String test();

    static {
    	System.loadLibrary("gnustl_shared");
        System.loadLibrary("MathTest");
    	//System.load("/data/data/com.mfoot.mathlibtest/lib/libmathtest.so");
    }
}
