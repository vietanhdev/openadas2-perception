# HybridNets with TensorFlow Lite / ONNX Runtime in C++

MacOS:

- Install bazel 5.3.0: https://bazel.build/install/os-x
- Build TensorLite with bazel: https://www.tensorflow.org/lite/guide/build_arm

For mac m1:
```
bazel build --cpu=darwin_arm64 --macos_minimum_os=13.0 -c opt //tensorflow/lite:libtensorflowlite.dylib
```

See configs: https://github.com/tensorflow/tensorflow/blob/master/.bazelrc