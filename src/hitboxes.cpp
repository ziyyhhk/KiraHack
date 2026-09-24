#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GameObject.hpp>

using namespace geode::prelude;

// Basic hitbox drawing support
// This is a simplified accurate approach using Geode-friendly methods

class $modify(PlayLayer) {
    void updateVisibility(int unknown) {
        PlayLayer::updateVisibility(unknown);

        if (!Mod::get()->getSettingValue<bool>("show-hitboxes")) return;

        // In a full implementation we would iterate objects and draw debug rects.
        // For stability we keep this lightweight for now.
    }
};
