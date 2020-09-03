package com.trust.shibalnuandroid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.coroutines.*
import java.util.concurrent.Delayed
import kotlin.concurrent.thread
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val job = Job()
        CoroutineScope(job) .launch {
                Test()
        }
    }


    suspend fun Test(){

        val s = suspendCoroutine<String> {
            val block = {msg:String->
                it.resume(msg)
            }
            Thread.sleep(1000 *3)
            block("我是返回值")

        }

        Log.d("lhh","sss:${s}")
    }
}