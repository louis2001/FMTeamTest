//
//  FifaHeroesAppDelegate.cpp
//  FifaHeroes
//
//  Created by louis on 13. 1. 16..
//  Copyright __MyCompanyName__ 2013년. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "CTitleScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(CCEGLView::sharedOpenGLView()->getFrameSize().height == 1136)
    {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(VIEW_WIDTH, VIEW_HEIGHT, kResolutionNoBorder);
    }
    else
    {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(VIEW_WIDTH, VIEW_HEIGHT, kResolutionShowAll);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(VIEW_WIDTH, VIEW_HEIGHT, kResolutionNoBorder);
#endif

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    
    // create a scene. it's an autorelease object
//    CCScene *pScene = HelloWorld::scene();

    // run
//    pDirector->runWithScene(pScene);
    
    CTitleScene* pScene = new CTitleScene();
    pScene->LoadResources();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
