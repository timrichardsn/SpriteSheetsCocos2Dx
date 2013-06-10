#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) return false;
    return true;
}

void HelloWorld::onEnter() {
    CCLayerColor::onEnter();
    
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("Goober.plist");
    
    CCSpriteBatchNode* spritesheet = CCSpriteBatchNode::create("Goober.png");
    this->addChild(spritesheet);
    
    CCArray* gooberFrames = new CCArray;
    for(int i = 1; i <= 16; i++) {
        CCString* filename = CCString::createWithFormat("goober%d.png", i);
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
        gooberFrames->addObject(frame);
    }
    
    CCAnimation* runAnim = CCAnimation::createWithSpriteFrames(gooberFrames, 0.1);
    CCSprite* goober = CCSprite::createWithSpriteFrameName("goober1.png");
    
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    goober->setPosition(ccp(winsize.width*0.5, winsize.height*0.5));
    
    CCAction* action = CCRepeatForever::create(CCAnimate::create(runAnim));
    
    goober->runAction(action);
    spritesheet->addChild(goober);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
