/**
 * @author Pär Amsen 04/2017
 */

#include <jni.h>
#include <android/asset_manager_jni.h>
#include <malloc.h>
#include <stdbool.h>
#include <android/asset_manager.h>
#include <string.h>
#include "Torch.h"
#include "Log.h"
#include "Constants.h"

#ifdef __cplusplus
extern "C" {
#endif

Torch *torch;
float *buffer;

bool initialized = false;

JNIEXPORT void JNICALL
Java_com_paramsen_torchtemple_torch_JNIBridge_nSetup(JNIEnv *env, jobject jThis, jobject jAssetManager, jstring jNativeSrcPath, jstring jTorchNetPath) {
    if(!initialized) {
        AAssetManager *assetManager = AAssetManager_fromJava(env, jAssetManager);
        const char *nativeSrcPath = env->GetStringUTFChars(jNativeSrcPath, 0);
        const char *torchNetPath = env->GetStringUTFChars(jTorchNetPath, 0);

        buffer = (float*) malloc(sizeof(float) * INPUT_LENGTH);
        torch = new Torch(assetManager, nativeSrcPath, torchNetPath);
        initialized = true;
    } else {
        lW("Already setup");
    }
}

/**
 * My implementation works on a pre allocated array, so it is not thread safe in any way. Expects
 * the caller to wait for each result before calling again (thread safety is up to you). Right now
 * this method just returns nonsense from the analyzed data since the included .net is empty.
 */
JNIEXPORT jfloat JNICALL
Java_com_paramsen_torchtemple_torch_JNIBridge_nCall(JNIEnv *env, jobject jThis, jfloatArray jData) {
    if(initialized) {
        memcpy(buffer, env->GetFloatArrayElements(jData, 0), INPUT_LENGTH);
        return torch->call(buffer); //a nonsense value from our stub net
    } else {
        lW("Not setup");
        return INT32_MIN;
    }
}

JNIEXPORT void JNICALL
Java_com_paramsen_torchtemple_torch_JNIBridge_nDispose(JNIEnv *env, jobject jThis) {
    if(initialized) {
        delete torch;
        free(buffer);
        initialized = false;
    } else {
        lW("Not setup");
    }
}

#ifdef __cplusplus
}
#endif