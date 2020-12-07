package com.trust.shibalnuandroid

import kotlinx.coroutines.*
import org.junit.Test
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

class KtTestXC {


    @Test
    fun test(){
        GlobalScope.launch {
            println("codes run in coroutine scope")
            delay(1500)
            println("codes run in coroutine scope finished")
        }
        Thread.sleep(1000)
    }

    @Test
    fun test1(){
        runBlocking {
            println("codes run in runBlocking coroutine scope")
            delay(1500)
            println("codes run in runBlocking coroutine scope finished")
        }
    }


    @Test
    fun test02(){
        runBlocking {
            launch {
                println("launch1")
                delay(1000)
                println("launch1 finished")
            }

            launch {
                println("launch2")
                delay(1000)
                println("launch2 finished")
            }

             test04()
            println("runBlocking test04 finished")
        }
    }


    suspend fun test03(){
        println("test03 ")
        delay(1000)
        println("test03 finished")
    }

    suspend fun test04() = coroutineScope {
        launch {
            println("test04")
            delay(2000)
            println("test04 finished")
        }
    }

    @Test
    fun test05(){
        val job = GlobalScope.launch {
            //...
        }
        job.cancel()
    }


    @Test
    fun test06(){
        runBlocking {
            val currentTimeMillis = System.currentTimeMillis()
            val result = async {
                delay(1000)
                5+5
            }

            val result2 = async {
                delay(3000)
                5+5
            }

            println("协程执行结果： ${result.await() + result2.await()}")
            println("end ${ System.currentTimeMillis() - currentTimeMillis}")
        }
    }

    @Test
    fun test07(){
        runBlocking {

            val currentTimeMillis = System.currentTimeMillis()
            val reuslt = withContext(Dispatchers.Default){
                delay(2000)
                5+5
            }
            val reuslt2 = withContext(Dispatchers.Default){
                delay(2000)
                5+5
            }
            println("withContext:${reuslt+reuslt2}")
            println("执行结果 : ${System.currentTimeMillis() - currentTimeMillis}")
        }
    }


    @Test
     fun test08(){
        runBlocking {

            Thread.currentThread().name.BsLogd("runBlocking")
                launch {
                    request().BsLogd()
                    Thread.currentThread().name.BsLogd("launch")
                }
            "request 117line".BsLogd()
        }

    }


    suspend fun request():String{
        return suspendCoroutine { continuation ->
            Thread.sleep(2000)
            Thread.currentThread().name.BsLogd("request")
            continuation.resume("我是 request result")
        }
    }

    fun foo(){
        println("foo 1")
        println("foo 2")
        println("foo 3")
        println("foo 4")
    }

    fun bar(){
        println("bar 1")
        println("bar 2")
        println("bar 3")
        println("bar 4")
    }




    @Test
    fun test09(){

    }
}