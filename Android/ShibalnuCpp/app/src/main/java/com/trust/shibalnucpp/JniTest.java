package com.trust.shibalnucpp;

import android.os.Looper;

public class JniTest {

    public native void Test1();

    public native void addTest01(int number,String text,int[] intArray,String[] array);

    public native void putStudent(Student student);

    public native void ndk9();

    public native void testDog();

    public native void testUnBindDog();

    public native void testThread();

    public native void unThread();

    //C++线程操作Android ui
    public void updateUI(){
        if (Looper.getMainLooper() == Looper.myLooper()) {
            showLog("主线程 update ui");
        }else{
            showLog("我是子线程 updata ui");
        }
    }

    private void showLog(String msg){
        Dog.Companion.showLog(msg);
    }
}
