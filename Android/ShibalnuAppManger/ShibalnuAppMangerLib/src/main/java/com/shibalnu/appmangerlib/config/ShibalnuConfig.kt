package com.shibalnu.appmangerlib.config

import android.util.Log
import com.shibalnu.appmangerlib.ShibalnuAppManger

private val TAG = "ShibalnuAppManger"

fun Any.ShibalnuLogd() = Log.d(TAG,"$this")



const val CMD_DEFAULT = 0
const val CMD_START = 1
const val CMD_STOP = 2
const val CMD_PAUSE = 3
const val CMD_RESTART = 4
const val CMD_NO_DO = 5
const val CMD_TIME_OUT = 6
const val CMD_END = 7
const val CMD_ERROR = 8




//指令类型
const val CMD_TYPE_BLE = 300
const val CMD_TYPE_INTERNET = 301

//车辆指令
const val CMD_TYPE_DEVICE = 302
const val CMD_TYPE_DEVICE_ANDROID_BUTTON = 303
const val CMD_TYPE_DEVICE_SERIAL_PORT = 304



lateinit var mShibalnuCmdConfig:ShibalnuCmdConfig
    private set
lateinit var mShibalnuAppManger:ShibalnuAppManger
    private set
fun initShibalnuConfig(){
    mShibalnuAppManger = ShibalnuAppManger.getInstance()
    mShibalnuCmdConfig = ShibalnuCmdConfig(mShibalnuAppManger)
}

