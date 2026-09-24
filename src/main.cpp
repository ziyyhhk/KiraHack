#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// ======================
// Global state
// ======================
bool g_noclip = false;
bool g_showHitboxes = false;
bool g_noDeathEffect = false;
float g_speedValue = 1.0f;
bool g_speedEnabled = false;

$on_mod(Loaded) {
    log::info("KiraHack v1.1.0-alpha loaded");

    // Load settings
    g_noclip = Mod::get()->getSettingValue<bool>("noclip");
    g_showHitboxes = Mod::get()->getSettingValue<bool>("show-hitboxes");
    g_noDeathEffect = Mod::get()->getSettingValue<bool>("no-death-effect");
    g_speedEnabled = Mod::get()->getSettingValue<bool>("speedhack-enabled");
    g_speedValue = Mod::get()->getSettingValue<double>("speedhack-value");
}

// ======================
// Noclip + Death handling
// ======================
class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        if (g_noclip) {
            // Simply skip the death
            return;
        }
        PlayLayer::destroyPlayer(player, obj);
    }

    void showNewBest(bool p0, int p1, int p2, bool p3, bool p4, bool p5) {
        if (g_noDeathEffect) return;
        PlayLayer::showNewBest(p0, p1, p2, p3, p4, p5);
    }

    void update(float dt) {
        // Apply speedhack by scaling delta time
        if (g_speedEnabled && g_speedValue != 1.0f) {
            dt *= g_speedValue;
        }
        PlayLayer::update(dt);
    }
};

// ======================
// FPS related
// ======================
class $modify(CCDirector) {
    void setAnimationInterval(double interval) {
        if (Mod::get()->getSettingValue<bool>("fps-unlock")) {
            int target = Mod::get()->getSettingValue<int64_t>("target-fps");
            if (target > 0) {
                interval = 1.0 / static_cast<double>(target);
            }
        }
        CCDirector::setAnimationInterval(interval);
    }
};

// ======================
// Simple MenuLayer hook (menu will be expanded)
// ======================
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Future: add KiraHack button here
        return true;
    }
};
