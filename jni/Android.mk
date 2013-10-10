LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -lGLESv1_CM -ldl -L$(SYSROOT)/usr/lib -llog

LOCAL_MODULE    := snowRenderer
LOCAL_SRC_FILES := JNIWrapper.cpp SnowRenderer.cpp

include $(BUILD_SHARED_LIBRARY)