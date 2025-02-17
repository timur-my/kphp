// Compiler for PHP (aka KPHP)
// Copyright (c) 2023 LLC «V Kontakte»
// Distributed under the GPL v3 License, see LICENSE.notice.txt

#include "runtime/tl/tl_magics_decoding.h"

// This is a default weak implementation. Strong one is generated by KPHP compiler if TL scheme is passed
const char * __attribute__ ((weak)) tl_function_magic_to_name(uint32_t) noexcept {
  return "__unknown__";
}

string f$convert_tl_function_magic_to_name(int64_t magic) noexcept {
  return string{tl_function_magic_to_name(static_cast<uint32_t>(magic))};
}
