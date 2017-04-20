/**
 * This is a stub loaded when on x86. Torch isn't supported on x86 devices, but that's a matter for
 * Java to handle.
 *
 * @author Pär Amsen 04/2017
 */

#include <jni.h>
#include <stdio.h>
#include "Log.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_paramsen_torchtemple_torch_JNIBridge_nSetup(JNIEnv *env, jobject jThis, jobject jAssetManager, jstring jNativeLibraryDir, jstring jPath) {
    lW("Torch cannot be initialized on x86");
}

JNIEXPORT float JNICALL
Java_com_paramsen_torchtemple_torch_JNIBridge_nCall(JNIEnv *env, jobject jThis, jfloatArray data) {
    lW("Torch cannot be initialized on x86");
    return INT16_MIN;
}

JNIEXPORT void JNICALL
Java_com_paramsen_torchtemple_torch_JNIBridge_nDispose(JNIEnv *env, jobject jThis) {
    lW("Torch cannot be initialized on x86");
}

#ifdef __cplusplus
}
#endif