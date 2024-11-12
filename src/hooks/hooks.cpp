#include <hooks/hooks.hpp>
#include <hooks/endpoints.hpp>

void hooks::Init() {
  MH_Initialize();

  const auto proc = GetProcAddress(GetModuleHandleA("d3d9.dll"), "Direct3DCreate9");
  hooks::direct_3d_create_9.Install(proc, &hooks::endpoints::Direct3DCreate9);
}
