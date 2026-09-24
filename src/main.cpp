#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

namespace Kira {
    bool noclip = false;
    bool speedEnabled = false;
    float speedValue = 1.0f;
    bool fpsUnlock = false;
    int targetFps = 240;
    bool verticalSync = false;
    bool lockDelta = false;
}

$on_mod(Loaded) {
    log::info("KiraHack 1.2.1-alpha loaded");

    auto mod = Mod::get();
    Kira::noclip = mod->getSettingValue<bool>("noclip");
    Kira::speedEnabled = mod->getSettingValue<bool>("speedhack-enabled");
    Kira::speedValue = static_cast<float>(mod->getSettingValue<double>("speedhack-value"));
    Kira::fpsUnlock = mod->getSettingValue<bool>("fps-unlock");
    Kira::targetFps = static_cast<int>(mod->getSettingValue<int64_t>("target-fps"));
    Kira::verticalSync = mod->getSettingValue<bool>("vertical-sync");
    Kira::lockDelta = mod->getSettingValue<bool>("lock-delta");
}

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        if (Kira::noclip) return;
        PlayLayer::destroyPlayer(player, obj);
    }

    void update(float dt) {
        if (Kira::speedEnabled && Kira::speedValue != 1.0f) {
            dt *= Kira::speedValue;
        }
        if (Kira::lockDelta) {
            // simple lock to fixed step for stability testing
            dt = 1.0f / 240.0f;
        }
        PlayLayer::update(dt);
    }
};

class $modify(CCDirector) {
    void setAnimationInterval(double interval) {
        if (Kira::fpsUnlock && Kira::targetFps > 0) {
            interval = 1.0 / static_cast<double>(Kira::targetFps);
        }
        CCDirector::setAnimationInterval(interval);
    }
};
