/**
 * @author Pär Amsen 04/2017
 */

#ifndef TORCH_ANDROID_STUDIO_TEMPLATE_LOG_H
#define TORCH_ANDROID_STUDIO_TEMPLATE_LOG_H

#  define  lD(x...)  __android_log_print(ANDROID_LOG_DEBUG, "TorchTemple", x)
#  define  lW(x...)  __android_log_print(ANDROID_LOG_WARN, "TorchTemple", x)
#  define  lE(x...)  __android_log_print(ANDROID_LOG_ERROR, "TorchTemple", x)

#endif //TORCH_ANDROID_STUDIO_TEMPLATE_LOG_H
