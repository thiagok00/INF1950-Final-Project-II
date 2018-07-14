LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE:= libboost_chrono
LOCAL_MODULE_FILENAME := boost
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libboost_chrono-gcc-mt-1_63.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libboost_date_time
LOCAL_MODULE_FILENAME := boost
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libboost_date_time-gcc-mt-1_63.a 
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libboost_regex
LOCAL_MODULE_FILENAME := boost
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libboost_regex-gcc-mt-1_63.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libboost_system
LOCAL_MODULE_FILENAME := boost
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libboost_system-gcc-mt-1_63.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libboost_thread
LOCAL_MODULE_FILENAME := boost
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libboost_thread-gcc-mt-1_63.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)