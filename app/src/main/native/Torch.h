/**
 * @author Pär Amsen 04/2017
 */

#ifndef TORCH_ANDROID_STUDIO_TEMPLATE_TORCH_H
#define TORCH_ANDROID_STUDIO_TEMPLATE_TORCH_H

#include <android/asset_manager.h>
#include "torchandroid.h"

class Torch {
public:
    Torch(AAssetManager *assetManager, const char *nativeSrcPath, const char *torchNetPath, float *sharedBuffer, int32_t bufferSize);
    ~Torch();
    float call();
    lua_State *lua;
private:
    float *sharedBuffer;
    int32_t bufferSize;
    THFloatStorage *tensorStorage;
    THFloatTensor *tensor;
};


#endif //TORCH_ANDROID_STUDIO_TEMPLATE_TORCH_H
