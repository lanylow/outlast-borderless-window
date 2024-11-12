#include <windows.h>
#include <chrono>
#include <thread>

#include <hooks/hooks.hpp>

using namespace std::chrono_literals;

void Init() {
  while (!GetModuleHandleA("d3d9.dll"))
    std::this_thread::sleep_for(10ms);

  hooks::Init();
}

bool __stdcall DllMain(void* module, uint32_t reason, void* reserved) {
  if (reason == DLL_PROCESS_ATTACH)
    std::thread(Init).detach();

  return true;
}