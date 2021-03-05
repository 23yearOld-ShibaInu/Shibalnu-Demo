package com.shibalnu.shibalnumk

import android.os.Bundle
import android.webkit.WebSettings
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*


class MainActivity : AppCompatActivity() {



    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        show_tv.text = "${test().num}"

        test_webv.loadUrl("https://www.baidu.com/");
//        test_webv.loadUrl("www.baidu.com")
//声明WebSettings子类
        //声明WebSettings子类
        val webSettings: WebSettings = test_webv.getSettings()

//如果访问的页面中要与Javascript交互，则webview必须设置支持Javascript

//如果访问的页面中要与Javascript交互，则webview必须设置支持Javascript
        webSettings.javaScriptEnabled = true
// 若加载的 html 里有JS 在执行动画等操作，会造成资源浪费（CPU、电量）
// 在 onStop 和 onResume 里分别把 setJavaScriptEnabled() 给设置成 false 和 true 即可

//支持插件
// 若加载的 html 里有JS 在执行动画等操作，会造成资源浪费（CPU、电量）
// 在 onStop 和 onResume 里分别把 setJavaScriptEnabled() 给设置成 false 和 true 即可

//支持插件
//        webSettings.setPluginsEnabled(true)

//设置自适应屏幕，两者合用

//设置自适应屏幕，两者合用
        webSettings.useWideViewPort = true //将图片调整到适合webview的大小

        webSettings.loadWithOverviewMode = true // 缩放至屏幕的大小


//缩放操作

//缩放操作
        webSettings.setSupportZoom(true) //支持缩放，默认为true。是下面那个的前提。

        webSettings.builtInZoomControls = true //设置内置的缩放控件。若为false，则该WebView不可缩放

        webSettings.displayZoomControls = false //隐藏原生的缩放控件


//其他细节操作

//其他细节操作
        webSettings.cacheMode = WebSettings.LOAD_CACHE_ELSE_NETWORK //关闭webview中缓存

        webSettings.allowFileAccess = true //设置可以访问文件

        webSettings.javaScriptCanOpenWindowsAutomatically = true //支持通过JS打开新窗口

        webSettings.loadsImagesAutomatically = true //支持自动加载图片

        webSettings.defaultTextEncodingName = "utf-8" //设置编码格式

    }


}
