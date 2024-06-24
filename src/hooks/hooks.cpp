#include <hooks/hooks.hpp>
#include <hooks/endpoints.hpp>

void hooks::initialize() {
  MH_Initialize();

  const auto proc = GetProcAddress(GetModuleHandleA("d3d9.dll"), "Direct3DCreate9");
  hooks::direct_3d_create_9.install(proc, &hooks::endpoints::direct_3d_create_9);
}
