package com.trust.shibalnu;

public class Main {

    public static void main(String[] args) {
	// write your code here
        ShowLog("hello java");

        Integer i1 = 100;
        Integer i2 = 100;

        ShowLog("i1 == i2:"+(i1==i2));

        Integer i3 = 1000;
        Integer i4 = 1000;

        ShowLog("i3 == i4:"+(i3==i4));
    }



    public static void ShowLog(String msg){ System.out.println(msg); }
}
