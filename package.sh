#!/bin/sh
mkdir -p ipk-build
cd ipk-build
cmake \
    -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=armeabi-v7a \
    -DANDROID_PLATFORM=android-23 ../ \
    -DLUA_START_PATH=/opt/share/lua-sandbox/scripts/index.lua \
    -DDEBUG_HTDOCS_PATH="/opt/share/lua-sandbox/htdocs/"
make -j32
cd ../ipk/lua-sandbox
make clean
make
cd ../../

mkdir -p flappy-build
cd flappy-build
cmake \
    -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=armeabi-v7a \
    -DANDROID_PLATFORM=android-23 ../ \
    -DLUA_START_PATH=/opt/share/flappy-bird/scripts/index.lua \
    -DDEBUG_HTDOCS_PATH=/opt/share/flappy-bird/htdocs/
make -j32
cd ../ipk/flappy-bird
make clean
make

cd ../../

if [ "$1" = "install" ]; then
    adb connect 192.168.42.5:5555
    sleep 1
    adb push ipk/*.ipk /tmp
    adb shell ". /etc/mkshrc && cd /tmp && opkg install --force-reinstall *.ipk"
fi