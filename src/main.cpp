#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

namespace Kira {
    bool noclip = false;
    bool speedEnabled = false;
    float speedValue = 1.0f;
    bool unlockFps = false;
    int targetFps = 240;
}

$on_mod(Loaded) {
    log::info("KiraHack 1.3.0-alpha loaded");

    auto mod = Mod::get();
    Kira::noclip = mod->getSettingValue<bool>("noclip");
    Kira::speedEnabled = mod->getSettingValue<bool>("speedhack-enabled");
    Kira::speedValue = static_cast<float>(mod->getSettingValue<double>("speedhack-value"));
    Kira::unlockFps = mod->getSettingValue<bool>("unlock-fps");
    Kira::targetFps = static_cast<int>(mod->getSettingValue<int64_t>("target-fps"));
}

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        if (Kira::noclip) {
            return;
        }
        PlayLayer::destroyPlayer(player, obj);
    }

    void update(float dt) {
        if (Kira::speedEnabled && Kira::speedValue != 1.0f) {
            dt *= Kira::speedValue;
        }
        PlayLayer::update(dt);
    }
};

class $modify(CCDirector) {
    void setAnimationInterval(double value) {
        if (Kira::unlockFps && Kira::targetFps > 0) {
            value = 1.0 / static_cast<double>(Kira::targetFps);
        }
        CCDirector::setAnimationInterval(value);
    }
};

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }
        log::debug("KiraHack MenuLayer ready");
        return true;
    }
};
