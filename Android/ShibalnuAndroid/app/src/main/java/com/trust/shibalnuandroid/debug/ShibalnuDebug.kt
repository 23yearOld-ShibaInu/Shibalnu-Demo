package com.trust.shibalnuandroid.debug


import com.trust.shibalnuandroid.mainlogd
import com.trust.shibalnuandroid.waitTime
import kotlinx.coroutines.*
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine
import kotlin.properties.Delegates

class ShibalnuDebug {
        companion object{
            private lateinit var mShibalnuDebug:ShibalnuDebug

            fun getInstance():ShibalnuDebug{
                if (!::mShibalnuDebug.isInitialized) {
                    mShibalnuDebug = ShibalnuDebug()
                }
                return mShibalnuDebug
            }
        }


    fun initConfig(){
        val user = User()
        user.namg = "帅哥"
        user.namg = "李帅哥"

        user.namg.mainlogd("获取name:")
    }




    class User{
        var namg:String by Delegates.observable("陕西吴彦祖"){
            prop,old,new->
            "prop:$prop | old:$old | new:$new".mainlogd()
        }
    }

     fun DebugStart(){
         val job = Job()
         CoroutineScope(job).launch {
                waitTime(1000){
                    "计时结束".mainlogd()
                }
         }

    }




}