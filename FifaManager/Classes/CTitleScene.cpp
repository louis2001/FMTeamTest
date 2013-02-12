//
//  CTitleScene.cpp
//  FifaManager
//
//  Created by louis on 13. 1. 21..
//
//

#include "CTitleScene.h"
#include "SpriteHelperLoader.h"
#include "LHAnimationNode.h"
#include "FmP3D.h"

void CTitleScene::LoadResources()
{
    CTitle* pLayer = new CTitle();
    this->addChild(pLayer);
    
    
}

void CTitleScene::runScene()
{
    LoadResources();
    
    CCDirector::sharedDirector()->replaceScene(this);
}



void CTitle::onEnter()
{
    CCLayer::onEnter();
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 배경화면
    m_pBack = CCSprite::create("q_start.jpg");
    
    // position the sprite on the center of the screen
    m_pBack->setPosition( ccp(size.width/2, size.height/2) );
    
 //   m_pBack->setScale(0.5);
    
    // add the sprite as a child to this layer
    addChild(m_pBack, 0);
    
    float eyex, eyey, eyez, cenx, ceny, cenz, upx, upy, upz;
    m_pBack->getCamera()->getEyeXYZ(&eyex, &eyey, &eyez);
    m_pBack->getCamera()->getCenterXYZ(&cenx, &ceny, &cenz);
    m_pBack->getCamera()->getUpXYZ(&upx, &upy, &upz);
    
    
    CCSprite* pSprite = CCSprite::create("testsprite_player.png");
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    addChild(pSprite,1);
    
    LHSprite* pLHSprite = LHSprite::spriteWithName("ani_1_1", "player", "testsprite.pshs");
    pLHSprite->setPosition( ccp(size.width/2, size.height/3) );
    addChild(pLHSprite, 2);
    
    //Set up notifications for all animations or per sprite by passing the sprite to the object argument
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CTitle::animationHasEnded),
                                                                  LHAnimationHasEndedNotification,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CTitle::animationHasEndedRep),
                                                                  LHAnimationHasEndedAllRepetitionsNotification,
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CTitle::animationHasChanged),
                                                                  LHAnimationFrameNotification,
                                                                  NULL);;
    
    
    pLHSprite->prepareAnimationNamed("ani_left", "testsprite.pshs");
    pLHSprite->playAnimation();

    setTouchEnabled(true);
}

void CTitle::onExit()
{
    m_pBack->release();
    
    CCLayer::onExit();
}

void CTitle::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    FMScene* pFMScene = (FMScene*)getParent();
    pFMScene->SetState(FMSCENE_SIMUL);
}

void CTitle::animationHasEnded(CCNotificationObserver* noti)
{
    LHSprite* pLHSprite = (LHSprite*)noti->getObject();
}

void CTitle::animationHasEndedRep(CCNotificationObserver* noti)
{
    LHSprite* pLHSprite = (LHSprite*)noti->getObject();
}

void CTitle::animationHasChanged(CCNotificationObserver* noti)
{
    LHSprite* pLHSprite = (LHSprite*)noti->getObject();
}