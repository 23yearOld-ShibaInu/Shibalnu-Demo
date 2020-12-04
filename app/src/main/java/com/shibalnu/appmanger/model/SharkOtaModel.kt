package com.shibalnu.appmanger.model

import com.shibalnu.appmanger.MainActivity.Companion.getCmds
import com.shibalnu.appmangerlib.bean.ShibalnuCmdBean
import com.shibalnu.appmangerlib.bean.ShibalnuCmdCallBackBean
import com.shibalnu.appmangerlib.config.*

class SharkOtaModel {
//
//    fun init(){
//        getCmds()[BS_CMD_OTA]?.let {
//            it.forEach {cmd->
//                mShibalnuAppManger.addCmdCallBack(ShibalnuCmdCallBackBean(cmd = cmd.cmd,block = otaBlock))
//            }
//        }
//    }
//


    fun init(){
        getCmds()[BS_CMD_OTA]?.let {
            it.forEach {  it.block = otaBlock }
            addCmd(it[0])
        }
    }

    private val otaBlock:(ShibalnuCmdBean)->Unit = {bean->
        when (bean.status) {
            CMD_START -> { "开始".SharkMangerLogd(bean.toString()) }
            CMD_STOP -> { "停止".SharkMangerLogd(bean.toString()) }
            CMD_PAUSE -> { "暂停".SharkMangerLogd(bean.toString()) }
            CMD_RESTART -> { "恢复".SharkMangerLogd(bean.toString()) }
            CMD_TIME_OUT -> { "超时".SharkMangerLogd(bean.toString()) }
            CMD_END -> { "完成".SharkMangerLogd(bean.toString()) }
            CMD_ERROR -> { "异常".SharkMangerLogd(bean.toString()) }
            CMD_NO_DO -> { "已经有最高的级别的指令 无法添加指令".SharkMangerLogd(bean.toString()) }
            else -> { "未知:${bean.status}".SharkMangerLogd(bean.toString()) }
        }


        getCmds()[BS_CMD_OTA]?.let { it ->
            it.find { it.cmd == bean.cmd }?.let { it.status = bean.status }
            getCmds()[BS_CMD_OTA] = it
        }

        if(bean.status == CMD_START && bean.cmd == BS_CMD_OTA){
            getCmds()[BS_CMD_OTA]!!.filter { it.status == CMD_DEFAULT && it.cmd != BS_CMD_OTA }.let {
                if (it.isNotEmpty()) {
                    addCmd(it[0])
                }
            }
        }else if (bean.status == CMD_END) {
            getCmds()[BS_CMD_OTA]?.let { it ->
                getCmds()[BS_CMD_OTA]!!.filter { it.status == CMD_DEFAULT && it.cmd != BS_CMD_OTA }.let {
                    if (it.isNotEmpty()) {
                        addCmd(it[0])
                    }
                }

            }

            getCmds()[BS_CMD_OTA]?.let {
                if (it.isNotEmpty()) {
                    if (it[it.size-1].cmd == bean.cmd && bean.cmd != CMD_START) {
                        endCmd(BS_CMD_OTA)
                    }
                }


            }

        }





    }
}