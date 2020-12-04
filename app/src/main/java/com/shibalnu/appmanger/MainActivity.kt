package com.shibalnu.appmanger

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.method.ScrollingMovementMethod
import android.view.View
import com.shibalnu.appmanger.model.*
import com.shibalnu.appmangerlib.bean.ShibalnuCmdBean
import com.shibalnu.appmangerlib.bean.ShibalnuCmdCallBackBean
import com.shibalnu.appmangerlib.config.*
import com.shibalnu.appmangerlib.config.ShibalnuCmdConfig.Companion.CONFIG_PERMISSION_PRIORITY
import kotlinx.android.synthetic.main.activity_main.*
import java.text.SimpleDateFormat
import java.util.*
import kotlin.concurrent.thread

class MainActivity : AppCompatActivity() {



    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        test_tv.movementMethod = ScrollingMovementMethod.getInstance();
        initCmds()
        initSharkManger()
        mShibalnuAppManger.addCmdCallBack(maxCmdCallBack)

    }
    private val REQUEST_TAG = "调用方"
    private val DO_TAG = "执行方"

    private val strList = arrayListOf<String>()

    private fun setText(str:String?){
        if (str != null) {
            strList.add("${SimpleDateFormat("HH:mm:ss").format(Date(System.currentTimeMillis()))}|$str")
            val takeLast = strList.takeLast(120).reversed()

            runOnUiThread { test_tv.text = str.let {
                var msg = ""
                takeLast.forEach {
                    msg+="$it \n"
                }
                msg
            } }
        }else{
            runOnUiThread { test_tv.text = ""}
        }

    }

    fun bleNomorlCmd(view: View) {
        mShibalnuAppManger.addCmd(ShibalnuCmdBean(PERMISSION_NOMORL,CMD_TYPE_BLE,1,2,block = { getReuslt(REQUEST_TAG,it) }))
    }
    fun bleWaitCmd(view: View) { mShibalnuAppManger.addBleCmd(PERMISSION_WAIT_OTHER_DO_THIS_AFTER_RESUME_OTHER,2,2) { getReuslt(REQUEST_TAG,it) } }
    fun bleMaxPermissionCmd(view: View) { mShibalnuAppManger.addBleCmd(CONFIG_PERMISSION_PRIORITY,3,3) { getReuslt(REQUEST_TAG,it) } }
    fun internetNomorlCmd(view: View) { mShibalnuAppManger.addInternetCmd(PERMISSION_NOMORL,4,4) { getReuslt(REQUEST_TAG,it) } }
    fun internetWaitCmd(view: View) { mShibalnuAppManger.addInternetCmd(PERMISSION_WAIT_OTHER_DO_THIS_AFTER_RESUME_OTHER,5,5) { getReuslt(REQUEST_TAG,it) } }
    fun internetMaxPermissionCmd(view: View) {

    }
    fun closeInternetMaxPermissionCmd(view: View) {
    }
    fun serportNomorlCmd(view: View) { mShibalnuAppManger.addSerialPortCmd(PERMISSION_NOMORL,7,7) { getReuslt(REQUEST_TAG,it) } }
    fun serportWaitCmd(view: View) { mShibalnuAppManger.addSerialPortCmd(PERMISSION_WAIT_OTHER_DO_THIS_AFTER_RESUME_OTHER,8,8) { getReuslt(REQUEST_TAG,it) } }
    fun serportMaxPermissionCmd(view: View) { mShibalnuAppManger.addSerialPortCmd(CONFIG_PERMISSION_PRIORITY,9,9) { getReuslt(REQUEST_TAG,it) } }

    fun endMaxCmd(view: View) { mShibalnuAppManger.stopPriorityCmd() }

    private val maxCmdCallBack = ShibalnuCmdCallBackBean(cmd = 3,block = {
        getReuslt(DO_TAG,it)
        thread {
            Thread.sleep(2000)
            mShibalnuAppManger.endCmdCallBack(it)
        }
    })


    private fun getReuslt(user:String,cmdBean: ShibalnuCmdBean,isShowTx:Boolean = true):String{
        val cmdType = when (cmdBean.cmdType) {
            CMD_TYPE_BLE -> { "BLE" }
            CMD_TYPE_INTERNET -> { "网络" }
            CMD_TYPE_DEVICE_ANDROID_BUTTON -> { "仪表Android按钮" }
            CMD_TYPE_DEVICE_SERIAL_PORT -> { "串口" }
            else -> { "未知cmd类型:${cmdBean.cmdType}" }
        }



        val result = when (cmdBean.status) {
            CMD_END -> { "指令执行完毕" }
            CMD_START -> { "指令执行开始" }
            CMD_NO_DO -> { "当前已经有优先级最高的指令无法添加" }
            CMD_STOP -> { "指令停止｜中断" }
            CMD_ERROR -> { "指令失败" }
            CMD_TIME_OUT -> { "指令超时" }
            CMD_ADD_ERROR -> { "添加指令失败" }
            else -> { " 未知的status:${cmdBean.status}" }
        }
        val s = "$user |$cmdType |${cmdBean.cmd}|${cmdBean.action}| ${cmdBean.permission} |$result"
        if (isShowTx) { setText(s) }
        return s
    }


    fun clearLog(view: View) {
        strList.clear()
        setText(null)
    }
    fun findCmdList(view: View) {
        val str = mShibalnuAppManger.getCmdList().let {
            var msgStr = "开始查询: \n"
            msgStr += "${it.size} \n"
            if (it.isNullOrEmpty()) {
                msgStr  = "当前没有指令集 \n"
            }else{
                it.forEach {bean->
                    msgStr+="${getReuslt("查询",bean,false)} \n"
                }
            }
            msgStr += "查询结束 \n"
            msgStr
        }
        setText(str)
    }
    fun stopCmdList(view: View) {
        mShibalnuAppManger.stopAllCmd()
        setText("清空指令集成功")
    }

    fun addErrorBtn(view: View) {
        mShibalnuAppManger.addCmd(ShibalnuCmdBean(permission = 22,cmd = 22,block = { getReuslt(REQUEST_TAG,it) }))
    }

    fun sendMaxCmds(view: View) {}
    fun closeMaxCmds(view: View) {
        cmdsConfigList[BS_CMD_OTA]?.let {
            it.filter { it.cmd != BS_CMD_OTA &&  it.status == CMD_START}.let { beans->
                if (!beans.isNullOrEmpty()) {
                    endCmd(beans[0].cmd,BS_CMD_OTA)
                    setText("结束子指令成功")
                }else{
                    setText("所有相关指令都结束")
                }
            }
        }
    }


    companion object{
        private val cmdConfigList = arrayListOf<ShibalnuCmdBean>()
        private val cmdsConfigList = hashMapOf<Int,ArrayList<ShibalnuCmdBean>>()

        fun getCmds() = cmdsConfigList
    }
    private fun initCmds(){
        cmdConfigList.add(ShibalnuCmdBean(PERMISSION_NOMORL,cmd = BS_CMD_WIFI))
        cmdConfigList.add(ShibalnuCmdBean(PERMISSION_NOMORL,cmd = BS_CMD_VIDEO))
        cmdConfigList.add(ShibalnuCmdBean(PERMISSION_NOMORL,cmd = BS_CMD_MUTE))
        cmdConfigList.add(ShibalnuCmdBean(PERMISSION_NOMORL,cmd = BS_CMD_HOME))

        cmdConfigList.add(ShibalnuCmdBean(PERMISSION_PRIORITY,cmd = BS_CMD_OTA))

        val otaCmds = arrayListOf<ShibalnuCmdBean>()
        otaCmds.add(getCmdBean(BS_CMD_OTA, BS_ACTION_OPEN))
        otaCmds.add(getCmdBean(BS_CMD_WIFI, BS_ACTION_OPEN).apply { this.parentCmd = BS_CMD_OTA })
        otaCmds.add(getCmdBean(BS_CMD_VIDEO, BS_ACTION_OPEN).apply { this.parentCmd = BS_CMD_OTA })
        otaCmds.add(getCmdBean(BS_CMD_MUTE, BS_ACTION_OPEN).apply { this.parentCmd = BS_CMD_OTA })
        otaCmds.add(getCmdBean(BS_CMD_HOME, BS_ACTION_OPEN).apply { this.parentCmd = BS_CMD_OTA })
        cmdsConfigList[BS_CMD_OTA] = otaCmds
    }

    private fun getDafultCmdBean(cmd:Int,action:Int? = null) = ShibalnuCmdBean(permission = PERMISSION_NOMORL,cmd = cmd,action = action)

    fun getCmdBean(cmd:Int,action: Int? = null):ShibalnuCmdBean = cmdConfigList.find { it.cmd == cmd }?.copy()?.apply { this.action = action } ?: getDafultCmdBean(cmd)
}



