// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_filesystem)
#include <filesystem>

namespace mc {
namespace fs = std::filesystem;
}  // namespace mc
#endif
