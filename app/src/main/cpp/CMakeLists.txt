cmake_minimum_required(VERSION 3.10.2)

aux_source_directory(. SOURCE)
add_library(
        native-lib
        SHARED
        ${SOURCE})

find_library(
        log-lib
        log)

include_directories(include)

set(libs ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${libs}")

target_link_libraries(
        native-lib
        avfilter avformat avcodec avutil swresample swscale
        ${log-lib}
        z
        OpenSLES
        android
        ${log-lib})