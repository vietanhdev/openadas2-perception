cmake_minimum_required(VERSION 3.0)

# Create project
set(ProjectName "openadas2_perception")
project(${ProjectName})

# Select build system and set compile options
include(${CMAKE_CURRENT_LIST_DIR}/src/cmakes/build_setting.cmake)

# Create executable file
add_executable(demo src/demo.cpp)

# Link engine module
add_subdirectory(./src src)
target_include_directories(demo PUBLIC ./src ./src/common)
target_link_libraries(demo openadas2_perception_engine)

# For OpenCV
find_package(OpenCV REQUIRED)
target_include_directories(demo PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(demo ${OpenCV_LIBS})

# Copy resouce
file(COPY ${CMAKE_CURRENT_LIST_DIR}/data/models DESTINATION ${CMAKE_BINARY_DIR}/)
add_definitions(-DRESOURCE_DIR="${CMAKE_BINARY_DIR}/models/")

