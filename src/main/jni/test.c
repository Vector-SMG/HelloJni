//test.c
#include "com_cornucopia_HelloJni.h"
#include <stdio.h>


//JNI访问非静态方法
JNIEXPORT void JNICALL Java_com_cornucopia_HelloJni_accessMethod
  (JNIEnv *env, jobject jobj){
    //通过jobject搜索class
    jclass jclz=(*env)->GetObjectClass(env,jobj);
    //获取非静态方法的ID,GetMethodID的参数:方法的名字，方法的签名
    jmethodID mid=(*env)->GetMethodID(env,jclz,"getRandomInt","(I)I");
    //调用非静态方法,CallIntMethod的参数:非静态方法的ID，参数
    jint random=(*env)->CallIntMethod(env,jobj,mid,200);
    printf("C random:%d\n",random);
 }

//JNI访问静态方法
// JNIEXPORT void JNICALL Java_com_cornucopia_HelloJni_accessStaticMethod
//   (JNIEnv *env, jobject jobj){
//    //通过jobject搜索jclass
//    jclass jclz=(*env)->GetObjectClass(env,jobj);
//    //获取静态方法的ID
//    jmethodID jmid=(*env)->GetStaticMethodID(env,jclz,"getRandomUUID","()Ljava/lang/String;");
//    //调用静态方法
//    jstring uuid=(*env)->CallStaticObjectMethod(env,jclz,jmid);
//    //jstring->char*
//    char * uuid_c=(*env)->GetStringUTFChars(env,uuid,NUL);
//    //将字符串写入文件中
//    char filename[100];
//    sprintf(filename,"1.txt",uuid_c);
//    File *fp=fopen(filename,"w");
//    fputs("I Love you",fp);
//    fclose(fp);
//    printf("文件写入成功!!!");
//  }

//访问java构造方法
  JNIEXPORT jobject JNICALL Java_com_cornucopia_HelloJni_accessConstructor
    (JNIEnv *env, jobject jobj){
    //通过类的路径从jvm里面找到对应的类
    jclass jclz=(*env)->FindClass(env,"java/util/Date");
    //得到构造函数
    jmethodID jmid=(*env)->GetMethodID(env,jclz,"<init>","()V");
    //调用newObject实例化Date对象，返回值是一个jobject
    jobject date_obj=(*env)->NewObject(env,jclz,jmid);
    jmethodID time_mid=(*env)->GetMethodID(env,jclz,"getTime","()L");
    jlong time=(*env)->CallLongMethod(env,date_obj,time_mid);
    printf("time:%lld\n",time);
    return date_obj;
}

//转码字符串
JNIEXPORT jstring JNICALL Java_com_cornucopia_HelloJni_chinesChars
  (JNIEnv *env, jobject jobj, jstring in){
//    char *c_str=(*env)->GetStringUTFChars(env,in,NULL);
//    printf("string:%s",c_str);
    char *c_str="刘伟";
    jclass str_cls=(*env)->FindClass(env,"java/lang/String");
    jmethodID jmid=(*env)->GetMethodID(env,str_cls,"<init>","([BLjava/lang/String;)V");
    //jstring -> jbyteArray
    jbyteArray bytes=(*env)->NewByteArray(env,strlen(c_str));
    //将char*赋值给bytes
    (*env)->SetByteArrayRegion(env,bytes,0,strlen(c_str),c_str);
    //调用new String("UTF-8")将数据返回
    jstring charsetName=(*env)->NewStringUTF(env,"utf-8");
    return (*env)->NewObject(env,str_cls,jmid,bytes,charsetName);
}





