package com.trust.shibalnuandroid

import org.junit.Test

class KtDebug {
    @Test
    fun debug1(){
        dependencies {
            implementation("this is test1")
            implementation("this is test2")
            implementation("this is test3")
        }.BsLogd()
    }

    @Test
    fun debug2(){
        val oldVersion = "G680_V09_0A201930_test"
        val newVersion = "G680_V09_0A201930"
        when{
            oldVersion == newVersion ->{ "版本一致".BsLogd() }
            oldVersion < newVersion ->{ "新版需要升级".BsLogd() }
            oldVersion > newVersion ->{ "新版比老版 版本低".BsLogd() }
        }
    }
}