/**
 * @author Pär Amsen 04/2017
 */

#include "Torch.h"
#include "Constants.h"
#include "Log.h"
#include <stdexcept>

Torch::Torch(AAssetManager *assetManager, const char *nativeSrcPath, const char *torchNetPath) {
    tensorStorage = THFloatStorage_newWithSize(INPUT_LENGTH);
    lua = inittorch(assetManager, nativeSrcPath);

    char file[] = "main.lua";
    int32_t ret;
    size_t size = (size_t) android_asset_get_size(file);
    if (size != -1) {
        char *filebytes = android_asset_get_bytes(file);
        ret = luaL_dobuffer(lua, filebytes, size, "main");
        if (ret == 1) {
            lE("Init Torch error");
        } else {
            lD("Init Torch with dynamic net path");
            lua_getglobal(lua, "init");
            lua_pushstring(lua, torchNetPath);
            int success = lua_pcall(lua, 1, 1, 0);
            if (success != 0) throw std::runtime_error(std::string("Error calling main.lua::init with path"));
            lD("Torch setup successfully with neuron net");
        }
    }
}

float Torch::call(float *data) {
    THFloatStorage_rawCopy(tensorStorage, data);
    lua_getglobal(lua, "call");
    luaT_pushudata(lua, (void *)tensor, "torch.FloatTensor");
    int success = lua_pcall(lua, 1, 1, 0);
    if(success != 0)  throw std::runtime_error(std::string("Error calling main.lua::call with FloatTensor"));
    float result = (float) lua_tonumber(lua, -1);
    lua_pop(lua, 1);

    return result;
}

Torch::~Torch() {
    THFloatStorage_free(tensorStorage);
    lua_close(lua);
}
