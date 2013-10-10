#include <android/log.h>

#define LOGD(TAG, MESSAGE) __android_log_write(ANDROID_LOG_INFO, TAG, MESSAGE)
