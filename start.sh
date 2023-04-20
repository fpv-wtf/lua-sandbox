#!/bin/sh
set -e
adb connect 192.168.42.5:5555
mkdir -p build
cd build
cmake \
    -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=armeabi-v7a \
    -DANDROID_PLATFORM=android-23 ../ \
    -DLUA_START_PATH=/tmp/scripts/index.lua \
    -DDEBUG_HTDOCS_PATH=/tmp/htdocs/
make -j32 
adb push ../scripts /tmp/
adb push ../debug_server/htdocs /tmp/
adb push lua-sandbox /tmp 
adb shell "/tmp/lua-sandbox"