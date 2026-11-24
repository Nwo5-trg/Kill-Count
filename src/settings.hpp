#pragma once

#include <nwo5.silly-api/cache/include.hpp>

using namespace nwo5::cache::prelude;

namespace settings {
    inline SettingCache<bool> enabled{"enabled"};
    inline SettingCache<std::string> labelPosition{"label-position"};
    inline SettingCache<std::string> labelPrefix{"label-prefix"};
    inline SettingCache<cocos2d::ccColor4B> labelColor{"label-color"};
    inline SettingCache<float> labelScale{"label-scale"};
    inline SettingCache<float> labelBuffer{"label-buffer"};
    inline SettingCache<int> labelFont{"label-font"};
    inline SettingCache<bool> chroma{"chroma"};
    inline SettingCache<float> chromaSpeed{"chroma-speed"};
}