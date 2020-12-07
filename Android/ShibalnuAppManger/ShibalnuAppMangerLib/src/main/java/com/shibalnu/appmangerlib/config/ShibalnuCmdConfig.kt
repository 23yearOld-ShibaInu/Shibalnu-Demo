package com.shibalnu.appmangerlib.config

import com.shibalnu.appmangerlib.bean.ShibalnuCmdBean

open class ShibalnuCmdConfig() {
    companion object{
        //默认最高权限
        const val CONFIG_PERMISSION_DEFAULT_PRIORITY = 200

        /**
         * CONFIG_PERMISSION_PRIORITY
         * 优先级别最高的指令
         *
         * 该指令如果 添加时 指令集中没有同级别指令 会先停止指令集所有指令 并清楚指令集 再添加该指令
         * 该指令如果 添加时 指令集中已经有同级别指令 必须等待前一个指令成功了 才能添加成功 否则 该指令添加不成功
         */
        const val CONFIG_PERMISSION_PRIORITY = CONFIG_PERMISSION_DEFAULT_PRIORITY
    }

    open fun checkCmd(cmd:ShibalnuCmdBean):Boolean{ return true }
}