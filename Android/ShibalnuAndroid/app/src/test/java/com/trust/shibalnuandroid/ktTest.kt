package com.trust.shibalnuandroid

import kotlin.text.StringBuilder

/**
 * Created by Trust on 2020/7/6
 */
object HigherOrderFunction{
    init {
        val n1 = 100
        val n2 = 20

        println("numlAndNum2(n1,n2,::plus):${numlAndNum2(n1,n2,::plus)}")
        println("numlAndNum2(n1,n2,::minus):${ numlAndNum2(n1,n2,::minus)}")
        println("-------")
        println("numlAndNum2(n1,n2):${numlAndNum2(n1,n2){n1,n2-> n1+n2}}")
        println("numlAndNum2(n1,n2):${numlAndNum2(n1,n2){n1,n2-> n1-n2}}")
        println("-------")
        println("模拟apply")
        val list = listOf("你","我","他")
        val result = StringBuilder().build {
            append("start\n")
            for (s in list) {
                append(s).append("\n")
            }
            append("end")
        }
        println("result:${result.toString()}")
    }

    fun plus(num1:Int,num2: Int):Int{
        return num1 + num2
    }

    fun minus(num1: Int,num2: Int):Int{
        return num1 - num2

    }


    fun numlAndNum2(num1:Int,num2:Int,operation:(Int,Int)->Int):Int{
        return operation(num1,num2)
    }


    fun StringBuilder.build(block:StringBuilder.() -> Unit):StringBuilder{
        block()
        return this
    }


    fun Any.logp(msg:String = ""){
        System.out.println("$msg ${this}")
    }
}