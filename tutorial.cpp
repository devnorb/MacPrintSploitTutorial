#include <thread>
#include <mach-o/dyld.h>

int main()
{
    std::this_thread::sleep_for(std::chrono::seconds(13)); // give ample time to get into a game (you can modify this value based on your Mac's performance)
    uintptr_t offset = 0x1010adc10;
    typedef int (*printdef)(int, const char*, ...);
    auto printfunction = reinterpret_cast<printdef>(_dyld_get_image_vmaddr_slide(0) + (uintptr_t)offset);

    printfunction(0, "print"); // white
    printfunction(1, "info"); // blue -> doesn't have chunkname (like Stack Begin/End)
    printfunction(2, "warn"); // yellow
    printfunction(3, "error"); // red -> doesn't have chunkname (like Stack Begin/End)

    return 0;
}

__attribute__((constructor)) void entry()
{
    printf("[ Custom printsploit dylib injected ]\n");
    std::thread(main).detach();
}
