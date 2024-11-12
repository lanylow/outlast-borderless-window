#pragma once

#include <d3d9.h>
#include <cstdint>

namespace hooks::endpoints {
  IDirect3D9* __stdcall Direct3DCreate9(uint32_t sdk_version);
  HRESULT __stdcall CreateDevice(IDirect3D9* _this, uint32_t adapter, D3DDEVTYPE device_type, HWND focus_window, uint32_t behavior_flags, D3DPRESENT_PARAMETERS* presentation_parameters, IDirect3DDevice9** returned_device_interface);
  HRESULT __stdcall Reset(IDirect3DDevice9* _this, D3DPRESENT_PARAMETERS* presentation_parameters);
}