#pragma once

#include <minhook/MinHook.h>

namespace hooks {
  class Hook {
  public:
    Hook() = default;

    template <typename TTarget, typename TDetour>
    void Install(TTarget target, TDetour detour) {
      CreateHook((void*)target, (void*)detour);
    }

    template <typename TObj, typename TDetour>
    void InstallInVMT(TObj obj, size_t index, TDetour detour) {
      const auto target = (*(void***)obj)[index];
      CreateHook(target, (void*)detour);
    }

    template <typename TTrampoline>
    inline TTrampoline GetTrampoline() const { return (TTrampoline)trampoline_; }

  private:
    void CreateHook(void* target, void* detour) {
      MH_CreateHook(target, detour, &trampoline_);
      MH_EnableHook(target);
    }

    void* trampoline_ = nullptr;
  };
}