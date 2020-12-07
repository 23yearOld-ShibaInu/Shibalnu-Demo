package com.shibalnu.appmanger.model

import com.shibalnu.appmangerlib.bean.ShibalnuCmdBean
import com.shibalnu.appmangerlib.config.ShibalnuCmdConfig

class SharkMangerModel : ShibalnuCmdConfig() {

    override fun checkCmd(cmd: ShibalnuCmdBean): Boolean {
        return true
    }


}