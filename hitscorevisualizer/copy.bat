@echo off

echo Starting build...

ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk
adb push libs/armeabi-v7a/libhitscorevisualizer.so /sdcard/Android/data/com.beatgames.beatsaber/files/mods/libhitscorevisualizer.so
adb shell am force-stop com.beatgames.beatsaber

adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
