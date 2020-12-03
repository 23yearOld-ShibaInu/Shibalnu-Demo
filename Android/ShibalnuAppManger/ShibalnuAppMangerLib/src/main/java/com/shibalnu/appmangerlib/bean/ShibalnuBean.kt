package com.shibalnu.appmangerlib.bean

import com.shibalnu.appmangerlib.config.CMD_DEFAULT


data class ShibalnuCmdBean(var permission:Int,val cmdType:Int? = null,val cmd:Int,var action:Int? = null,var status:Int = CMD_DEFAULT,val timeOut:Long = 1000 * 10,var block:((ShibalnuCmdBean) ->Unit)? = null)


class ShibalnuCmdCallBackBean(val cmdType:Int? = null,val cmd: Int,var action:Int? = null,var status:Int = CMD_DEFAULT,var block:((ShibalnuCmdBean) ->Unit)? = null)