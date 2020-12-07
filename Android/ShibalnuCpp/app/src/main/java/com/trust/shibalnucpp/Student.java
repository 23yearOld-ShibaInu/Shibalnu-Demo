package com.trust.shibalnucpp;

import android.util.Log;

public class Student {
    private final static String TAG = "LiHao";

    private String name;
    private int age;

    public Student(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public static String getTAG() {
        return TAG;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        Log.d(TAG,"java setName L"+name);
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        Log.d(TAG,"java setAge L"+age);
        this.age = age;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }

    public static void startMethod(){
        Log.d(TAG,"startMethod");
    }
}
