LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jni
LOCAL_SRC_FILES := Store.cpp
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)