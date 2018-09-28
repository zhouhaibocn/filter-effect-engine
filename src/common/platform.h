//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_PLATFORM_H
#define FILTERENGINE_PLATFORM_H

#define DEBUG_FLAG 1
#define INFO_FLAG  1

#define OPENGL_ES 1

// 调试信息
#ifdef __APPLE__
#define LOGD(...)  if (DEBUG_FLAG) \
{printf("[DEBUG] FILE: %s, LINE: %d", __FILE__, __LINE__);printf(__VA_ARGS__);printf("\n");}     // 定义LOGD
#define LOGI(...)  if (INFO_FLAG) \
{printf("[INFO] FILE: %s, LINE: %d", __FILE__, __LINE__);printf(__VA_ARGS__);printf("\n");}      // 定义LOGI
#define LOGE(...)  if (true) \
{printf("[ERROR] FILE: %s, LINE: %d", __FILE__, __LINE__);printf(__VA_ARGS__);printf("\n");}     // 定义LOGE
#elif __ANDROID__
#include <android/log.h>
#define LOGD(...)  if (DEBUG_FLAG) \
__android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "FILE: %s, LINE: %d", __FILE__, __LINE__, ##__VA_ARGS__)    // 定义LOGD
#define LOGI(...)  if (INFO_FLAG) \
__android_log_print(ANDROID_LOG_INFO, "INFO", "FILE: %s, LINE: %d", __FILE__, __LINE__, ##__VA_ARGS__)     // 定义LOGI
#define LOGE(...)  if (true) \
__android_log_print(ANDROID_LOG_ERROR, "ERROR", __VA_ARGS__)    // 定义LOGE

#endif

//__android_log_print(ANDROID_LOG_ERROR, "ERROR", "FILE: %s, LINE: %d", __FILE__, __LINE__, ##__VA_ARGS__)    // 定义LOGE

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
