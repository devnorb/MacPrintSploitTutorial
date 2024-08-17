local version=$(echo "$json" | grep -o '"clientVersionUpload":"[^"]*' | grep -o '[^"]*$')
curl "http://setup.rbxcdn.com/mac/$version-RobloxPlayer.zip" -o "./RobloxPlayer.zip"
unzip -o -q "./RobloxPlayer.zip"
mv "./RobloxPlayer.app"
rm "./RobloxPlayer.zip"
xattr -c Roblox.app # removes it from quarantine 
codesign --remove-signature "/Applications/Roblox.app/Contents/MacOS/RobloxPlayer" # need to remove the signature to make the injection method work
