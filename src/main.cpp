#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Simple entry point for now
$on_mod(Loaded) {
    log::info("KiraHack loaded successfully!");
}

// Example: add a button or open menu later
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Placeholder - menu system will be added next
        log::debug("KiraHack: MenuLayer ready");

        return true;
    }
};
