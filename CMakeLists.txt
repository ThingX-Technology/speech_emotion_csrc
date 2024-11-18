# CMakeList.txt: thingx_emotion_recognition 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("thingx_emotion_recognition")

# 设置C++标准
set(CMAKE_CXX_STANDARD 20) # 新增：设置C++ 20标准

# 设置ONNX Runtime路径 - 这里替换为你解压的实际路径
set(ONNXRUNTIME_DIR "C:/Users/edith/software/onnxruntime-win-x64-1.20.0") # 新增：设置ONNX Runtime库的路径
set(LIBROSA_DIR "C:/Users/edith/dl_workplace/thingx_emotion_recognition/librosa") # 新增：设置ONNX Runtime库的路径
set(AUBIO_SOURCE_DIR "C:/Users/edith/software/aubio-0.4.6-win64")

# 添加ONNX Runtime头文件路径
include_directories(${ONNXRUNTIME_DIR}/include) # 新增：包含ONNX Runtime的头文件路径
# 添加 aubio 的 include 路径
include_directories(${AUBIO_SOURCE_DIR}/include)
include_directories(${LIBROSA_DIR})
link_directories(${AUBIO_SOURCE_DIR}/lib)


# 将源代码添加到此项目的可执行文件。
add_executable (thingx_emotion_recognition 
    "src/thingx_emotion_recognition.cpp" 
    "include/thingx_emotion_recognition.h" 
    "jni/AudioUtilsJNI.cpp" 

 "src/test_aubio.cpp")

# 链接ONNX Runtime库
target_link_libraries(thingx_emotion_recognition "${ONNXRUNTIME_DIR}/lib/onnxruntime.lib") # 新增：链接ONNX Runtime库文件
# 链接动态库
target_link_libraries(thingx_emotion_recognition "${AUBIO_SOURCE_DIR}/lib/libaubio-5.lib")


include_directories(include)
target_sources(thingx_emotion_recognition PRIVATE include/json.hpp)
#target_sources(thingx_emotion_recognition PRIVATE json.hpp)


# 设置生成的可执行文件路径
set_target_properties(thingx_emotion_recognition PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") # 新增：设置可执行文件的输出路径

# 复制ONNX Runtime动态库到输出目录
add_custom_command(TARGET thingx_emotion_recognition POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ONNXRUNTIME_DIR}/lib/onnxruntime.dll"
        $<TARGET_FILE_DIR:thingx_emotion_recognition>) # 新增：将onnxruntime.dll复制到可执行文件目录下


# 复制动态库到运行目录
add_custom_command(TARGET thingx_emotion_recognition POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${AUBIO_SOURCE_DIR}/bin/libaubio-5.dll"  # 动态库路径
        $<TARGET_FILE_DIR:thingx_emotion_recognition>)       # 目标文件目录

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET thingx_emotion_recognition PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
