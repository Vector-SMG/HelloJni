package com.cornucopia;

import java.util.Date;
import java.util.Random;
import java.util.UUID;

/**
 * jni开发流程demo
 * <p>
 * <p>
 * 1.在java中声明`native`方法.
 * 2.编译java源文件得到class文件，然后通过javah命令导出JNI的头文件。
 * 2.1 javac com/cornucopia/HelloJni
 * 2.2 javah com.cornucopia.HelloJni
 * 3.编写.c或者.cpp文件，实现JNI方法。
 * 4.编译so库，拷贝动态库至java.library.path本地裤搜索目录下，并在Java中调用。
 * 4.1  gcc -dynamiclib -I /Library/Java/JavaVirtualMachines/
 * jdk1.8.0_161.jdk/Contents/Home/include/ test.c -o libhello.jnilib
 *
 * @author cornucopia
 * @version 1.0
 * @since 2019/12/17
 */
public class HelloJni {

    static {
        //设置路径
        //1. System.load("path")，path为绝对路径
        //2. System.loadLibrary("hello"),直接加载库
        //    2.1 System.setProperty("java.library.path","."); 指定路径
        System.load("/Users/ivan/developer/java/java_project/HelloJni" +
                "/src/main/jni/libhello.jnilib");
    }

    public static void main(String[] args) {
        HelloJni helloJni = new HelloJni();
//      HelloJni.accessStaticMethod();
        String result=helloJni.chinesChars("中");
        System.out.println(result);
    }

    //访问非静态方法
    public native void accessMethod();

    //访问静态方法
    public native static void accessStaticMethod();

    //访问构造方法
    public native Date accessConstructor();


    //转码
    public native String chinesChars(String str);

    //生成随机整形数
    int getRandomInt(int max) {
        return new Random().nextInt(max);
    }

    //生成随机UUID
    static String getRandomUUID() {
        return UUID.randomUUID().toString();
    }

}
