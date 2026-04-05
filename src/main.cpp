#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <fstream>
#include <ctime>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
public:
    static FLAlertLayer* savedAlert;
    static std::string currentBundle;

    bool init() {
        if (!MenuLayer::init()) return false;

        // Nút Installer
        auto installerBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
            this,
            menu_selector(MyMenuLayer::onInstallerButton)
        );
        installerBtn->setID("installer-button");

        auto menu = this->getChildByID("bottom-menu");
        auto geodeBtn = menu->getChildByID("geode-button");
        if (geodeBtn) {
            auto pos = geodeBtn->getPosition();
            installerBtn->setPosition({pos.x + 50, pos.y});
        }

        menu->addChild(installerBtn);
        menu->updateLayout();
        return true;
    }

    // Popup nhập key
    void onInstallerButton(CCObject*) {
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto alert = FLAlertLayer::create(
            nullptr,
            "Super Hack Installer",
            "Please enter your license key below:",
            "Cancel",
            "Confirm"
        );

        auto input = CCTextInputNode::create(200, 40, "Enter key", "chatFont.fnt");
        input->setPosition({winSize.width / 2, winSize.height / 2 - 50});
        alert->addChild(input, 1, 999);

        // m_button2 là CCMenuItemSpriteExtra → có setTarget

auto installerBtn = CCMenuItemSpriteExtra::create(
    ButtonSprite::create(
        "Install",
        "bigFont.fnt",
        "GJ_button_01.png", // background sprite
        1.0f                // scale chữ
    ),
    this,
    menu_selector(MyMenuLayer::onInstallerButton)
);




   
        alert->show();

        savedAlert = alert;
    }

    // Xác nhận key
    void onConfirmKey(CCObject*) {
        auto input = static_cast<CCTextInputNode*>(savedAlert->getChildByTag(999));
        std::string key = input->getString();

        std::vector<std::string> validKeys = {
            "TEST123", "VIP456", "ULTIMATE789", "NeonGD1667"
        };

        if (std::find(validKeys.begin(), validKeys.end(), key) != validKeys.end()) {
            logAction("Entered valid key: " + key);

            auto bundleAlert = FLAlertLayer::create(
                nullptr,
                "Choose Bundle",
                "Select which bundle to install:",
                "Cancel",
                nullptr
            );

            auto menu = CCMenu::create();

            auto btnBasic = CCMenuItemFont::create("Basic");
            btnBasic->setTarget(this, menu_selector(MyMenuLayer::onSelectBasic));

            auto btnPro = CCMenuItemFont::create("Pro");
            btnPro->setTarget(this, menu_selector(MyMenuLayer::onSelectPro));

            auto btnUltimate = CCMenuItemFont::create("Ultimate");
            btnUltimate->setTarget(this, menu_selector(MyMenuLayer::onSelectUltimate));

            menu->addChild(btnBasic);
            menu->addChild(btnPro);
            menu->addChild(btnUltimate);

            menu->alignItemsVerticallyWithPadding(10);
            menu->setPosition({CCDirector::sharedDirector()->getWinSize().width / 2,
                               CCDirector::sharedDirector()->getWinSize().height / 2 - 40});

            bundleAlert->addChild(menu);
            bundleAlert->show();
        } else {
            FLAlertLayer::create("Error", "Invalid license key!", "OK")->show();
        }
    }

    void onSelectBasic(CCObject*) { showInstallProgress("Basic"); }
    void onSelectPro(CCObject*) { showInstallProgress("Pro"); }
    void onSelectUltimate(CCObject*) { showInstallProgress("Ultimate"); }

    void updateProgress(CCNode* sender) {
        auto label = static_cast<CCLabelBMFont*>(sender->getChildByTag(1000));
        auto barFill = static_cast<CCSprite*>(sender->getChildByTag(2000));

        std::string text = label->getString();
        int percent = 0;
        if (!text.empty()) {
            percent = std::stoi(text.substr(0, text.find("%")));
        }

        percent += 10;
        if (percent > 100) percent = 100;

        label->setString((std::to_string(percent) + "%").c_str());
        barFill->setScaleX(3.0f * (percent / 100.0f));

        if (percent == 100) {
            FLAlertLayer::create("Success", currentBundle + " bundle installed!", "OK")->show();
            logAction("Installed bundle: " + currentBundle);
        }
    }

    static void showInstallProgress(const std::string& bundleName) {
        currentBundle = bundleName;

        auto alert = FLAlertLayer::create(
            nullptr,
            "Installing...",
            "Installing " + bundleName + " bundle...\nPlease wait.",
            nullptr,
            nullptr
        );

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto label = CCLabelBMFont::create("0%", "chatFont.fnt");
        label->setPosition({winSize.width / 2, winSize.height / 2 + 40});
        alert->addChild(label, 1, 1000);

        auto barBg = CCSprite::create("square01_001.png");
        barBg->setScaleX(3.0f);
        barBg->setScaleY(0.5f);
        barBg->setColor({100, 100, 100});
        barBg->setPosition({winSize.width / 2, winSize.height / 2});
        alert->addChild(barBg);

        auto barFill = CCSprite::create("square01_001.png");
        barFill->setScaleX(0.0f);
        barFill->setScaleY(0.5f);
        barFill->setColor({0, 255, 0});
        barFill->setPosition({winSize.width / 2, winSize.height / 2});
        alert->addChild(barFill, 1, 2000);

        alert->show();

        int steps = 10;
        float interval = 0.5f;

        for (int i = 1; i <= steps; i++) {
            auto delay = CCDelayTime::create(interval * i);
            auto update = CCCallFuncN::create(alert, callfuncN_selector(MyMenuLayer::updateProgress));
            auto seq = CCSequence::create(delay, update, nullptr);
            alert->runAction(seq);
        }
    }

    static void logAction(const std::string& text) {
        std::ofstream logFile("installer.log", std::ios::app);
        if (logFile.is_open()) {
            std::time_t now = std::time(nullptr);
            char buf[64];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            logFile << "[" << buf << "] " << text << std::endl;
            logFile.close();
        }
    }
};

FLAlertLayer* MyMenuLayer::savedAlert = nullptr;
std::string MyMenuLayer::currentBundle = "";
