#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;

enum class KiraTab {
    Core = 0,
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

        auto winSize = CCDirector::get()->getWinSize();

        auto bg = CCLayerColor::create({20, 20, 30, 200});
        bg->setContentSize(winSize);
        this->addChild(bg);

        auto title = CCLabelBMFont::create("KiraHack", "bigFont.fnt");
        title->setScale(0.65f);
        title->setPosition({winSize.width / 2.f, winSize.height - 35.f});
        this->addChild(title);

        // Tab labels
        const char* tabs[] = {
            "Core", "Protection", "Editor", "Visual", "Gameplay",
            "Info", "Global", "Safety", "Screen", "Tools", "Replay"
        };

        float x = 60.f;
        float y = winSize.height - 80.f;

        for (int i = 0; i < 11; ++i) {
            auto label = CCLabelBMFont::create(tabs[i], "goldFont.fnt");
            label->setScale(0.4f);
            label->setPosition({x + (i % 6) * 95.f, y - (i / 6) * 30.f});
            this->addChild(label);
        }

        // Screen / Display section hint
        auto info = CCLabelBMFont::create(
            "Screen tab: Unlock FPS, Physics TPS, VSync, Lock Delta",
            "chatFont.fnt"
        );
        info->setScale(0.55f);
        info->setPosition({winSize.width / 2.f, winSize.height / 2.f});
        this->addChild(info);

        auto hint = CCLabelBMFont::create("Press TAB or ESC to close", "chatFont.fnt");
        hint->setScale(0.55f);
        hint->setPosition({winSize.width / 2.f, 25.f});
        this->addChild(hint);

        return true;
    }

    void keyBackClicked() override {
        this->removeFromParentAndCleanup(true);
        g_menuOpen = false;
    }
};

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        if (isKeyDown && !isKeyRepeat && key == KEY_Tab) {
            if (!g_menuOpen) {
                if (auto scene = CCDirector::get()->getRunningScene()) {
                    auto menu = KiraMenuLayer::create();
                    if (menu) {
                        scene->addChild(menu, 999);
                        g_menuOpen = true;
                    }
                }
            }
            return true;
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};
