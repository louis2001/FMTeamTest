//
//  CSimulScene.h
//  FifaManager
//
//  Created by louis on 13. 1. 21..
//
//

#ifndef __FifaManager__CSimulScene__
#define __FifaManager__CSimulScene__

#include "FMScene.h"
#include "FmP3D.h"
#include "FmBall.h"

USING_NS_CC;

class CSimulScene : public FMScene
{
public:
    virtual void runScene();
    
    void LoadResources();
};

class CSimul : public CCLayer
{
protected:
    CCSprite*   m_pBack;
    CCSprite*   m_pGround;
    
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual void draw();

    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};

//게임 진행 화면 클래스
class CGameBoard : public CCLayer
{
protected:
    CCSprite*   m_pGround;
    FmP2D       m_sLineData[14];
    
    CFmBall*    m_pBall;
    CCSprite*   m_pBallShadow;
    
    CCPoint     prevlocation;
    
    bool        btestpressed;
    float       angle;
    FmP3D       befball;
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual void draw();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
    {
        CCTouch *touch = (CCTouch*)(pTouches->anyObject());
        CCPoint location = touch->getLocation();
        CCPoint prev;
        prev.x =  this->getPosition().x + m_pBall->m_pPos->GetDD().nX;
        prev.y =  this->getPosition().y + m_pBall->m_pPos->GetDD().nY;
        
        angle = 90+CC_RADIANS_TO_DEGREES(atan2(-(location.y-prev.y), location.x-prev.x));
        btestpressed = true;
        befball = *m_pBall->m_pPos;
    }
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};

class CTestBoard : public CCLayer
{
protected:
    float m_Tx = 0;
    float m_Ty = 0;
    float m_Tz = 0;
    
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual void draw();
    
    FmP2D GetScreenPoint(int x, int y, int z);
};

#endif /* defined(__FifaManager__CSimulScene__) */
