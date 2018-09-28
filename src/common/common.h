//
// Created by zhouhaibo on 2017/7/23.
//

#ifndef FILTERENGINE_COMMON_H
#define FILTERENGINE_COMMON_H

#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <queue>
#include <string>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <cwchar>

#include "platform.h"

#define GLES_ATTACH_STRING_L "#ifdef OPENGL_ES\nprecision lowp float;\n#endif\n"
#define GLES_ATTACH_STRING_M "#ifdef OPENGL_ES\nprecision mediump float;\n#endif\n"
#define GLES_ATTACH_STRING_H "#ifdef OPENGL_ES\nprecision highp float;\n#endif\n"

#define GLES_SHADER_STRING(...)  #__VA_ARGS__
#define GLES_SHADER_STRING_PRECISION_L(...) GLES_ATTACH_STRING_L  #__VA_ARGS__
#define GLES_SHADER_STRING_PRECISION_M(...) GLES_ATTACH_STRING_M  #__VA_ARGS__
#define GLES_SHADER_STRING_PRECISION_H(...) GLES_ATTACH_STRING_H  #__VA_ARGS__

typedef const char* ConstString;


#endif //FILTERENGINE_COMMON_H
