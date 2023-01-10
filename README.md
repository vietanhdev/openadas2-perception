# OpenADAS2 Perception

## Build and run (mac M1 arm64):

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

- Download models and data from [data.zip](https://1drv.ms/u/s!Av71xxzl6mYZgsov4IpTQdjqn4x7ZQ?e=f1SoFU) and extract to `data` folder.

- Run the demo:

```
cd build
./demo ../data/video.mp4
```