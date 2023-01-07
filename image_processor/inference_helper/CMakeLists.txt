cmake_minimum_required(VERSION 3.0)

set(LibraryName "InferenceHelper")
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/../third_party/)

set(INFERENCE_HELPER_ENABLE_PRE_PROCESS_BY_OPENCV off CACHE BOOL "Enable PreProcess by OpenCV? [on/off]")
set(INFERENCE_HELPER_ENABLE_TFLITE off CACHE BOOL "With Tflite? [on/off]")
set(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_XNNPACK off CACHE BOOL "With Tflite Delegate XNNPACK? [on/off]")
set(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_GPU off CACHE BOOL "With Tflite Delegate GPU? [on/off]")
set(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_EDGETPU off CACHE BOOL "With Tflite Delegate EdgeTPU? [on/off]")
set(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_NNAPI off CACHE BOOL "With Tflite Delegate NNAPI? [on/off]")

# Create library
set(SRC inference_helper.h inference_helper.cpp inference_helper_log.h)

add_library(${LibraryName} ${SRC})

# set(TENSORFLOW_SOURCE_DIR "thirdparty/tensorflow" CACHE PATH
#   "Directory that contains the TensorFlow project" )
# if(NOT TENSORFLOW_SOURCE_DIR)
#   get_filename_component(TENSORFLOW_SOURCE_DIR
#     "${CMAKE_CURRENT_LIST_DIR}/../../../../" ABSOLUTE)
# endif()

# add_subdirectory(
#   "${TENSORFLOW_SOURCE_DIR}/tensorflow/lite"
#   "${CMAKE_CURRENT_BINARY_DIR}/tensorflow-lite" EXCLUDE_FROM_ALL)

include_directories(thirdparty/tensorflow/tensorflow)
target_link_libraries(${LibraryName} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/thirdparty/tensorflow/bazel-bin/tensorflow/lite/libtensorflowlite.dylib")


# # For TensorInfo (Pre process calculation)
# if(INFERENCE_HELPER_ENABLE_PRE_PROCESS_BY_OPENCV)
#     find_package(OpenCV REQUIRED)
#     target_include_directories(${LibraryName} PUBLIC ${OpenCV_INCLUDE_DIRS})
#     target_link_libraries(${LibraryName} PRIVATE ${OpenCV_LIBS})
#     add_definitions(-DINFERENCE_HELPER_ENABLE_PRE_PROCESS_BY_OPENCV)
# endif()

# # For OpenCV
# if(INFERENCE_HELPER_ENABLE_OPENCV)
#     find_package(OpenCV REQUIRED)
#     target_include_directories(${LibraryName} PUBLIC ${OpenCV_INCLUDE_DIRS})
#     target_link_libraries(${LibraryName} PRIVATE ${OpenCV_LIBS})
#     add_definitions(-DINFERENCE_HELPER_ENABLE_OPENCV)
# endif()

# # For Tensorflow Lite
# if(INFERENCE_HELPER_ENABLE_TFLITE OR INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_XNNPACK OR INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_GPU OR INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_EDGETPU OR INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_NNAPI)
#     include(${THIRD_PARTY_DIR}/cmakes/tflite.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${TFLITE_INC})
#     target_link_libraries(${LibraryName} PRIVATE ${TFLITE_LIB})
#     add_definitions(-DINFERENCE_HELPER_ENABLE_TFLITE)
# endif()

# # For Tensorflow Lite Delegate(XNNPACK)
# if(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_XNNPACK)
#     add_definitions(-DINFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_XNNPACK)
# endif()

# # For Tensorflow Lite Delegate(GPU)
# if(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_GPU)
#     find_package(OpenCL)
#     if(OpenCL_Found)
#         target_include_directories(${LibraryName} PUBLIC ${OpenCL_INCLUDE_DIRS})
#         target_link_libraries(${LibraryName} PRIVATE ${OpenCL_LIBRARIES})
#     endif()
#     include(${THIRD_PARTY_DIR}/cmakes/tflite_gpu.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${TFLITE_GPU_INC})
#     target_link_libraries(${LibraryName} PRIVATE ${TFLITE_GPU_LIB} EGL GLESv2)
#     add_definitions(-DINFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_GPU)
# endif()

# # For Tensorflow Lite Delegate(Edge TPU)
# if(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_EDGETPU)
#     include(${THIRD_PARTY_DIR}/cmakes/tflite_edgetpu.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${TFLITE_EDGETPU_INC})
#     target_link_libraries(${LibraryName} PRIVATE ${TFLITE_EDGETPU_LIB})
#     add_definitions(-DINFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_EDGETPU)
# endif()

# # For Tensorflow Lite Delegate(NNAPI)
# if(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_NNAPI)
#     add_definitions(-DINFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_NNAPI)
# endif()


# # For TensorRT
# if(INFERENCE_HELPER_ENABLE_TENSORRT)
#     find_package(CUDA)
#     if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13.0") 
#         if(MSVC_VERSION)
#             # note: the following lines for my environment (Windows 10/11. cuDNN is copied into CUDA install path)
#             # Copy TensorRT into CUDA install path
#             # or, Set environment variable(TensorRT_ROOT = C:\Program Files\NVIDIA GPU Computing Toolkit\TensorRT\TensorRT-8.2.0.6), and add %TensorRT_ROOT%\lib to path
#             target_link_directories(${LibraryName} PUBLIC ${CUDA_TOOLKIT_ROOT_DIR}/bin)
#             target_link_directories(${LibraryName} PUBLIC ${CUDA_TOOLKIT_ROOT_DIR}/lib/x64)
#         else()
#             target_link_directories(${LibraryName} PUBLIC /usr/local/cuda/lib64)
#         endif()
#     endif()
#     if(CUDA_FOUND)
#         if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13.0") 
#             if(NOT $ENV{TensorRT_ROOT} STREQUAL "")
#                 target_link_directories(${LibraryName} PUBLIC $ENV{TensorRT_ROOT}/lib)
#             endif()
#         endif()
#         target_link_libraries(${LibraryName} PRIVATE
#             ${CUDA_LIBRARIES}
#             nvinfer
#             nvonnxparser
#             nvinfer_plugin
#             cudnn
#         )
#         target_include_directories(${LibraryName} PUBLIC
#             ${CUDA_INCLUDE_DIRS}
#             tensorrt
#         )
#         if(NOT $ENV{TensorRT_ROOT} STREQUAL "")
#             target_include_directories(${LibraryName} PUBLIC $ENV{TensorRT_ROOT}/include)
#         endif()
#         add_definitions(-DINFERENCE_HELPER_ENABLE_TENSORRT)
#         message("CUDA_INCLUDE_DIRS: ${CUDA_INCLUDE_DIRS}")
#     else()
#         message(WARNING, "Cannot find CUDA")
#     endif()
# endif()

# # For NCNN
# if(INFERENCE_HELPER_ENABLE_NCNN)
#     include(${THIRD_PARTY_DIR}/cmakes/ncnn.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${NCNN_INC})
#     target_link_libraries(${LibraryName} PRIVATE ${NCNN_LIB})
#     add_definitions(-DINFERENCE_HELPER_ENABLE_NCNN)
# endif()

# # For MNN
# if(INFERENCE_HELPER_ENABLE_MNN)
#     include(${THIRD_PARTY_DIR}/cmakes/mnn.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${MNN_INC})
#     target_link_libraries(${LibraryName} PRIVATE ${MNN_LIB})
#     add_definitions(-DINFERENCE_HELPER_ENABLE_MNN)
# endif()

# # For SNPE
# if(INFERENCE_HELPER_ENABLE_SNPE)
#     include(${THIRD_PARTY_DIR}/cmakes/snpe.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${SNPE_INC} ./snpe)
#     target_link_libraries(${LibraryName} PRIVATE ${SNPE_LIB})
#     add_definitions(-DINFERENCE_HELPER_ENABLE_SNPE)
# endif()

# # For ARMNN
# if(INFERENCE_HELPER_ENABLE_ARMNN)
#     include(${THIRD_PARTY_DIR}/cmakes/armnn.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${ARMNN_INC})
#     target_link_libraries(${LibraryName} PRIVATE ${ARMNN_LIB})
#     add_definitions(-DINFERENCE_HELPER_ENABLE_ARMNN)
# endif()

# # For NNABLA
# if(INFERENCE_HELPER_ENABLE_NNABLA OR INFERENCE_HELPER_ENABLE_NNABLA_CUDA)
#     include(${THIRD_PARTY_DIR}/cmakes/nnabla.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${NNABLA_INC})
#     target_link_libraries(${LibraryName} PRIVATE ${NNABLA_LIB})
#     if (INFERENCE_HELPER_ENABLE_NNABLA)
#         add_definitions(-DINFERENCE_HELPER_ENABLE_NNABLA)
#     endif()
#     if (INFERENCE_HELPER_ENABLE_NNABLA_CUDA)
#         find_package(CUDA)
#         target_link_libraries(${LibraryName} PRIVATE ${CUDA_LIBRARIES})
#         target_include_directories(${LibraryName} PUBLIC ${CUDA_INCLUDE_DIRS})
#         add_definitions(-DINFERENCE_HELPER_ENABLE_NNABLA_CUDA)
#     endif()
# endif()

# # For ONNX Runtime 
# if(INFERENCE_HELPER_ENABLE_ONNX_RUNTIME OR INFERENCE_HELPER_ENABLE_ONNX_RUNTIME_CUDA)
#     include(${THIRD_PARTY_DIR}/cmakes/onnx_runtime.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${ONNX_RUNTIME_INC})
#     target_link_libraries(${LibraryName} PRIVATE ${ONNX_RUNTIME_LIB})
#     if (INFERENCE_HELPER_ENABLE_ONNX_RUNTIME)
#         add_definitions(-DINFERENCE_HELPER_ENABLE_ONNX_RUNTIME)
#     endif()
#     if (INFERENCE_HELPER_ENABLE_ONNX_RUNTIME_CUDA)
#         # find_package(CUDA)
#         # target_link_libraries(${LibraryName} PRIVATE ${CUDA_LIBRARIES})
#         # target_include_directories(${LibraryName} PUBLIC ${CUDA_INCLUDE_DIRS})
#         add_definitions(-DINFERENCE_HELPER_ENABLE_ONNX_RUNTIME_CUDA)
#     endif()
# endif()

# # For LibTorch
# if(INFERENCE_HELPER_ENABLE_LIBTORCH OR INFERENCE_HELPER_ENABLE_LIBTORCH_CUDA)
#     include(${THIRD_PARTY_DIR}/cmakes/libtorch.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${LIBTORCH_INC})
#     target_link_libraries(${LibraryName} PRIVATE  ${LIBTORCH_LIB})  # Use PRIVATE to avoid `Target "torch_cpu" not found.` error when cmake configure
#     if (INFERENCE_HELPER_ENABLE_LIBTORCH)
#         add_definitions(-DINFERENCE_HELPER_ENABLE_LIBTORCH)
#     endif()
#     if (INFERENCE_HELPER_ENABLE_LIBTORCH_CUDA)
#         # find_package(CUDA)
#         # target_link_libraries(${LibraryName} PRIVATE ${CUDA_LIBRARIES})
#         # target_include_directories(${LibraryName} PUBLIC ${CUDA_INCLUDE_DIRS})
#         add_definitions(-DINFERENCE_HELPER_ENABLE_LIBTORCH_CUDA)
#     endif()
# endif()

# # For TensorFlow
# if(INFERENCE_HELPER_ENABLE_TENSORFLOW OR INFERENCE_HELPER_ENABLE_TENSORFLOW_GPU)
#     include(${THIRD_PARTY_DIR}/cmakes/tensorflow.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${TENSORFLOW_INC})
#     target_link_libraries(${LibraryName} PRIVATE  ${TENSORFLOW_LIB})
#     if (INFERENCE_HELPER_ENABLE_TENSORFLOW)
#         add_definitions(-DINFERENCE_HELPER_ENABLE_TENSORFLOW)
#     endif()
#     if (INFERENCE_HELPER_ENABLE_TENSORFLOW_GPU)
#         # find_package(CUDA)
#         # target_link_libraries(${LibraryName} PRIVATE ${CUDA_LIBRARIES})
#         # target_include_directories(${LibraryName} PUBLIC ${CUDA_INCLUDE_DIRS})
#         add_definitions(-DINFERENCE_HELPER_ENABLE_TENSORFLOW_GPU)
#     endif()
# endif()

# # For Sample (template code to implement a new framework)
# if(INFERENCE_HELPER_ENABLE_SAMPLE)
#     include(${THIRD_PARTY_DIR}/cmakes/sample.cmake)
#     target_include_directories(${LibraryName} PUBLIC ${SAMPLE_INC})
#     target_link_libraries(${LibraryName} PRIVATE ${SAMPLE_LIB})
#     add_definitions(-DINFERENCE_HELPER_ENABLE_SAMPLE)
# endif()
