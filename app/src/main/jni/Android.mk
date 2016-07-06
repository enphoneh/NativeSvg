LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libskia
LOCAL_SRC_FILES := libskia.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libbase
LOCAL_SRC_FILES := libbase.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE :=NativeSvg
LOCAL_LDLIBS:= -llog
LOCAL_SRC_FILES :=com_aven_nativesvg_NativeSvgUtils.cpp
include $(BUILD_SHARED_LIBRARY)