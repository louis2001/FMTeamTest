//
//  CTitleScene.h
//  FifaManager
//
//  Created by louis on 13. 1. 21..
//
//

#ifndef __FifaManager__CTitleScene__
#define __FifaManager__CTitleScene__

#include "FMScene.h"
#include "FmP3D.h"

USING_NS_CC;

class CTitleScene : public FMScene
{
public:
    virtual void runScene();
    
    void LoadResources();
};

class CTitle : public CCLayer
{
protected:
    CCSprite*   m_pBack;
    
    FmP2D m_sLineData[4];
    
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    void animationHasEnded(CCNotificationObserver* noti);
    void animationHasEndedRep(CCNotificationObserver* noti);
    void animationHasChanged(CCNotificationObserver* noti);
};

#endif /* defined(__FifaManager__CTitleScene__) */
