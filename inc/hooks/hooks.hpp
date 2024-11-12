#pragma once

#include <hooks/hook.hpp>

namespace hooks {
  void Init();

  inline hooks::Hook direct_3d_create_9;
  inline hooks::Hook create_device;
  inline hooks::Hook reset;
}
