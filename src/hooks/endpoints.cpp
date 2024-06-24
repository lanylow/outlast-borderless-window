#include <hooks/hooks.hpp>
#include <hooks/endpoints.hpp>

IDirect3D9* __stdcall hooks::endpoints::direct_3d_create_9(std::uint32_t sdk_version) {
  const auto result = hooks::direct_3d_create_9.get_trampoline<decltype(&hooks::endpoints::direct_3d_create_9)>()(sdk_version);

  if (result != nullptr)
    hooks::create_device.install_in_vtable(result, 16, &hooks::endpoints::create_device);

  return result;
}

HRESULT __stdcall hooks::endpoints::create_device(IDirect3D9* _this, std::uint32_t adapter, D3DDEVTYPE device_type, HWND focus_window, std::uint32_t behavior_flags, D3DPRESENT_PARAMETERS* presentation_parameters, IDirect3DDevice9** returned_device_interface) {
  const auto result = hooks::create_device.get_trampoline<decltype(&hooks::endpoints::create_device)>()(_this, adapter, device_type, focus_window, behavior_flags, presentation_parameters, returned_device_interface);

  if (SUCCEEDED(result))
    hooks::reset.install_in_vtable(*returned_device_interface, 16, &hooks::endpoints::reset);

  return result;
}

HRESULT __stdcall hooks::endpoints::reset(IDirect3DDevice9* _this, D3DPRESENT_PARAMETERS* presentation_parameters) {
  const auto trampoline = hooks::reset.get_trampoline<decltype(&hooks::endpoints::reset)>();

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