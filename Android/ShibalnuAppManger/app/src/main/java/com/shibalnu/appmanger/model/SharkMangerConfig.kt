package com.shibalnu.appmanger.model

import android.util.Log
import com.shibalnu.appmangerlib.bean.ShibalnuCmdBean
import com.shibalnu.appmangerlib.config.CMD_DEFAULT
import com.shibalnu.appmangerlib.config.ShibalnuCmdConfig.Companion.CONFIG_PERMISSION_PRIORITY
import com.shibalnu.appmangerlib.config.initShibalnuConfig
import com.shibalnu.appmangerlib.config.mShibalnuAppManger

fun Any.SharkMangerLogd(msg:String = "") = Log.d("SharkManger","$msg|$this")

fun initSharkManger(){
    initCmdConfig()
    initCmdsConfig()
    initShibalnuConfig(SharkMangerModel())
    SharkOtaModel()
}

fun addNomorlCmd(cmdType: Int, cmd: Int, action: Int? = null, status: Int = CMD_DEFAULT, timeOut: Long = 1000 * 5, block: ((ShibalnuCmdBean) -> Unit)?){
    mShibalnuAppManger.addCmd(getCmdBean(cmd).apply {
        this.permission = PERMISSION_NOMORL
        this.action = action
        this.status = status
        this.timeOut = timeOut
        this.cmdType = cmdType
        this.block = block
    })
}

fun addPriorityCmd(cmdType: Int, cmd: Int, action: Int? = null, status: Int = CMD_DEFAULT, timeOut: Long = 1000 * 5, block: ((ShibalnuCmdBean) -> Unit)?){
    mShibalnuAppManger.addCmd(getCmdBean(cmd).apply {
        this.permission =CONFIG_PERMISSION_PRIORITY
        this.action = action
        this.status = status
        this.timeOut = timeOut
        this.cmdType = cmdType
        this.block = block
    })
}

fun errorCmd(cmd:Int,parentCmd:Int) = mShibalnuAppManger.errorCmdCallBack(getCmdBean(cmd).apply { this.parentCmd = parentCmd })

fun endCmd(cmd:Int,parentCmd: Int? = null) = mShibalnuAppManger.endCmdCallBack(getCmdBean(cmd).apply { this.parentCmd = parentCmd })




fun addCmd(cmdBean:ShibalnuCmdBean) = mShibalnuAppManger.addCmd(cmdBean)


//fun getCmdBean(permission:Int,cmdType:Int,cmd:Int,action:Int?,status:Int,timeOut:Long,block: ((ShibalnuCmdBean) -> Unit)?): ShibalnuCmdBean = ShibalnuCmdBean(permission = permission,cmdType = cmdType,cmd = cmd,action = action,status = status,timeOut = timeOut,block = block)