cmake_minimum_required(VERSION 3.4.1)

set(X86 FALSE)
if("x86" STREQUAL ${ANDROID_ABI})
    set(X86 TRUE)
else()
    set(X86 FALSE)
endif()

if(NOT ${X86})
    message("Building native for ARM")

    add_library( native
                 SHARED

                 src/main/native/JNIBridge.cpp
                 src/main/native/Torch.cpp )

    add_library( torchandroid
                 SHARED
                 IMPORTED )

    add_library( nnx
                 SHARED
                 IMPORTED )

    add_library( image
                 SHARED
                 IMPORTED )

    add_library( THNN
                 SHARED
                 IMPORTED )

    add_library( torch
                 SHARED
                 IMPORTED )

    add_library( TH
                 SHARED
                 IMPORTED )

    add_library( luaT
                 SHARED
                 IMPORTED )

    add_library( luajit
                 SHARED
                 IMPORTED )


    # Specify paths for each dependency
    set_target_properties( torchandroid
                           PROPERTIES IMPORTED_LOCATION
                           ${CMAKE_SOURCE_DIR}/native-libs/${ANDROID_ABI}/libtorchandroid.so )

    set_target_properties( nnx
                           PROPERTIES IMPORTED_LOCATION
                           ${CMAKE_SOURCE_DIR}/native-libs/${ANDROID_ABI}/libnnx.so )

    set_target_properties( image
                           PROPERTIES IMPORTED_LOCATION
                           ${CMAKE_SOURCE_DIR}/native-libs/${ANDROID_ABI}/libimage.so )

    set_target_properties( THNN
                           PROPERTIES IMPORTED_LOCATION
                           ${CMAKE_SOURCE_DIR}/native-libs/${ANDROID_ABI}/libTHNN.so )

    set_target_properties( torch
                           PROPERTIES IMPORTED_LOCATION
                           ${CMAKE_SOURCE_DIR}/native-libs/${ANDROID_ABI}/libtorch.so )

    set_target_properties( TH
                           PROPERTIES IMPORTED_LOCATION
                           ${CMAKE_SOURCE_DIR}/native-libs/${ANDROID_ABI}/libTH.so )

    set_target_properties( luaT
                           PROPERTIES IMPORTED_LOCATION
                           ${CMAKE_SOURCE_DIR}/native-libs/${ANDROID_ABI}/libluaT.so )

    set_target_properties( luajit
                           PROPERTIES IMPORTED_LOCATION
                           ${CMAKE_SOURCE_DIR}/native-libs/${ANDROID_ABI}/libluajit.so )

    find_library( log-lib
                  log )

    find_library( android-lib
                  android )

    # Include header files
    target_include_directories( native PRIVATE
                                ${CMAKE_SOURCE_DIR}/native-libs/headers
                                ${CMAKE_SOURCE_DIR}/src/main/native )

    target_link_libraries( native

                           torchandroid
                           nnx
                           image
                           THNN
                           torch
                           TH
                           luaT
                           luajit

                           ${log-lib}
                           ${android-lib} )
else()
    message("Building native stub for x86")

    add_library( native
                 SHARED
                 src/main/native/JNIBridgeX86.cpp )

    find_library( log-lib
                  log )

    find_library( android-lib
                  android )

    # Include header files
    target_include_directories( native PRIVATE
                                ${CMAKE_SOURCE_DIR}/native-libs/headers
                                ${CMAKE_SOURCE_DIR}/src/main/native )

    target_link_libraries( native

                           ${log-lib}
                           ${android-lib} )

endif()