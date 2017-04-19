/**
 * @author Pär Amsen 04/2017
 */

#include "Torch.h"
#include <stdexcept>
#include <android/log.h>

Torch::Torch(AAssetManager *assetManager, const char *nativeSrcPath, const char *torchNetPath, float *sharedBuffer, int32_t bufferSize) {
    this->sharedBuffer = sharedBuffer;
    this->bufferSize = bufferSize;
    tensorStorage = THFloatStorage_newWithData(tensorData, bufferSize);
    lua = inittorch(assetManager, nativeSrcPath);

    char file[] = "main.lua";
    int32_t ret;
    size_t size = (size_t) android_asset_get_size(file);
    if (size != -1) {
        char *filebytes = android_asset_get_bytes(file);
        ret = luaL_dobuffer(lua, filebytes, size, "main");
        if (ret == 1) {
            __android_log_print(ANDROID_LOG_ERROR, "Torch.cpp", "Init Torch error");
        } else {
            __android_log_print(ANDROID_LOG_DEBUG, "Torch.cpp", "Init Torch with dynamic net path");
            lua_getglobal(lua, "init");
            lua_pushstring(lua, torchNetPath);
            int success = lua_pcall(lua, 1, 1, 0);
            if (success != 0) throw std::runtime_error(std::string("Error calling main.lua::init with path"));
            __android_log_print(ANDROID_LOG_DEBUG, "Torch.cpp", "Torch setup successfully with neuron net");
        }
    }
}

float Torch::call() {
    lua_getglobal(lua, "call");
    luaT_pushudata(lua, (void *)tensor, "torch.FloatTensor");
    int success = lua_pcall(lua, 1, 1, 0);
    if(success != 0)  throw std::runtime_error(std::string("Error calling main.lua::call with FloatTensor"));
    float result = lua_tonumber(lua, -1);
    lua_pop(lua, 1);

    return result;
}

Torch::~Torch() {
    luaT_free(lua);
}
