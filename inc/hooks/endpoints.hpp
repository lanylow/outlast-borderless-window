#pragma once

#include <d3d9.h>
#include <d3d11.h>

namespace hooks::endpoints {
  IDirect3D9* __stdcall direct_3d_create_9(std::uint32_t sdk_version);
  HRESULT __stdcall create_device(IDirect3D9* _this, std::uint32_t adapter, D3DDEVTYPE device_type, HWND focus_window, std::uint32_t behavior_flags, D3DPRESENT_PARAMETERS* presentation_parameters, IDirect3DDevice9** returned_device_interface);
  HRESULT __stdcall reset(IDirect3DDevice9* _this, D3DPRESENT_PARAMETERS* presentation_parameters);
}