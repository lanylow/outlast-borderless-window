#pragma once

#include <type_traits>

namespace utils {
  template <typename cast_type>
  struct is_fn_convertible :
    std::disjunction<
      std::is_integral<cast_type>,
      std::is_pointer<cast_type>
    > { };
}