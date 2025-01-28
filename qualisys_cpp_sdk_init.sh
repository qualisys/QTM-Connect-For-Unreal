#!/usr/bin/env bash

# The target directory for copied files
dir_private="Qualisys/QTMConnectLiveLink/Source/QTMConnectLiveLink/Private/RTClientSDK"

# Files to copy
files=(
    "Markup.cpp"
    "Network.cpp"
    "RTPacket.cpp"
    "RTProtocol.cpp"
    "Markup.h"
    "Network.h"
    "RTPacket.h"
    "RTProtocol.h"
)

echo "Ensuring directory exists..."
mkdir -p "$dir_private"

echo "Copying files from qualisys_cpp_sdk into $dir_private"

# Loop over files array and copy each into $dir_private
for file in "${files[@]}"; do
    cp -f "qualisys_cpp_sdk/$file" "$dir_private"
done

echo "Done copying files from qualisys_cpp_sdk into $dir_private"
