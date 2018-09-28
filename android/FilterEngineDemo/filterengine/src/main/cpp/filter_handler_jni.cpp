//
// Created by zhouhaibo on 2017/9/18.
//

#include "filter_handler_jni.h"
#include "filter_handler.h"

// for test
#include <android/bitmap.h>

JNIEXPORT jlong JNICALL Java_com_me_filterengine_FilterHandler_nativeCreateInstance(JNIEnv * env, jobject obj) {
    FilterHandler *handler = new FilterHandler();
    return (jlong)handler;
}

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeInit(JNIEnv * env, jobject obj, jlong instance, jstring fileName) {
    FilterHandler *handler = (FilterHandler*)instance;
    const char *configFileName = env->GetStringUTFChars(fileName, 0);
    handler->init(configFileName);
    env->ReleaseStringUTFChars(fileName, configFileName);
}

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeSetSize(JNIEnv * env, jobject obj, jlong instance, jint width, jint height) {
    FilterHandler *handler = (FilterHandler*)instance;
    handler->setSize(width, height);
}

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeSetBeautyParams(JNIEnv * env, jobject obj, jlong instance, jint type, jfloat intensity) {
    FilterHandler *handler = (FilterHandler*)instance;
    handler->setBeautifyParams(type, intensity);
}

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeSetFilter(JNIEnv * env, jobject obj, jlong instance, jstring filterZip) {
    FilterHandler *handler = (FilterHandler*)instance;
    const char *configFilterPath= env->GetStringUTFChars(filterZip, 0);
    int length = strlen(configFilterPath);
    if (length > 3) {
        handler->setFilter(configFilterPath);
    } else {
        handler->setFilter(NULL);
    }
    env->ReleaseStringUTFChars(filterZip, configFilterPath);
}

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeSetAdjustParams(JNIEnv * env, jobject obj, jlong instance, jint type, jfloat intensity) {
    FilterHandler *handler = (FilterHandler*)instance;
    handler->setAdjustParams(type, intensity);
}

JNIEXPORT jint JNICALL Java_com_me_filterengine_FilterHandler_nativeProcess(JNIEnv * env, jobject obj, jlong instance, jint textureId) {
    FilterHandler *handler = (FilterHandler*)instance;
    return handler->process(textureId);
}

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeDestory(JNIEnv * env, jobject obj, jlong instance) {
    FilterHandler *handler = (FilterHandler*)instance;
    handler->destroy();
    delete handler;
}

JNIEXPORT jobject JNICALL Java_com_me_filterengine_FilterHandler_nativeGetResult(JNIEnv * env, jobject obj, jlong instance) {
    FilterHandler *handler = (FilterHandler*)instance;
    jclass bitmapCls = env->FindClass("android/graphics/Bitmap");

    jmethodID createBitmapFunction = env->GetStaticMethodID(bitmapCls, "createBitmap", "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jstring configName = env->NewStringUTF("ARGB_8888");
    jclass bitmapConfigClass = env->FindClass("android/graphics/Bitmap$Config");
    jmethodID valueOfBitmapConfigFunction = env->GetStaticMethodID(bitmapConfigClass, "valueOf", "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");
    jobject bitmapConfig = env->CallStaticObjectMethod(bitmapConfigClass, valueOfBitmapConfigFunction, configName);
    env->DeleteLocalRef(configName);

    int width = 0;
    int height = 0;
    handler->getIameSize(&width, &height);
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    jobject newBitmap = env->CallStaticObjectMethod(bitmapCls, createBitmapFunction, width, height, bitmapConfig);

    unsigned char* row;

    int ret = AndroidBitmap_lockPixels(env, newBitmap, (void**) &row);

    if (ret < 0) {
        return NULL;
    }

    handler->getResult(row);
    AndroidBitmap_unlockPixels(env, newBitmap);

    return newBitmap;
}


