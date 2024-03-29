cmake_minimum_required(VERSION 3.0)

set(LibraryName openadas2_perception_engine)

# Create library
add_library (${LibraryName} image_processor.cpp image_processor.h detection_engine.cpp detection_engine.h prior_bbox.cpp prior_bbox.h)

# For OpenCV
find_package(OpenCV REQUIRED)
target_include_directories(${LibraryName} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${LibraryName} ${OpenCV_LIBS})

# Link Common Helper module
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/common common)
target_include_directories(${LibraryName} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/common)
target_link_libraries(${LibraryName} CommonHelper)

# For InferenceHelper
set(INFERENCE_HELPER_DIR ${CMAKE_CURRENT_LIST_DIR}/inference)
add_subdirectory(${INFERENCE_HELPER_DIR} inference_helper)
target_include_directories(${LibraryName} PUBLIC ${INFERENCE_HELPER_DIR})
target_link_libraries(${LibraryName} InferenceHelper)

if (NOT DEFINED ENV{ANDROID_NDK})
    target_link_libraries(${LibraryName} OpenMP::OpenMP_CXX)
endif()



