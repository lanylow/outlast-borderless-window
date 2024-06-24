#pragma once

#include <utils/function.hpp>
#include <minhook/MinHook.h>
#include <type_traits>

namespace hooks {
  struct hook_storage {
    void* address{ nullptr };
    void* trampoline{ nullptr };
  };

  template <typename storage_type = hooks::hook_storage,
    std::enable_if_t<(std::is_base_of_v<hook_storage, storage_type> || std::is_same_v<hook_storage, storage_type>) && std::is_default_constructible_v<storage_type>, int> = 0>
  class hook {
  public:
    constexpr hook() = default;

  private:
    void create(void* detour) {
      MH_CreateHook(storage.address, detour, &storage.trampoline);
      MH_EnableHook(storage.address);
    }

  public:
    template <typename target_type, typename detour_type,
      std::enable_if_t<std::is_pointer_v<detour_type>, int> = 0>
    void install(target_type target, detour_type detour) {
      storage.address = (void*)(target);
      create((void*)(detour));
    }

    template <typename obj_type, typename detour_type,
      std::enable_if_t<std::is_pointer_v<obj_type> && std::is_pointer_v<detour_type>, int> = 0>
    void install_in_vtable(obj_type obj, std::size_t index, detour_type detour) {
      storage.address = (*(void***)(obj))[index];
      create((void*)(detour));
    }

    template <typename trampoline_type,
      std::enable_if_t<utils::is_fn_convertible<trampoline_type>::value, int> = 0>
    constexpr trampoline_type get_trampoline() const {
      return (trampoline_type)(storage.trampoline);
    }

    storage_type storage;
  };
}