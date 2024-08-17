#!/bin/bash

main() {
    local json=$(curl -s "https://clientsettingscdn.roblox.com/v2/client-version/MacPlayer")
    local version=$(echo "$json" | grep -o '"clientVersionUpload":"[^"]*' | grep -o '[^"]*$')
    curl "http://setup.rbxcdn.com/mac/$version-RobloxPlayer.zip" -o "./RobloxPlayer.zip"
    unzip -o -q "./RobloxPlayer.zip"
    rm "./RobloxPlayer.zip"
    xattr -c Roblox.app
    codesign --remove-signature "Roblox.app/Contents/MacOS/RobloxPlayer" 
}

main
