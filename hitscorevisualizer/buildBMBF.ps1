# Builds a .zip file for loading with BMBF
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}
$FileName = "./hitscorevisualizer_v3.1.0.zip"
& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk
if (Test-Path $FileName) {
    Remove-Item $FileName
}
Compress-Archive -Path "./libs/arm64-v8a/libhitscorevisualizer.so","./bmbfmod.json" -DestinationPath $FileName
