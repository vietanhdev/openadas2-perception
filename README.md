# OpenADAS2 Perception

## I. Build and run

- Download models and data from [data.zip](https://1drv.ms/u/s!Av71xxzl6mYZgsov4IpTQdjqn4x7ZQ?e=f1SoFU) and extract to `data` folder.

### Mac (Apple Silicon)

- Install Bazel 5.3.0: https://bazel.build/install/os-x
- Build TensorLite with bazel: https://www.tensorflow.org/lite/guide/build_arm

```
cd src/inference/thirdparty/tensorflow
bazel build --cpu=darwin_arm64 --macos_minimum_os=13.0  --define tflite_with_xnnpack=true -c opt //tensorflow/lite:libtensorflowlite.dylib
```

See configs: https://github.com/tensorflow/tensorflow/blob/master/.bazelrc

- Build the project:

```
mkdir build
cd build
cmake .. -DCMAKE_HOST_SYSTEM_PROCESSOR=arm64 -DBUILD_SYSTEM=arm64
make
```

- Update cpuinfo CMAKE (`build/cpuinfo/CMakeLists.txt`) from the second build:

From:
```
IF(NOT DEFINED CLOG_SOURCE_DIR)
  SET(CLOG_SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/clog")
ENDIF()
```

To:
```
SET(CLOG_SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/clog")
```

- Run the demo:

```
cd build
./demo ../data/video.mp4
```

### Windows

- Use Git Bash for Terminal
- Install Visual Studio 2022
- Install Chocolatey: <https://chocolatey.org/install>
- Install CMake and OpenCV:

```
choco install cmake
choco install opencv
```

- Build the project:

```
mkdir build
cd build
OPENCV_DIR=C:\\tools\\opencv\\build cmake ..
cmake --build . --config Release
```

- Run the demo:

```
cd build
./demo.exe ../data/video.mp4
```