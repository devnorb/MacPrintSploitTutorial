#include <thread>
#include <mach-o/dyld.h>

int main()
{
    std::this_thread::sleep_for(std::chrono::seconds(13)); // give ample time to get into a game (you can modify this value based on your Mac's performance)
    uintptr_t offset = 0x1010adc10;
    typedef int (*printdef)(int, const char*, ...);
    auto printfunction = reinterpret_cast<printdef>(_dyld_get_image_vmaddr_slide(0) + (uintptr_t)offset);

    auto delayprint = [&](int type, const char* message, std::chrono::milliseconds delay) {
        std::this_thread::sleep_for(delay);
        printfunction(type, message);
    };

    delayprint(0, "print", std::chrono::milliseconds(200)); 
    delayprint(1, "info", std::chrono::milliseconds(200));  
    delayprint(2, "warn", std::chrono::milliseconds(200));  
    delayprint(3, "error", std::chrono::milliseconds(200));

    return 0;
}

__attribute__((constructor)) void entry()
{
    printf("[ Custom printsploit dylib injected ]\n");
    std::thread(main).detach();
}
