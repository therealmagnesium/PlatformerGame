#!/bin/bash

config="$1"
appName="UntitledPlatformer"

if [[ $config = "run" ]]
then
    mode="$2"
    if [[ $mode = "debug" ]]
    then
        cd "bin/Debug-linux/$appName"
        ./$appName
    elif [[ $mode = "release" ]]
    then
        cd "bin/Release-linux/$appName"
        ./$appName
    elif [[ $mode = "dist" ]]
    then
        cd "bin/Dist-linux/$appName"
        ./$appName
    fi
elif [[ $config = "assets" ]]
then
    mode="$2"
    if [[ $mode = "debug" ]]
    then
        cp -r App/assets/ bin/Debug-linux/Application/
    elif [[ $mode = "release" ]]
    then
        cp -r App/assets/ bin/Release-linux/Application/
    elif [[ $mode = "dist" ]]
    then
        cp -r App/assets/ bin/Dist-linux/Application/
    fi

elif [[ $config = "clean" ]]
then
    rm -rf bin build
else
    vendor/premake/linux/premake5 export-compile-commands
    vendor/premake/linux/premake5 gmake
    make all config=$config -j4
    cp compile_commands/debug.json compile_commands.json
fi
