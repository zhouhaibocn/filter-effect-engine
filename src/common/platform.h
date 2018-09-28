//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_PLATFORM_H
#define FILTERENGINE_PLATFORM_H

#define DEBUG_FLAG true
#define INFO_FLAG  true

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

// 调试信息
#ifdef __APPLE__
#define LOGD(...)  if (DEBUG_FLAG) \
{printf("[DEBUG] FILE: %s, LINE: %d", __FILENAME__, __LINE__);printf(__VA_ARGS__);printf("\n");}     // 定义LOGD
#define LOGI(...)  if (INFO_FLAG) \
{printf("[INFO] FILE: %s, LINE: %d", __FILENAME__, __LINE__);printf(__VA_ARGS__);printf("\n");}      // 定义LOGI
#define LOGE(...)  if (true) \
{printf("[ERROR] FILE: %s, LINE: %d", __FILENAME__, __LINE__);printf(__VA_ARGS__);printf("\n");}     // 定义LOGE
#elif __ANDROID__
#include <android/log.h>

// 定义LOGD
#if DEBUG_FLAG
#define LOGD(LOG_TAG, fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "[%s, %d]: "fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)
#else
#define LOGD(LOG_TAG, fmt, ...)
#endif

// 定义LOGI
#if INFO_FLAG
#define LOGI(LOG_TAG, fmt, ...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[%s, %d]: "fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)
#else
LOGI(LOG_TAG, fmt, ...)
#endif

// 定义LOGE
#define LOGE(LOG_TAG, fmt, ...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s, %d]: "fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)

#endif

// OpenGL ES 头文件
#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES3/gl.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#endif

#endif //FILTERENGINE_PLATFORM_H
