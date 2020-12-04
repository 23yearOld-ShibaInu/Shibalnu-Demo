package com.shibalnu.appmangerlib

import com.shibalnu.appmangerlib.bean.ShibalnuCmdBean
import com.shibalnu.appmangerlib.bean.ShibalnuCmdCallBackBean
import com.shibalnu.appmangerlib.config.*
import com.shibalnu.appmangerlib.config.ShibalnuCmdConfig.Companion.CONFIG_PERMISSION_PRIORITY

class ShibalnuAppManger {
    companion object{
        private lateinit var mShibalnuAppManger:ShibalnuAppManger

        fun getInstance():ShibalnuAppManger{
            if (!::mShibalnuAppManger.isInitialized) {
                mShibalnuAppManger = ShibalnuAppManger()
            }
            return mShibalnuAppManger
        }
    }

    private val cmdList = arrayListOf<ShibalnuCmdBean>()

    private val cmdCallBack = arrayListOf<ShibalnuCmdCallBackBean>()

    fun addCmd(cmd:ShibalnuCmdBean) = check(cmd)

    fun addBleCmd(permission: Int,cmd:Int,action:Int? = null,timeOut:Long = 1000 *5,block:((ShibalnuCmdBean) ->Unit)? = null){
        check(ShibalnuCmdBean(permission,CMD_TYPE_BLE,cmd,action,timeOut = timeOut,block = block))
    }

    fun addInternetCmd(permission: Int,cmd:Int,action:Int? = null,timeOut:Long = 1000 *5,block:((ShibalnuCmdBean) ->Unit)? = null){
        check(ShibalnuCmdBean(permission, CMD_TYPE_INTERNET,cmd,action,timeOut = timeOut,block = block))
    }

    fun addAndroidCmd(permission: Int,cmd:Int,action:Int? = null,timeOut:Long = 1000 *5,block:((ShibalnuCmdBean) ->Unit)? = null){
        check(ShibalnuCmdBean(permission, CMD_TYPE_DEVICE_ANDROID_BUTTON,cmd,action,timeOut = timeOut,block = block))
    }

    fun addSerialPortCmd(permission: Int,cmd:Int,action:Int? = null,timeOut:Long = 1000 *5,block:((ShibalnuCmdBean) ->Unit)? = null){
        check(ShibalnuCmdBean(permission, CMD_TYPE_DEVICE_SERIAL_PORT,cmd,action,timeOut = timeOut,block = block))
    }



    private fun check(cmd:ShibalnuCmdBean):Boolean{
        "添加的cmd :$cmd".ShibalnuLogd()
        return if (cmdList.isNullOrEmpty()) {
            if (mShibalnuCmdConfig.checkCmd(cmd)) {
                startCmd(cmd)
                true
            }else{
                addError(cmd)
                false
            }

        }else{
            if (!getCmdListIsHaveMaxPermission()) {
                if (cmd.permission == ShibalnuCmdConfig.CONFIG_PERMISSION_PRIORITY) {
                    stopOtherThanPriority()
                    startCmd(cmd)
                    true
                }else{
                    if (mShibalnuCmdConfig.checkCmd(cmd)) {
                        startCmd(cmd)
                        true
                    }else{
                        addError(cmd)
                        false
                    }
                }
            }else{
                when (checkPermission(cmd)) {
                    //有同种CMD 不同action
                    //停止指令集的cmd
                    CHECK_SAME_PERMISSION_DIFFERENT_ACTION -> {
                        getCmdList().find { it.cmd== cmd.cmd }?.let { endCmdCallBack(it) }
                        true
                    }
                    //有同种CMD 相同action
                    //无法添加
                    CHECK_SAME_PERMISSION_SAME_ACTION -> {
                        noAddCmd(cmd)
                        false
                    }
                    //无法添加
                    else -> {
                        if (cmd.parentCmd == getMaxPernissionCmd()!!.cmd) {
                            //最高等级指令附属指令
                            startCmd(cmd)
                        }else{
                            noAddCmd(cmd)
                        }
                        false
                    }
                }
            }
        }
    }


    private fun stopOtherThanPriority(){
        val filter = cmdList.filter { it.permission != ShibalnuCmdConfig.CONFIG_PERMISSION_PRIORITY }
        filter.forEach { stopCmd(it) }
    }

    private fun startCmd(cmd: ShibalnuCmdBean) {
        cmdList.add(cmd)
        changeCmd(cmd.apply { status = CMD_START })
        cmdCallBack.find { it.cmd == cmd.cmd }?.block?.invoke(cmd)
    }


    private fun stopCmd(cmd:ShibalnuCmdBean) {
//        cmdList.find { it.cmd == cmd.cmd && it.status == CMD_START }?.let {
            cmdList.removeAll(changeCmd(cmd.apply { status = CMD_STOP }))
//        }
    }

    private fun noAddCmd(cmd: ShibalnuCmdBean) = changeCmd(cmd.apply { status = CMD_NO_DO })
    private fun addError(cmd:ShibalnuCmdBean) = changeCmd(cmd.apply { status = CMD_ADD_ERROR })

    private fun timeOutCmd(cmd:ShibalnuCmdBean) = cmdList.removeAll(changeCmd(cmd.apply { status = CMD_TIME_OUT }))

    private fun errorCmd(cmd:ShibalnuCmdBean) = cmdList.removeAll(changeCmd(cmd.apply { status = CMD_ERROR }))



    private fun changeCmd(cmd: ShibalnuCmdBean):List<ShibalnuCmdBean>{
        val filter = cmdList.filter { it.cmd == cmd.cmd }
        if (filter.isNullOrEmpty()) {
            cmd.block?.invoke(cmd)
        }
        filter.forEach { it.block?.invoke(cmd) }
        return filter
    }



    fun addCmdCallBack(cmdc: ShibalnuCmdCallBackBean){
        removeCmdCallBack(cmdc)
        cmdCallBack.add(cmdc)
    }

    fun removeCmdCallBack(cmdc:ShibalnuCmdCallBackBean){
        cmdCallBack.remove(cmdc)
    }

    /**
     * 执行指令模块调用 通知执行结果
     */

    //执行完成 成功
    fun endCmdCallBack(cmd: ShibalnuCmdBean){ chengeCmd(status = CMD_END,cmd = cmd)?.let {
        cmdList.remove(it)
        it.block?.invoke(it) } }

    //执行停止 中断
    fun stopCmdCallBack(cmd: ShibalnuCmdBean){ chengeCmd(status = CMD_STOP,cmd = cmd)?.let { it.block?.invoke(it) } }

    //执行超时
    fun timeOutCmdCallBack(cmd: ShibalnuCmdBean) { chengeCmd(status = CMD_TIME_OUT,cmd = cmd)?.let { it.block?.invoke(it) } }

    //执行失败 异常
    fun errorCmdCallBack(cmd:ShibalnuCmdBean){ chengeCmd(status = CMD_ERROR,cmd = cmd)?.let { it.block?.invoke(it) } }

    fun chengeCmd(status:Int,cmd: ShibalnuCmdBean):ShibalnuCmdBean?{
        return cmdList.find { it.cmd == cmd.cmd }?.let {
            it.status = status
            it
        }
    }


    fun stopAllCmd(){
        getCmdList().forEach {
            it.status = CMD_STOP
            it.block?.invoke(it)
        }
        getCmdList().clear()
    }

    fun stopPriorityCmd(){
        cmdList.find { it.permission == ShibalnuCmdConfig.CONFIG_PERMISSION_PRIORITY }?.let {
            stopCmd(it)
        }
    }

    fun getCmdList() = cmdList


    private fun getCmdListIsHaveMaxPermission() = !cmdList.none { it.permission == CONFIG_PERMISSION_PRIORITY }
    private fun getMaxPernissionCmd() = cmdList.find { it.permission == CONFIG_PERMISSION_PRIORITY }

    private fun checkPermission(cmd:ShibalnuCmdBean):Int{
        return if (cmd.permission == ShibalnuCmdConfig.CONFIG_PERMISSION_PRIORITY) {
            "开始检查".ShibalnuLogd()
            getCmdList().find { it.cmd == cmd.cmd  }?.let {
                "检查的 cmd:${cmd}".ShibalnuLogd()
                "数据集中的 cmd:$it".ShibalnuLogd()
                if (it.action == cmd.action) {
                    CHECK_SAME_PERMISSION_SAME_ACTION
                }else{
                    CHECK_SAME_PERMISSION_DIFFERENT_ACTION
                }
            }?:CHECK_DIFFERENT_PERMISSION_SAME
        }else{ CHECK_DIFFERENT_PERMISSION_SAME }

    }
}