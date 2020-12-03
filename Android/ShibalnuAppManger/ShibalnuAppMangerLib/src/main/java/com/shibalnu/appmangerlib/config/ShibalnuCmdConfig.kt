package com.shibalnu.appmangerlib.config

import com.shibalnu.appmangerlib.ShibalnuAppManger
import com.shibalnu.appmangerlib.bean.ShibalnuCmdBean

open class ShibalnuCmdConfig(private val manger:ShibalnuAppManger) {
    companion object{
        //普通指令 （优先级最低）
        const val PERMISSION_NOMORL = 1

        //需要先暂停其他指令 等该等级指令有结果了 再恢复其他指令  如果有同等级指令 同等级不会暂停只会暂停比该指令等级低的指令集  同等级按照顺序执行
        const val PERMISSION_WAIT_OTHER_DO_THIS_AFTER_RESUME_OTHER = 2

        //系统指令
        const val PERMISSIOON_SYS = 3

        //目前指令集最高等级 可以自定义比该等级更高的优先级 需要修改CONFIG_PERMISSION_PRIORITY 参数来调节最高等级上限
        const val PERMISSION_PRIORITY = 200



        /**
         * CONFIG_PERMISSION_PRIORITY
         * 优先级别最高的指令
         *
         * 该指令如果 添加时 指令集中没有同级别指令 会先停止指令集所有指令 并清楚指令集 再添加该指令
         * 该指令如果 添加时 指令集中已经有同级别指令 必须等待前一个指令成功了 才能添加成功 否则 该指令添加不成功
         */
        const val CONFIG_PERMISSION_PRIORITY = PERMISSION_PRIORITY


        /**
         * cmd
         */
        //动作 打开
        const val BS_ACTION_OPEN = 10000
        //动作 关闭
        const val BS_ACTION_CLOSE = 10001
        //动作 增加
        const val BS_ACTION_ADD = 10002
        //动作 减小
        const val BS_ACTION_REDIUCE = 10003


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

    }





    fun checkCmd(cmd:ShibalnuCmdBean):Boolean{
        return cmd.permission != PERMISSIOON_SYS
    }
}