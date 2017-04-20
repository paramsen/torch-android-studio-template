/**
 * Defs for logging to Android logcat
 *
 * @author Pär Amsen 04/2017
 */

#ifndef TORCH_ANDROID_STUDIO_TEMPLATE_LOG_H
#define TORCH_ANDROID_STUDIO_TEMPLATE_LOG_H

#include <android/log.h>

#define TAG "Native"
#define  lD(args...)  __android_log_print(ANDROID_LOG_DEBUG, TAG, args)
#define  lW(args...)  __android_log_print(ANDROID_LOG_WARN, TAG, args)
#define  lE(args...)  __android_log_print(ANDROID_LOG_ERROR, TAG, args)

#endif //TORCH_ANDROID_STUDIO_TEMPLATE_LOG_H
