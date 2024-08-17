#!/bin/bash

main() {
    local json=$(curl -s "https://clientsettingscdn.roblox.com/v2/client-version/MacPlayer")
    local version=$(echo "$json" | grep -o '"clientVersionUpload":"[^"]*' | grep -o '[^"]*$')
    curl "http://setup.rbxcdn.com/mac/$version-RobloxPlayer.zip" -o "./RobloxPlayer.zip"
    [ -d "/Applications/Roblox.app" ] && rm -rf "/Applications/Roblox.app"
    unzip -o -q "./RobloxPlayer.zip"
    mv "./RobloxPlayer.app" "/Applications/Roblox.app"
    rm "./RobloxPlayer.zip"
    xattr -c /Applications/Roblox.app # removes it from quarantine 
    codesign --remove-signature "/Applications/Roblox.app/Contents/MacOS/RobloxPlayer" # need to remove the signature to make the injection method work
}

main
