// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace mc {
/// \brief Explicitly ignore arguments or variables.
/// \code
/// auto main(int argc, char** argv) -> int
/// {
///   mc::ignoreUnused(argc, argv);
///   return 0;
/// }
/// \endcode
template<typename... Types>
constexpr auto ignoreUnused(Types&&... /*unused*/) -> void
{}
}  // namespace mc
