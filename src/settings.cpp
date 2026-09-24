#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Listen for setting changes so features update live
$execute {
    listenForSettingChanges("noclip", [](bool value) {
        // Global is updated on next load / we can expand this
        log::debug("Noclip set to {}", value);
    });

    listenForSettingChanges("speedhack-enabled", [](bool value) {
        log::debug("Speedhack enabled: {}", value);
    });

    listenForSettingChanges("show-hitboxes", [](bool value) {
        log::debug("Show Hitboxes: {}", value);
    });
}
