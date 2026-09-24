#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
    log::info("KiraHack 1.3.3-alpha loaded");
}

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        if (Mod::get()->getSettingValue<bool>("noclip")) {
            return;
        }
        PlayLayer::destroyPlayer(player, obj);
    }

    void update(float dt) {
        if (Mod::get()->getSettingValue<bool>("speedhack-enabled")) {
            float mult = static_cast<float>(Mod::get()->getSettingValue<double>("speedhack-value"));
            if (mult != 1.0f) {
                dt *= mult;
            }
        }
        PlayLayer::update(dt);
    }
};

class $modify(CCDirector) {
    void setAnimationInterval(double value) {
        if (Mod::get()->getSettingValue<bool>("unlock-fps")) {
            int fps = static_cast<int>(Mod::get()->getSettingValue<int64_t>("fps"));
            if (fps > 0) {
                value = 1.0 / static_cast<double>(fps);
            }
        }
        CCDirector::setAnimationInterval(value);
    }
};
