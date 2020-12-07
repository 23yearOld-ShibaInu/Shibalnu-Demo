package com.trust.shibalnuandroid

import android.content.Context
import android.content.SharedPreferences
import android.util.Log
import org.junit.Test
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

}


class ktTest{

    inline fun inlineTest(block1:()->Unit,noinline block2:()->Unit,block3:()->Unit){}


    @Test
    fun ktTest1(){
        "ktTest1 start".logd()
        val str = ""
        printString(str){s->
            "lambda start".logd()
            if(s.isEmpty()) return
            s.logd()
            "lambda end".logd()
        }
        "ktTest1 end".logd()

    }

     inline fun printString(str:String,block:(String)-> Unit){
        "printString begin".logd()
        block(str)
        "printString end".logd()
     }



    @Test
    fun ktTest02(){
//        getSharedPreferences("data", Context.MODE_PRIVATE).trustOpen{
//            putString("name","Tom")
//        }
    }



    @Test
    fun ktTest03(){
        "".build {  }
    }

    @Test
    fun ktTest04(){
        val instance = ClassBikeListener.getInstance(BikeHelp())
        instance.reusltTest05Listener { it.logd("lambda reusltTest05Listener") }

        test("addasd").toString()

        instance.test05()
    }


    fun test(msg:String):String{
        return msg
    }



    class MySet<T>(val helperSet:HashSet<T>):Set<T> by helperSet{
        override fun isEmpty() = false

        fun helloWorld() = print("helloWorld")
    }

    interface BikeListener{
        fun test01()
        fun test02()
        fun test03()
        fun test04()
        fun test05()
    }


    private val bike1 = object :BikeListener{
        override fun test01() {}

        override fun test02() {}

        override fun test03() {}

        override fun test04() {}

        override fun test05() {}
    }


    class BikeHelp():BikeListener{
        override fun test01() { "BikeHelp1" .logd() }

        override fun test02() { "BikeHelp2" .logd() }

        override fun test03() { "BikeHelp3" .logd() }

        override fun test04() { "BikeHelp4" .logd() }

        override fun test05() { "BikeHelp5" .logd() }
    }

    class ClassBikeListener (val i: BikeHelp) : BikeListener by i {
        override fun test05() {
            reusltTest05?.let { it("test05") }
        }

        companion object{
            lateinit var mClassBikeListener:ClassBikeListener
            fun getInstance(b:BikeHelp):ClassBikeListener{
                    mClassBikeListener = ClassBikeListener(b)
                return mClassBikeListener
            }
        }

        var reusltTest05: ((String) -> Unit?)? = null

        fun reusltTest05Listener(block: (String) -> Unit){
            reusltTest05 = block
        }
    }

    fun ktTest.ClassBikeListener.ssss(){
        this.toString()
    }


}
fun Any.logd(msg:String = "") = println("$msg  $this")

fun SharedPreferences.trustOpen(block:SharedPreferences.Editor.()->Unit){
    val edit = edit()
    edit.block()
    edit.apply()
}

fun <T> T.build(block:T.() -> Unit):T{
    block()
    return this
}


    fun Any.logp(msg:String = ""){
        System.out.println("$msg ${this}")
    }
