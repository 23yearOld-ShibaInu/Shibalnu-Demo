package com.shibalnu.appmanger

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.method.ScrollingMovementMethod
import android.util.Log
import android.view.View
import com.shibalnu.appmangerlib.bean.ShibalnuCmdBean
import com.shibalnu.appmangerlib.bean.ShibalnuCmdCallBackBean
import com.shibalnu.appmangerlib.config.*
import kotlinx.android.synthetic.main.activity_main.*
import java.text.SimpleDateFormat
import java.util.*
import kotlin.concurrent.thread

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        initShibalnuConfig()
        mShibalnuAppManger.addCmdCallBack(maxCmdCallBack)
        test_tv.movementMethod = ScrollingMovementMethod.getInstance();
    }
    val REQUEST_TAG = "调用方"
    val DO_TAG = "执行方"

    val strList = arrayListOf<String>()

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
        mShibalnuAppManger.addCmd(ShibalnuCmdBean(ShibalnuCmdConfig.PERMISSION_NOMORL,CMD_TYPE_BLE,ShibalnuCmdConfig.BS_CMD_VIDEO,ShibalnuCmdConfig.BS_ACTION_OPEN,block = { getReuslt(REQUEST_TAG,it) }))
    }
    fun bleWaitCmd(view: View) { mShibalnuAppManger.addBleCmd(ShibalnuCmdConfig.PERMISSION_WAIT_OTHER_DO_THIS_AFTER_RESUME_OTHER,2,2) { getReuslt(REQUEST_TAG,it) } }
    fun bleMaxPermissionCmd(view: View) { mShibalnuAppManger.addBleCmd(ShibalnuCmdConfig.CONFIG_PERMISSION_PRIORITY,3,3) { getReuslt(REQUEST_TAG,it) } }
    fun internetNomorlCmd(view: View) { mShibalnuAppManger.addInternetCmd(ShibalnuCmdConfig.PERMISSION_NOMORL,4,4) { getReuslt(REQUEST_TAG,it) } }
    fun internetWaitCmd(view: View) { mShibalnuAppManger.addInternetCmd(ShibalnuCmdConfig.PERMISSION_WAIT_OTHER_DO_THIS_AFTER_RESUME_OTHER,5,5) { getReuslt(REQUEST_TAG,it) } }
    fun internetMaxPermissionCmd(view: View) {

    }
    fun closeInternetMaxPermissionCmd(view: View) {
    }
    fun serportNomorlCmd(view: View) { mShibalnuAppManger.addSerialPortCmd(ShibalnuCmdConfig.PERMISSION_NOMORL,7,7) { getReuslt(REQUEST_TAG,it) } }
    fun serportWaitCmd(view: View) { mShibalnuAppManger.addSerialPortCmd(ShibalnuCmdConfig.PERMISSION_WAIT_OTHER_DO_THIS_AFTER_RESUME_OTHER,8,8) { getReuslt(REQUEST_TAG,it) } }
    fun serportMaxPermissionCmd(view: View) { mShibalnuAppManger.addSerialPortCmd(ShibalnuCmdConfig.CONFIG_PERMISSION_PRIORITY,9,9) { getReuslt(REQUEST_TAG,it) } }

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

        val permission = when(cmdBean.permission){
            ShibalnuCmdConfig.PERMISSION_NOMORL ->{ "普通权限" }
            ShibalnuCmdConfig.PERMISSION_WAIT_OTHER_DO_THIS_AFTER_RESUME_OTHER ->{ "一般权限" }
            ShibalnuCmdConfig.CONFIG_PERMISSION_PRIORITY ->{ "最高权限" }
            ShibalnuCmdConfig.PERMISSIOON_SYS ->{ "添加失败" }
            else -> { "未知权限:${cmdBean.permission}" }
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
        val s = "$user |$cmdType | $permission |$result"
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
        mShibalnuAppManger.addCmd(ShibalnuCmdBean(permission = ShibalnuCmdConfig.PERMISSIOON_SYS,cmd = 22){ getReuslt(REQUEST_TAG,it) })
    }


}



