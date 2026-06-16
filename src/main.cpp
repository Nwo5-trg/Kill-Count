#include <Geode/modify/MenuGameLayer.hpp>
#include <nwo5.silly-api/include/include.hpp>
#include "settings.hpp"

using namespace geode::prelude;
using namespace nwo5::prelude;

class $modify(MenuGameLayerHook, MenuGameLayer) {
    struct Fields {
        CCLabelBMFont* killCountLabel = nullptr;
    };

    bool init() {
        if (!MenuGameLayer::init()) {
            return false;
        }

        if (!Settings::enabled) {
            return true;
        }

        auto fields = m_fields.self();
        
        m_fields->killCountLabel = ui::node(Setup(
            ui::label("", nwo5::utils::getFontString(Settings::labelFont)
        ))
            .id("kill-count-label"_spr)
            .color(color_cast<ccColor3B>(Settings::labelColor.get()))
            .opacity(Settings::labelColor.get().a) 
            .scale(Settings::labelScale)
            .parent(this)
        );

        const auto winSize = CCDirector::get()->getWinSize();
        if (Settings::labelPosition.get() == "Top Right") {
            fields->killCountLabel->setPosition(winSize - Settings::labelBuffer);
            fields->killCountLabel->setAnchorPoint(ccp(1.0f, 1.0f));
        }
        else if (Settings::labelPosition.get() == "Top Left") {
            fields->killCountLabel->setPosition(Settings::labelBuffer, winSize.height - Settings::labelBuffer);
            fields->killCountLabel->setAnchorPoint(ccp(0.0f, 1.0f));
        }
        else if (Settings::labelPosition.get() == "Bottom Left") {
            fields->killCountLabel->setPosition(Settings::labelBuffer, Settings::labelBuffer);
            fields->killCountLabel->setAnchorPoint(ccp(0.0f, 0.0f));
        }
        else if (Settings::labelPosition.get() == "Bottom Right") {
            fields->killCountLabel->setPosition(winSize.width - Settings::labelBuffer, Settings::labelBuffer);
            fields->killCountLabel->setAnchorPoint(ccp(1.0f, 0.0f));
        }

        schedule(schedule_selector(MenuGameLayerHook::updateKillCountLabel));

        return true;
    }

    void updateKillCountLabel(float) {
        if (auto label = m_fields->killCountLabel) {
            label->setString(fmt::format("{}{}", Settings::labelPrefix.get(), GameStatsManager::get()->getStat("9")).c_str());

            if (Settings::chroma) {
                label->setColor(
                    nwo5::utils::getChroma<ccColor3B>(Settings::chromaSpeed, {}, 0.5f)
                );
            }
        }
    }
};

$on_mod(Loaded) {
    SettingsManager::get()->load();
}