# OpenADAS2 Perception

## MacOS:

- Install bazel 5.3.0: https://bazel.build/install/os-x
- Build TensorLite with bazel: https://www.tensorflow.org/lite/guide/build_arm

For mac m1:
```
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