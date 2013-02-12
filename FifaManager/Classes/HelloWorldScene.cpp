#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC_EXT;

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
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width-45 - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    
    
    // test code
    // 배경화면
    CCSprite* pSpriteBack = CCSprite::create("test.png");
    
    // position the sprite on the center of the screen
    pSpriteBack->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSpriteBack, 0);
    
    // 시작화면
//    CCSprite* pSpriteStart = CCSprite::create("q_start.jpg");
    
    // position the sprite on the center of the screen
//    pSpriteStart->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
//    this->addChild(pSpriteStart, 0);
    
    

    
    
    
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    //CCDirector::sharedDirector()->end();

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
//    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//    CCBReader* reader = new CCBReader(ccNodeLoaderLibrary);
//    CCScene* scene = reader->createSceneWithNodeGraphFromFile("TeLabels.ccbi");
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(2.0f, scene));
CCLog("1");
    
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    CCLog("2");
    CCBReader* reader = new CCBReader(ccNodeLoaderLibrary);
    CCLog("3");
    CCNode* scene = reader->readNodeGraphFromFile("TestLabels.ccbi");
    CCLog("4");
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    scene->setPosition(ccp(size.width/2, size.height/2));
                                                  if(scene != NULL)
                                                  {
                                                      this->addChild(scene, 2);
                                                      scene->release();
                                                  }
    CCLog("5");
//#endif
}
