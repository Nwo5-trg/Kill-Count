#include <Geode/modify/MenuGameLayer.hpp>
#include <nwo5.silly-api/include/include.hpp>
#include "settings.hpp"

using namespace geode::prelude;
using namespace nwo5::prelude;

class $modify(KillCountMenuGameLayer, MenuGameLayer) {
    struct Fields {
        geode::Label* killCountLabel = nullptr;
    };

    bool init() {
        if (!MenuGameLayer::init()) {
            return false;
        }

        if (!settings::enabled) {
            return true;
        }

        auto fields = m_fields.self();
        
        m_fields->killCountLabel = ui::label("", nwo5::utils::getFontString(settings::labelFont))
            .id("kill-count-label"_spr)
            .color(color_cast<ccColor3B>(settings::labelColor.get()))
            .opacity(settings::labelColor.get().a) 
            .scale(settings::labelScale)
            .parent(this);

        const auto winSize = CCDirector::get()->getWinSize();
        if (settings::labelPosition.get() == "Top Right") {
            fields->killCountLabel->setPosition(winSize - settings::labelBuffer);
            fields->killCountLabel->setAnchorPoint(ccp(1.0f, 1.0f));
        }
        else if (settings::labelPosition.get() == "Top Left") {
            fields->killCountLabel->setPosition(settings::labelBuffer, winSize.height - settings::labelBuffer);
            fields->killCountLabel->setAnchorPoint(ccp(0.0f, 1.0f));
        }
        else if (settings::labelPosition.get() == "Bottom Left") {
            fields->killCountLabel->setPosition(settings::labelBuffer, settings::labelBuffer);
            fields->killCountLabel->setAnchorPoint(ccp(0.0f, 0.0f));
        }
        else if (settings::labelPosition.get() == "Bottom Right") {
            fields->killCountLabel->setPosition(winSize.width - settings::labelBuffer, settings::labelBuffer);
            fields->killCountLabel->setAnchorPoint(ccp(1.0f, 0.0f));
        }

        schedule(schedule_selector(KillCountMenuGameLayer::updateKillCountLabel));

        return true;
    }

    void updateKillCountLabel(float) {
        if (auto label = m_fields->killCountLabel) {
            label->setText(fmt::format("{}{}", settings::labelPrefix.get(), GameStatsManager::get()->getStat("9")));

            if (settings::chroma) {
                label->setColor(
                    nwo5::utils::getChroma<ccColor3B>(settings::chromaSpeed, {}, 0.5f)
                );
            }
        }
    }
};

$on_mod(Loaded) {
    SettingsManager::get()->load();
}