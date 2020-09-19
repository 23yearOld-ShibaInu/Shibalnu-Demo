package com.trust.shibalnucpp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    private val jniTest = JniTest()
    private val TAG = "LiHao"
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }


    fun test1(view: View) {
        val intArrayOf = intArrayOf(1, 2, 3, 4, 5, 6)
        jniTest.addTest01(1995,"Trust",intArrayOf , arrayOf("Trust","李豪","欢屁"))

        intArrayOf.forEach {
            Log.d(TAG," JAVA test1  intArrayOf: $it")
        }
    }

    fun putStudent(view: View) {
        val student = Student("李豪",11);
        jniTest.putStudent(student)
    }

    fun ndk9(view: View) {
        jniTest.ndk9()
    }

    fun testDog(view: View) {
        jniTest.testDog()
    }

    fun testUnbindDog(view: View) { jniTest.testUnBindDog() }

}
