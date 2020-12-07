package com.shibalnu.appmangerlib.bean

import com.shibalnu.appmangerlib.config.CMD_DEFAULT


data class ShibalnuCmdBean(var permission:Int,var cmdType:Int? = null,var cmd:Int,var action:Int? = null,var status:Int = CMD_DEFAULT,var timeOut:Long = 1000 * 10,var block:((ShibalnuCmdBean) ->Unit)? = null,var parentCmd:Int? = null)


class ShibalnuCmdCallBackBean(var cmdType:Int? = null,var cmd: Int,var action:Int? = null,var status:Int = CMD_DEFAULT,var block:((ShibalnuCmdBean) ->Unit)? = null,var parentCmd:Int? = null)