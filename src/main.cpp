#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

// ======================
// Global state (synced with settings)
// ======================
namespace Kira {
    bool noclip = false;
    bool showHitboxes = false;
    bool noDeathEffect = false;
    bool speedEnabled = false;
    float speedValue = 1.0f;
    bool fpsUnlock = false;
    int targetFps = 240;
}

$on_mod(Loaded) {
    log::info("KiraHack loaded - menu available with TAB key");

    Kira::noclip = Mod::get()->getSettingValue<bool>("noclip");
    Kira::showHitboxes = Mod::get()->getSettingValue<bool>("show-hitboxes");
    Kira::noDeathEffect = Mod::get()->getSettingValue<bool>("no-death-effect");
    Kira::speedEnabled = Mod::get()->getSettingValue<bool>("speedhack-enabled");
    Kira::speedValue = static_cast<float>(Mod::get()->getSettingValue<double>("speedhack-value"));
    Kira::fpsUnlock = Mod::get()->getSettingValue<bool>("fps-unlock");
    Kira::targetFps = static_cast<int>(Mod::get()->getSettingValue<int64_t>("target-fps"));
}

// ======================
// Core gameplay hooks
// ======================
class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        if (Kira::noclip) {
            return; // skip death
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

// FPS unlock
class $modify(CCDirector) {
    void setAnimationInterval(double interval) {
        if (Kira::fpsUnlock && Kira::targetFps > 0) {
            interval = 1.0 / static_cast<double>(Kira::targetFps);
        }
        CCDirector::setAnimationInterval(interval);
    }
};
