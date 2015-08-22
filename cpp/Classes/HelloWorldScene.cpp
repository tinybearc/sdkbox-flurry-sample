#include "HelloWorldScene.h"
#include "PluginFlurryAnalytics/PluginFlurryAnalytics.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    FileUtils::getInstance()->addSearchPath("fonts");
    
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    std::string defaultFont("arial.ttf");
    int defaultFontSize = 32;
    
    auto eventItem = MenuItemLabel::create(Label::createWithTTF("Log Event", defaultFont, defaultFontSize),
                                           CC_CALLBACK_1(HelloWorld::onEvent, this));
    
    auto menu = Menu::create(eventItem, NULL);
    menu->setPosition(Vec2(size.width/2, size.height/2));
    addChild(menu);
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + size.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto cl_menu = Menu::create(closeItem, NULL);
    cl_menu->setPosition(Vec2::ZERO);
    this->addChild(cl_menu, 1);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onEvent(cocos2d::Ref *sender)
{
    CCLOG("Log Event");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sdkbox::PluginFlurryAnalytics::logEvent("Test Event iOS");
#else
    sdkbox::PluginFlurryAnalytics::logEvent("Test Event Android");
#endif
}
