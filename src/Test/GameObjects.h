#pragma once

#include <Cruz3D/Graphic/Passes.h>
#include <memory>

namespace game
{
struct Trash
{
    std::unique_ptr<cruz::SimpleBinding> binding;
};

struct Checkboard
{
    std::unique_ptr<cruz::SimpleBinding> binding;
};
} // namespace game