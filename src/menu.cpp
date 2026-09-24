#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

// Simple tab enum matching our design
enum class KiraTab {
    Core,
    Protection,
    Editor,
    Visual,
    Gameplay,
    Info,
    Global,
    Safety,
    Screen,
    Tools,
    Replay
};

static bool g_menuOpen = false;
static KiraTab g_currentTab = KiraTab::Core;

// Very lightweight menu layer (will be expanded)
class KiraMenuLayer : public CCLayer {
public:
    static KiraMenuLayer* create() {
        auto ret = new KiraMenuLayer();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() override {
        if (!CCLayer::init()) return false;

        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // Dark background
        auto bg = CCLayerColor::create({0, 0, 0, 180});
        bg->setContentSize(winSize);
        this->addChild(bg);

        // Title
        auto title = CCLabelBMFont::create("KiraHack", "bigFont.fnt");
        title->setScale(0.7f);
        title->setPosition({winSize.width / 2, winSize.height - 40});
        this->addChild(title);

        // Simple tab buttons (placeholder layout)
        const char* tabNames[] = {
            "Core", "Protection", "Editor", "Visual", "Gameplay",
            "Info", "Global", "Safety", "Screen", "Tools", "Replay"
        };

        float startX = 80.f;
        float y = winSize.height - 90.f;

        for (int i = 0; i < 11; i++) {
            auto btn = CCMenuItemLabel::create(
                CCLabelBMFont::create(tabNames[i], "goldFont.fnt"),
                this,
                menu_selector(KiraMenuLayer::onTab)
            );
            btn->setTag(i);
            btn->setScale(0.45f);
            btn->setPosition({startX + (i % 6) * 90.f, y - (i / 6) * 35.f});

            auto menu = CCMenu::create(btn, nullptr);
            menu->setPosition({0, 0});
            this->addChild(menu);
        }

        // Close hint
        auto hint = CCLabelBMFont::create("Press TAB or ESC to close", "chatFont.fnt");
        hint->setScale(0.6f);
        hint->setPosition({winSize.width / 2, 30});
        this->addChild(hint);

        return true;
    }

    void onTab(CCObject* sender) {
        auto btn = static_cast<CCMenuItem*>(sender);
        g_currentTab = static_cast<KiraTab>(btn->getTag());
        log::info("Switched to tab {}", btn->getTag());
        // Later: refresh content for the selected tab
    }

    void keyBackClicked() override {
        this->removeFromParentAndCleanup(true);
        g_menuOpen = false;
    }
};

// Open / close menu with Tab key
class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool repeat) {
        if (down && !repeat && key == KEY_Tab) {
            if (g_menuOpen) {
                // close handled by keyBackClicked
            } else {
                if (auto scene = CCDirector::sharedDirector()->getRunningScene()) {
                    auto menu = KiraMenuLayer::create();
                    scene->addChild(menu, 999);
                    g_menuOpen = true;
                }
            }
            return true;
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, repeat);
    }
};
