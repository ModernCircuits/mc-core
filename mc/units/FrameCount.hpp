#pragma once

#include "mc/cstdint.hpp"

namespace mc {

struct FrameCount {
private:
    std::uint64_t count_ { 0 };
};

} // namespace mc