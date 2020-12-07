package com.trust.shibalnucpp

import android.util.Log

class Dog  {
    companion object{
        val TAG = "LiHao Dog"
        fun showLog(msg:String){
            Log.d(TAG,msg)
        }
    }

    init {

        showLog("Dog 构造被调用")
    }
}