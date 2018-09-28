//
// Created by zhouhaibo on 2017/9/18.
//

#ifndef FILTERENGINE_FILTER_HANDLER_JNI_H
#define FILTERENGINE_FILTER_HANDLER_JNI_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_me_filterengine_FilterHandler_nativeCreateInstance(JNIEnv * env, jobject obj);

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeInit(JNIEnv * env, jobject obj, jlong instance, jstring fileName);

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeSetSize(JNIEnv * env, jobject obj, jlong instance, jint width, jint height);

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeSetBeautyParams(JNIEnv * env, jobject obj, jlong instance, jint type, jfloat intensity);

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeSetAdjustParams(JNIEnv * env, jobject obj, jlong instance, jint type, jfloat intensity);

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeSetFilter(JNIEnv * env, jobject obj, jlong instance, jstring filterZip);

JNIEXPORT jint JNICALL Java_com_me_filterengine_FilterHandler_nativeProcess(JNIEnv * env, jobject obj, jlong instance, jint textureId);

JNIEXPORT void JNICALL Java_com_me_filterengine_FilterHandler_nativeDestory(JNIEnv * env, jobject obj, jlong instance);


JNIEXPORT jobject JNICALL Java_com_me_filterengine_FilterHandler_nativeGetResult(JNIEnv * env, jobject obj, jlong instance);

#ifdef __cplusplus
}
#endif


#endif //FILTERENGINE_FILTER_HANDLER_JNI_H
