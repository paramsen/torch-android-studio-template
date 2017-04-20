# Torch Android Studio template

This repo displays a modern working sample of `torch-android`, in contrast to the official outdated demos it does not use ANT or eclipse.
* Android Studio
* Latest build tools (25+ as of April 2017)
* Gradle
* Cmake NDK buildchain (using CMakeLists.txt to setup native build)

This project is the topic of a `torch-android` article series of mine [paramsen.github.io](https://paramsen.github.io/building-torch-android-01/).

## Setup

In order to run it you have to build `torch-android` from source, I've automated the process as described [here in an article @ paramsen.github.io](https://paramsen.github.io/torch-android-vagrant-build-box/). Simply put you will need to build `torch-android` for the architectures armeabi-v7a and arm64-v8a either by using my automatic-vagrant-build-box or the manual official guide. When built you copy the binaries to `./app/native-libs` and the built lua lib to `./app/src/main/assets/lua`.

## Motivation

The official demo projects are built with ANT and probably created in Eclipse back in 2011 (?). The Android devs have long since deprecated pretty much everything from back then, even the old NDK buildchain, so integrating `torch-android` into a modern Android Studio project is all about trial-and-error right now.

I integrated `torch-android` for a client, spending over 400 hours on the task. With a proper project like this I would probably only have spent ~80 hours, focusing less on figuring out wth is going on and more on actually integrating Torch. With this sample project I hope to help future devs from going down the same rabbit hole.

## Features

#### cmake buildchain
It's not pretty, but I got the cmake buildchain working with `torch-android` after some struggling, check it out [CMakeLists.txt](https://github.com/paramsen/torch-android-studio-template/blob/master/app/CMakeLists.txt). I also did some magic in the [build.gradle](https://github.com/paramsen/torch-android-studio-template/blob/master/app/build.gradle#L32) to get it working.

#### x86 fallback (emulator support)
I've setup the project to run on both x86 and ARM systems, even though Torch only supports ARM. This means you can use the emulator even though you have an ARM-only dependency. This is done through simply providing a stub implementation of the native parts when on x86. Here's the magic [CMakeLists.txt](https://github.com/paramsen/torch-android-studio-template/blob/master/app/CMakeLists.txt#L109).

#### Dynamic parameters to Torch .lua script
1. Torch is initialized with a dynamic path to the `.net` model file, look at [Torch.cpp#25](https://github.com/paramsen/torch-android-studio-template/blob/master/app/src/main/native/Torch.cpp#L25) and [main.lua#8](https://github.com/paramsen/torch-android-studio-template/blob/master/app/src/main/assets/main.lua#L8) to see how it works.
2. Torch is processing dynamic data bridged from Java to Torch lua. Look at [Torch.cpp#36](https://github.com/paramsen/torch-android-studio-template/blob/master/app/src/main/native/Torch.cpp#L36) and [main.lua#16](https://github.com/paramsen/torch-android-studio-template/blob/master/app/src/main/assets/main.lua#L16)

#### Deterministic Torch lifecycle
Torch is properly initialized lazily and destroyed, freeing all resources. Low battery impact was top priority for my client, so inventing a proper lifecycle management was crucial. Look at [JNIBridge.cpp#25](https://github.com/paramsen/torch-android-studio-template/blob/master/app/src/main/native/JNIBridge.cpp#L25) and [JNIBridge.cpp#57](https://github.com/paramsen/torch-android-studio-template/blob/master/app/src/main/native/JNIBridge.cpp#L57) to see how it's implemented.  
Torch can be initialized, destroyed and initialized again without any problems.

#### Simple api
The integration between Java, C and lua (Torch) is pretty simple in this project. Hopefully the code is self-documenting.

<p align="center">
  <img src="https://github.com/paramsen/torch-android-studio-template/blob/master/optimized-flow-chart.jpg" alt="Preview flow chart" height=500/>
</p>

## Troubleshooting

Issues goes here, questions might be more fitting here [paramsen.github.io](https://paramsen.github.io/torch-cmake-and-android-studio/) in the comments section.

## License

I created this purely for educational purposes, hence the MIT license.