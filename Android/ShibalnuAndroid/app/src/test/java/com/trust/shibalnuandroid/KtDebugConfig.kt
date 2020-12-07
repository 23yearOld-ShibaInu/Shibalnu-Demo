package com.trust.shibalnuandroid

class Dependency{
    val list = ArrayList<String>()

    fun implementation(lib:String){
        list.add(lib)
    }
}

fun dependencies(block:Dependency.() -> Unit):List<String>{
    val dependency = Dependency()
    dependency.block()
    return dependency.list
}


fun Any.BsLogd(msg:String = "") = println("$msg | $this")




