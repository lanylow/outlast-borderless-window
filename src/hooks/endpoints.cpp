#include <hooks/hooks.hpp>
#include <hooks/endpoints.hpp>

IDirect3D9* __stdcall hooks::endpoints::Direct3DCreate9(uint32_t sdk_version) {
  const auto result = hooks::direct_3d_create_9.GetTrampoline<decltype(&hooks::endpoints::Direct3DCreate9)>()(sdk_version);

  if (result != nullptr)
    hooks::create_device.InstallInVMT(result, 16, &hooks::endpoints::CreateDevice);

  return result;
}

HRESULT __stdcall hooks::endpoints::CreateDevice(IDirect3D9* _this, uint32_t adapter, D3DDEVTYPE device_type, HWND focus_window, uint32_t behavior_flags, D3DPRESENT_PARAMETERS* presentation_parameters, IDirect3DDevice9** returned_device_interface) {
  const auto result = hooks::create_device.GetTrampoline<decltype(&hooks::endpoints::CreateDevice)>()(_this, adapter, device_type, focus_window, behavior_flags, presentation_parameters, returned_device_interface);

  if (SUCCEEDED(result))
    hooks::reset.InstallInVMT(*returned_device_interface, 16, &hooks::endpoints::Reset);

  return result;
}

HRESULT __stdcall hooks::endpoints::Reset(IDirect3DDevice9* _this, D3DPRESENT_PARAMETERS* presentation_parameters) {
  const auto trampoline = hooks::reset.GetTrampoline<decltype(&hooks::endpoints::Reset)>();

  if (presentation_parameters == nullptr || presentation_parameters->Windowed)
    return trampoline(_this, presentation_parameters);

  if (presentation_parameters->hDeviceWindow)
    SetForegroundWindow(presentation_parameters->hDeviceWindow);

  const auto window = GetActiveWindow();

  presentation_parameters->Windowed = TRUE;
  presentation_parameters->FullScreen_RefreshRateInHz = 0;
  presentation_parameters->hDeviceWindow = window;

  auto style = GetWindowLongA(window, GWL_STYLE);
  style &= ~(WS_OVERLAPPEDWINDOW | WS_MINIMIZE | WS_MAXIMIZE);
  SetWindowLongA(window, GWL_STYLE, style);

  auto monitor_info = MONITORINFO();
  monitor_info.cbSize = sizeof(monitor_info);
  GetMonitorInfoA(MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST), &monitor_info);

  const auto width = monitor_info.rcMonitor.right - monitor_info.rcMonitor.left;
  const auto height = monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top;

  SetWindowPos(window, nullptr, monitor_info.rcMonitor.left, monitor_info.rcMonitor.top, width, height, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
  BringWindowToTop(window);

  return trampoline(_this, presentation_parameters);
}