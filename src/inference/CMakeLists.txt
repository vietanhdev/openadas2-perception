cmake_minimum_required(VERSION 3.0)

set(LibraryName "InferenceHelper")
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/../third_party/)

set(INFERENCE_HELPER_ENABLE_PRE_PROCESS_BY_OPENCV OFF CACHE BOOL "Enable preprocess by OpenCV? [ON/OFF]")
set(INFERENCE_HELPER_ENABLE_TFLITE ON CACHE BOOL "With TFLite? [ON/OFF]")
set(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_XNNPACK ON CACHE BOOL "With TFLite Delegate XNNPACK? [ON/OFF]")
set(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_GPU ON CACHE BOOL "With TFLite Delegate GPU? [ON/OFF]")

# Create library
set(SRC inference_helper.h inference_helper.cpp inference_helper_log.h inference_helper_tensorflow_lite.cpp inference_helper_tensorflow_lite.h)

add_library(${LibraryName} ${SRC})

include_directories(thirdparty/tensorflow thirdparty/flatbuffers)
target_link_libraries(${LibraryName} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/thirdparty/tensorflow/bazel-bin/tensorflow/lite/libtensorflowlite.dylib")


# For Tensorflow Lite
if(INFERENCE_HELPER_ENABLE_TFLITE OR INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_XNNPACK OR INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_GPU OR INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_EDGETPU OR INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_NNAPI)
    add_definitions(-DINFERENCE_HELPER_ENABLE_TFLITE)
endif()

# For Tensorflow Lite Delegate(XNNPACK)
if(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_XNNPACK)
    add_definitions(-DINFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_XNNPACK)
endif()

# For Tensorflow Lite Delegate(GPU)
if(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_GPU)
    find_package(OpenCL)
    if(OpenCL_Found)
        target_include_directories(${LibraryName} PUBLIC ${OpenCL_INCLUDE_DIRS})
        target_link_libraries(${LibraryName} PRIVATE ${OpenCL_LIBRARIES})
    endif()
    target_include_directories(${LibraryName} PUBLIC ${TFLITE_GPU_INC})
    target_link_libraries(${LibraryName} PRIVATE ${TFLITE_GPU_LIB})
    add_definitions(-DINFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_GPU)
endif()

