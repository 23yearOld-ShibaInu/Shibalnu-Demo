package com.trust.shibalnuandroid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import androidx.lifecycle.LiveData
import androidx.lifecycle.ViewModel
import com.trust.shibalnuandroid.debug.ShibalnuDebug
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
        val instance = ShibalnuDebug.getInstance()
        instance.initConfig()
        instance.DebugStart()


        val currentTimeMillis = System.currentTimeMillis()
        waitTime(3000){
            "waitTime success".logd()
            (System.currentTimeMillis() - currentTimeMillis).logd("耗时：")
        }

        Log.d("lhh","coroutineScope code end")


        coroutineScope.launch {

            launch {
                val currentTimeMillis = System.currentTimeMillis()
                val reuslt = suspendCoroutine<String> {
                    var i = 0
                    for (x in 0..10){
                        Thread.sleep(1000)
                        i = x
                    }
                    it.resume("我是 i:$i")
                }

                val result2 = suspendCoroutine<String>{
                    var j = 0
                    for (x in 0..4){
                        Thread.sleep(1000)
                        j = x
                    }
                    it.resume("我是 j:$j")
                }

                Log.d("lhh","$reuslt   $result2 " )
                Log.d("lhh","花费时间 ${System.currentTimeMillis() - currentTimeMillis}" )

            }


            launch {
                val start = System.currentTimeMillis()
                val as1 = async {
                    var i = 0
                    for (x in 0..5){
                        i = x
                        delay(1000)
                    }
                    i
                }.await()


                val as2 = async {
                    var i = 0
                    for (x in 0..5){
                        i = x
                        delay(1000)
                    }
                    i
                }.await()

                Log.d("lhh","as :  $as1   $as2 " )
                Log.d("lhh","as :  ${ System.currentTimeMillis() - start}" )


            }
        }

//        job.cancel()


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

fun Any.logd(msg:String = "") = Log.d("Mr_Li","$msg | $this")

fun waitTime(times:Long,block:()->Unit){
    val coroutineScope = CoroutineScope(Job())
    coroutineScope.async {
        delay(times)
        block()
    }
}

