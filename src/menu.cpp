#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;

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

        auto bg = CCLayerColor::create({15, 15, 25, 210});
        bg->setContentSize(winSize);
        this->addChild(bg);

        auto title = CCLabelBMFont::create("KiraHack", "bigFont.fnt");
        title->setScale(0.6f);
        title->setPosition({winSize.width / 2.f, winSize.height - 40.f});
        this->addChild(title);

        auto info = CCLabelBMFont::create(
            "TAB Menu\n\nCore | Screen | etc.\n\nUnlock FPS / TPS / Hz settings available",
            "chatFont.fnt"
        );
        info->setAlignment(kCCTextAlignmentCenter);
        info->setScale(0.55f);
        info->setPosition({winSize.width / 2.f, winSize.height / 2.f});
        this->addChild(info);

        auto hint = CCLabelBMFont::create("Press ESC or TAB to close", "chatFont.fnt");
        hint->setScale(0.5f);
        hint->setPosition({winSize.width / 2.f, 30.f});
        this->addChild(hint);

        return true;
    }

    void keyBackClicked() override {
        this->removeFromParent();
        g_menuOpen = false;
    }
};

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool repeat) {
        if (down && !repeat && key == KEY_Tab) {
            if (!g_menuOpen) {
                if (auto scene = CCDirector::get()->getRunningScene()) {
                    if (auto menu = KiraMenuLayer::create()) {
                        scene->addChild(menu, 1000);
                        g_menuOpen = true;
                    }
                }
            }
            return true;
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, repeat);
    }
};
