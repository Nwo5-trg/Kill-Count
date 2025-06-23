#include <Geode/Geode.hpp>
#include <Geode/modify/MenuGameLayer.hpp>

using namespace geode::prelude;

class $modify(MainMenuGameLayer, MenuGameLayer) {
    struct Fields {
        CCLabelBMFont* killCountLabel;
        std::string labelPrefix = "Kill Count: ";
    };

    bool init() {
        if (!MenuGameLayer::init()) return false;

        auto mod = Mod::get();
        auto winSize = CCDirector::get()->getWinSize();

        float labelScale = mod->getSettingValue<double>("label-scale");
        float labelBuffer = mod->getSettingValue<double>("label-buffer");
        m_fields->labelPrefix = mod->getSettingValue<std::string>("label-prefix");

        auto labelPositionString = mod->getSettingValue<std::string>("label-position");
        int labelPosition = 4;
        if (labelPositionString == "Top Right") labelPosition = 1;
        else if (labelPositionString == "Top Left") labelPosition = 2;
        else if (labelPositionString == "Bottom Left") labelPosition = 3;

        int labelFont = mod->getSettingValue<int64_t>("label-font");
        std::string fontString = "";
        float fontScale = 0.75f;
        if (labelFont == 0) fontString = "bigFont.fnt";
        else if (labelFont <= 59) {
            fontString = std::string("gjFont") + (labelFont < 10 ? "0" : "") + std::to_string(labelFont) + ".fnt";
        } else if (labelFont == 60) {
            fontString = "chatFont.fnt";
            fontScale = 1.75f;
        } else if (labelFont == 61) {
            fontString = "goldFont.fnt";
            fontScale = 1.0f;
        }
        
        auto killCountLabel = CCLabelBMFont::create("", "chatFont.fnt");
        killCountLabel->setScale(labelScale);
        this->addChild(killCountLabel);
        m_fields->killCountLabel = killCountLabel;
        updateKillCountLabel();

        switch (labelPosition) {
            case 1: {
                killCountLabel->setPosition(winSize - labelBuffer);
                killCountLabel->setAnchorPoint(ccp(1.0f, 1.0f));
                break;
            }
            case 2: {
                killCountLabel->setPosition(labelBuffer, winSize.height - labelBuffer);
                killCountLabel->setAnchorPoint(ccp(0.0f, 1.0f));
                break;
            }
            case 3: {
                killCountLabel->setPosition(labelBuffer, labelBuffer);
                killCountLabel->setAnchorPoint(ccp(0.0f, 0.0f));
                break;
            }
            case 4: {
                killCountLabel->setPosition(winSize.width - labelBuffer, labelBuffer);
                killCountLabel->setAnchorPoint(ccp(1.0f, 0.0f));
                break;
            }
        }

        if (mod->getSettingValue<bool>("chroma")) {
            auto speed = mod->getSettingValue<float>("chroma-speed");
            auto rgbtqiaplus16mcolultra4khd = CCRepeatForever::create(CCSequence::create(
                CCTintTo::create(speed, 255, 128, 128), CCTintTo::create(speed, 255, 255, 128),
                CCTintTo::create(speed, 128, 255, 128), CCTintTo::create(speed, 128, 255, 255),
                CCTintTo::create(speed, 128, 128, 255), CCTintTo::create(speed, 255, 128, 255),
            nullptr));
            killCountLabel->runAction(rgbtqiaplus16mcolultra4khd);
        }

        return true;
    }

    void destroyPlayer() {
        MenuGameLayer::destroyPlayer();
        updateKillCountLabel();
    }

    void updateKillCountLabel() {
        if (auto label = m_fields->killCountLabel) {
            label->setString((m_fields->labelPrefix + std::to_string(GameStatsManager::get()->getStat("9"))).c_str());
        }
    }
};