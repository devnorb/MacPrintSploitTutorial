#include <thread>
#include <mach-o/dyld.h>

int main()
{
    std::this_thread::sleep_for(std::chrono::seconds(13)); // give ample time to get into a game (you can modify this value based on your Mac's performance)
    uintptr_t offset = 0x1010adc10;
    auto print = reinterpret_cast<void(*)(int, const char*, ...)>(_dyld_get_image_vmaddr_slide(0) + (uintptr_t)offset);

    print(0, "print"); // white
    print(1, "info"); // blue -> doesn't have chunkname (like Stack Begin/End)
    print(2, "warn"); // yellow
    print(3, "error"); // red -> doesn't have chunkname (like Stack Begin/End)

    return 0;
}

__attribute__((constructor)) void entry()
{
    printf("[ Custom printsploit dylib injected ]\n");
    std::thread(main).detach();
}
