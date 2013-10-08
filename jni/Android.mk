LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog

LOCAL_MODULE    := snowRenderer
LOCAL_SRC_FILES := JNIWrapper.c snowRenderer.c

include $(BUILD_SHARED_LIBRARY)