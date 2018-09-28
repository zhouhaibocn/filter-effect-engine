# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# FilterEngine src源代码
set(FILTER_ENGINE_SRC_DIR ${CMAKE_SOURCE_DIR}/../../../src/)
set(FILTER_ENGINE_INC_DIR ${CMAKE_SOURCE_DIR}/../../../src/)

# JNI 源码
set(FILTER_ENGINE_JNI_SRC_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp/)


# 编译源码
add_library( filter_engine
             SHARED

             # Provides a relative path to your source file(s).
             # common
             ${FILTER_ENGINE_SRC_DIR}/common/common.h
             ${FILTER_ENGINE_SRC_DIR}/common/filter_interface.cpp

             # decoder
             ${FILTER_ENGINE_SRC_DIR}/decoder/picture_decoder.cpp

             # utils
             ${FILTER_ENGINE_SRC_DIR}/utils/common_utils.cpp
             ${FILTER_ENGINE_SRC_DIR}/utils/gl_utils.cpp
             ${FILTER_ENGINE_SRC_DIR}/utils/default_drawer.cpp
             ${FILTER_ENGINE_SRC_DIR}/utils/parse_config.cpp

             # beautify
             ${FILTER_ENGINE_SRC_DIR}/beautify/beautify_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/beautify/beautify_manager.cpp

             # filter adjust
             ${FILTER_ENGINE_SRC_DIR}/filter/adjust/adjust_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/adjust/adjust_filter_manager.cpp

             # filter base
             ${FILTER_ENGINE_SRC_DIR}/filter/base/multi_input_filter.cpp

             # filter normal
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/whitecat_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/antique_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/blackcat_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/cool_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/romance_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/latte_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/sakura_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/emerald_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/evergreen_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/crayon_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/sketch_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/nostalgia_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/healthy_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/sweets_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/tender_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/calm_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/warm_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/sunset_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/sunrise_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/normal/lookup_filter.cpp

             # filter advanced
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/amaro_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/brannan_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/earlybird_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/hefe_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/hudson_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/I1977_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/inkwell_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/lomo_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/lordkelvin_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/nashville_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/rise_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/sierra_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/sutro_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/toaster_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/valencia_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/walden_filter.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/advanced/xproll_filter.cpp

             # filter
             ${FILTER_ENGINE_SRC_DIR}/filter/filter_manager.cpp
             ${FILTER_ENGINE_SRC_DIR}/filter/filter_factory.cpp

             # filter handler
             ${FILTER_ENGINE_SRC_DIR}/filter_handler.cpp
             ${FILTER_ENGINE_JNI_SRC_DIR}/filter_handler_jni.cpp
             )

# 第三方FFmpeg库目录
set(FFMPEG_LIB_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
set(FFMPEG_INC_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/include)

# FFmpeg库 libijkffmpeg.so
find_library(ijkffmpeg-lib ijkffmpeg PATHS ${FFMPEG_LIB_DIR}/ NO_CMAKE_FIND_ROOT_PATH)


# 头文件
include_directories(
    ${FILTER_ENGINE_INC_DIR}
    ${FFMPEG_INC_DIR}
    ${FFMPEG_INC_DIR}/libffmpeg
)

target_link_libraries( filter_engine

                       ${ijkffmpeg-lib}
                       jnigraphics
                       GLESv2
                       GLESv3
                       log
                       EGL
                       android
                       z
                       OpenSLES
                       mediandk
                       )