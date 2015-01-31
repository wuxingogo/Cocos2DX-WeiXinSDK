#include "HelloWorldScene.h"

USING_NS_CC;

#if ANDROID
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    
    auto friendItem = MenuItemImage::create("frend.png","frend.png",CC_CALLBACK_1(HelloWorld::friendCall, this));
    
    auto lineItem = MenuItemImage::create("call.png","call.png",CC_CALLBACK_1(HelloWorld::msgCall, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    friendItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/2 ));
    lineItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/2 - 100));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,lineItem,friendItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale( 2);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

void HelloWorld::msgCall(cocos2d::Ref *pSender){
    CCLOG("MSG call");
#if ANDROID
    callMsg();
#endif
}
void HelloWorld::friendCall(cocos2d::Ref *pSender){
    CCLOG("Friend call");
#if ANDROID
    callFri();
#endif
}

void HelloWorld::callFri(){
#if ANDROID
    cocos2d::JniMethodInfo minfo;
    
    jobject jobj;
    
    if (!cocos2d::JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "callFriend", "(I)V"))
        return;
    
    jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    
    if (!cocos2d::JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "callFriend", "(I)V"))
        return;
    minfo.env->CallVoidMethod(jobj, minfo.methodID, 1);
#endif
}

void HelloWorld::callMsg(){
#if ANDROID
    cocos2d::JniMethodInfo minfo;
    
    jobject jobj;
    
    if (!cocos2d::JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "callMsg", "(I)V"))
        return;
    
    jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    
    if (!cocos2d::JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "callMsg", "(I)V"))
        return;
    minfo.env->CallVoidMethod(jobj, minfo.methodID, 1);
#endif
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
