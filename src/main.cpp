
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/Popup.hpp>

using namespace geode::prelude;

// =====================================
// POPUP
// =====================================

class SuperHackPopup : public geode::Popup {
protected:
    bool init() {
        if (!Popup::init(360.f, 220.f))
            return false;

        this->setTitle("SUPER HACK INSTALLER");

        auto label = CCLabelBMFont::create(
            "Super Hack Menu Ready To Install",
            "goldFont.fnt"
        );

        label->setScale(0.45f);
        label->setPosition(
            m_size.width / 2,
            m_size.height / 2 + 10.f
        );

        m_mainLayer->addChild(label);

        auto footer = CCLabelBMFont::create(
            "Made by Homeless Team & NeonGD",
            "chatFont.fnt"
        );

        footer->setScale(0.45f);
        footer->setPosition(
            m_size.width / 2,
            20.f
        );

        m_mainLayer->addChild(footer);

        return true;
    }

public:
    static SuperHackPopup* create() {
        auto ret = new SuperHackPopup();

        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};

// =====================================
// MENU BUTTON
// =====================================

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto bottomMenu = this->getChildByID("bottom-menu");

        if (!bottomMenu)
            return true;

        auto sprite = CCSprite::create(
            (Mod::get()->getResourcesDir() / "SUPERHACK_LOGO.png").string().c_str()
        );

        if (!sprite) {
            log::error("Failed to load SUPERHACK_LOGO.png");
            return true;
        }

        sprite->setScale(0.35f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MyMenuLayer::onSuperHack)
        );

        button->setID("superhack-button");

        bottomMenu->addChild(button);
        bottomMenu->updateLayout();

        return true;
    }

    void onSuperHack(CCObject*) {
        SuperHackPopup::create()->show();
    }
};

