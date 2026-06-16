#pragma once

#include <nwo5.silly-api/include/settings/include.hpp>

using namespace nwo5::settings::prelude;

namespace Settings {
    inline Setting<bool> enabled{"enabled"};
    inline Setting<std::string> labelPosition{"label-position"};
    inline Setting<std::string> labelPrefix{"label-prefix"};
    inline Setting<cocos2d::ccColor4B> labelColor{"label-color"};
    inline Setting<float> labelScale{"label-scale"};
    inline Setting<float> labelBuffer{"label-buffer"};
    inline Setting<int> labelFont{"label-font"};
    inline Setting<bool> chroma{"chroma"};
    inline Setting<float> chromaSpeed{"chroma-speed"};
}