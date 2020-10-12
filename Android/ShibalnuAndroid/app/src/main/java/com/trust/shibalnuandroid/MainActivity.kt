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
        val coroutineScope = CoroutineScope(job)
        coroutineScope .launch {
            Test("1")
        }

        coroutineScope .launch {
            Test("2")
        }

        Log.d("lhh","coroutineScope code end")
        job.cancel()
    }


    suspend fun Test(msg:String){

        val s = suspendCoroutine<String> {
            val block = {msg:String->
                it.resume(msg)
            }
            Thread.sleep(1000 *3)
            block("我是返回值$msg")

        }

        Log.d("lhh","sss:${s}")
    }
}