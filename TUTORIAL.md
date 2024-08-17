# Mac PrintSploit Tutorial / Walkthrough
------------------------------

## Introduction
This tutorial will walk you through the process of making a simple MacOS printsploit using native Mac libraries for injection (dyld) and calling the Roblox print offset externally

## Prerequisites
Any IDA that works on MacOS (Binary Ninja preferably) -> `https://binary.ninja/free/`
Roblox **INTEL** version -> `curl -s "https://raw.githubusercontent.com/devnorb/MacPrintSploitTutorial/main/intelinstaller.sh" | bash`
VSCode or any IDE -> `https://code.visualstudio.com/Download`
Basic knowledge of how Mac works
Common Sense

(I used Binary Ninja Personal 4.1.5747, VSCode, and this tutorial was done on Roblox version `version-9a42bf606f9f44c2`)

## Tutorial

First Section:
### Getting print offset
Open Binary Ninja and load `/Applications/Roblox.app/Contents/MacOS/RobloxPlayer` (Do not load /Applications/Roblox.app as it is a directory containing the main executable and dependencies!)
If you cannot find the RobloxPlayer dylib, run `open /Applications/Roblox.app/Contents/MacOS/` and then drag the RobloxPlayer dylib into Binary Ninja
Binary Ninja will start analyzing the RobloxPlayer dylib -> (Status should show `Analysis Phase 1...Analysis/Disassembling (*/*)`)
If you do **not** see that status, double check if your Roblox is Intel version (again refer to Prerequisites)
Open the strings view -> (There are 2 ways to open the strings view -> 1 is to go to the Mac topbar (when Binary Ninja is **focused**) and press View, and click Strings. -> 2 is to go to the rightmost bar, and there should be a quote icon on the bar. Click that and Strings view should open. (THIS IS VERSION SPECIFIC i think))
Type in `Current identity is %d` and a search result should pop up.
Click the search result -> (If the text is still blue and not pink then wait until it turns pink; should be around 3 minutes)
After it is done analyzing the function that contains the string `Current identity is %d`, open the Cross References tab in Binary Ninja (The last button in the leftmost bar of Binary Ninja) and double click the first result.
You should see `r14_1 = sub_PRINTADDRESS(0, "Current identity is %d", 0);`
The print address is the sub_ function there (for `version-9a42bf606f9f44c2` it is sub_1010adc10)
Remove the sub_ and replace it with 0x (should look like 0x1010adc10)
Save the offset

Next Section:
### Adding C++ code
Make a folder named `printsploit` 
Copy and paste code -> (find code here: `https://github.com/devnorb/MacPrintSploitTutorial/blob/main/tutorial.cpp`)
Change the offset variable in main.cpp to the one you found (uintptr_t offset = **0x1010adc10**;) -> (uintptr_t offset = THEOFFSETYOUSAVED;)
Save the file & name the file as main.cpp
Open a new VSCode terminal -> (go to Mac topbar (when VSCode is **focused**) and press Terminal, and press New Terminal)
Compile the main.cpp using clang++ (cmake is a bit more complex so I chose to use clang++ instead)
Enter this into VSCode terminal: `clang++ -arch x86_64 -std=c++17 -dynamiclib main.cpp -o printsploit.dylib -lpthread`
Wait for it to compile
Afterwards, you should see a printsploit.dylib file in the folder
Run `DYLD_INSERT_LIBRARIES="./printsploit.dylib" /Applications/Roblox.app/Contents/MacOS/RobloxPlayer` in the same VSCode terminal
Roblox should launch; join a game and open console
It should display the 4 console outputs (print, info, warn, error), and if it doesn't, increase the sleep time by ~5 seconds and it should work.
------------------------------------------------------------------------------------------------------------------------------------------------
If there are any issues, feel free to contact me on Discord (@norby.dev_) or make a issue here on this repository.
Any improvements or suggestions, make a pull request.
