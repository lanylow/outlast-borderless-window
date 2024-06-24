#include <hooks/hooks.hpp>
#include <windows.h>
#include <chrono>

using namespace std::chrono_literals;

void init() {
  while (!GetModuleHandleA("d3d9.dll"))
    std::this_thread::sleep_for(10ms);

  hooks::initialize();
}

bool __stdcall DllMain(void* module, std::uint32_t reason, void* reserved) {
  if (reason == DLL_PROCESS_ATTACH)
    std::thread(init).detach();

  return true;
}