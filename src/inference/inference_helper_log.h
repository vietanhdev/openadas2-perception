#ifndef INFERENCE_HELPER_LOG_
#define INFERENCE_HELPER_LOG_


#include <cstdint>
#include <cmath>
#include <string>
#include <vector>
#include <array>


#if defined(ANDROID) || defined(__ANDROID__)
#define CV_COLOR_IS_RGB
#include <android/log.h>
#define INFERENCE_HELPER_LOG_NDK_TAG "MyApp_NDK"
#define INFERENCE_HELPER_LOG_PRINT_(...) __android_log_print(ANDROID_LOG_INFO, INFERENCE_HELPER_LOG_NDK_TAG, __VA_ARGS__)
#else
#define INFERENCE_HELPER_LOG_PRINT_(...) printf(__VA_ARGS__)
#endif

#define INFERENCE_HELPER_LOG_PRINT(INFERENCE_HELPER_LOG_PRINT_TAG, ...) do { \
    INFERENCE_HELPER_LOG_PRINT_("[" INFERENCE_HELPER_LOG_PRINT_TAG "][%d] ", __LINE__); \
    INFERENCE_HELPER_LOG_PRINT_(__VA_ARGS__); \
} while(0);

#define INFERENCE_HELPER_LOG_PRINT_E(INFERENCE_HELPER_LOG_PRINT_TAG, ...) do { \
    INFERENCE_HELPER_LOG_PRINT_("[ERR: " INFERENCE_HELPER_LOG_PRINT_TAG "][%d] ", __LINE__); \
    INFERENCE_HELPER_LOG_PRINT_(__VA_ARGS__); \
} while(0);

#endif
