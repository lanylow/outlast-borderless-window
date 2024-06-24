#pragma once

#include <hooks/hook.hpp>
#include <mutex>

namespace hooks {
  void initialize();

  inline hooks::hook<> direct_3d_create_9;
  inline hooks::hook<> create_device;
  inline hooks::hook<> reset;
}
