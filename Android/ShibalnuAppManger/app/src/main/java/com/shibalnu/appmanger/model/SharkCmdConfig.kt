package com.shibalnu.appmanger.model

import com.shibalnu.appmangerlib.bean.ShibalnuCmdBean

//普通指令 （优先级最低）
const val PERMISSION_NOMORL = 1

//需要先暂停其他指令 等该等级指令有结果了 再恢复其他指令  如果有同等级指令 同等级不会暂停只会暂停比该指令等级低的指令集  同等级按照顺序执行
const val PERMISSION_WAIT_OTHER_DO_THIS_AFTER_RESUME_OTHER = 2

//系统指令
const val PERMISSIOON_SYS = 3

//目前指令集最高等级 可以自定义比该等级更高的优先级 需要修改CONFIG_PERMISSION_PRIORITY 参数来调节最高等级上限
const val PERMISSION_PRIORITY = 200







/**
 * action
 */
//动作 打开
const val BS_ACTION_OPEN = 10000
//动作 关闭
const val BS_ACTION_CLOSE = 10001
//动作 增加
const val BS_ACTION_ADD = 10002
//动作 减小
const val BS_ACTION_REDIUCE = 10003


/**
 * cmd
 */

//收音机 FM
const val BS_CMD_RADIO = 1000
const val BS_CMD_FM = 1001

const val BS_CMD_AM = 1002

//蓝牙电话
const val BS_CMD_BLE_PHONE = 1003
//蓝牙
const val BS_CMD_BLE = 1004

//蓝牙音乐
const val BS_CMD_BLE_MUSIC = 1005

//usb音乐
const val BS_CMD_USB_MUSIC = 1006

//设置页面
const val BS_CMD_SETTINGS = 1007

//音效设置
const val BS_CMD_SOUND_EFFECT_SETTINGS = 1008

//视频
const val BS_CMD_VIDEO = 1009

//静音
const val BS_CMD_MUTE = 1010

//wifi
const val BS_CMD_WIFI = 1011

//主页
const val BS_CMD_HOME = 1012

//屏幕
const val BS_CMD_SCREEN = 1013

//帮助
const val BS_CMD_HELP = 1014

//carlife
const val BS_CMD_CAR_LIFE = 1015

//音量调节
const val BS_CMD_VOLUME_ADJUSTMENT = 1016

//亮度调节
const val BS_CMD_SCREEN_DIMMING = 1017

//ota 升级
const val BS_CMD_OTA = 1018


private val cmdConfigList = arrayListOf<ShibalnuCmdBean>()
private val cmdsConfigList = hashMapOf<Int,ArrayList<ShibalnuCmdBean>>()

fun getCmds() = cmdsConfigList

fun initCmdConfig(){
    cmdConfigList.add(ShibalnuCmdBean(PERMISSION_NOMORL,cmd = BS_CMD_WIFI))
    cmdConfigList.add(ShibalnuCmdBean(PERMISSION_PRIORITY,cmd = BS_CMD_OTA))
}

fun initCmdsConfig(){
    //ota
    val otaCmds = arrayListOf<ShibalnuCmdBean>()
    otaCmds.add(getCmdBean(BS_CMD_WIFI, BS_ACTION_OPEN).apply { this.parentCmd = BS_CMD_OTA })
    cmdsConfigList[BS_CMD_OTA] = otaCmds
}

private fun getDafultCmdBean(cmd:Int,action:Int? = null) = ShibalnuCmdBean(permission = PERMISSION_NOMORL,cmd = cmd,action = action)

fun getCmdBean(cmd:Int,action: Int? = null):ShibalnuCmdBean = cmdConfigList.find { it.cmd == cmd }?.copy()?.apply { this.action = action } ?: getDafultCmdBean(cmd)