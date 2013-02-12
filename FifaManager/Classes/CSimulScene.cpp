//
//  CSimulScene.cpp
//  FifaManager
//
//  Created by louis on 13. 1. 21..
//
//

#include "CSimulScene.h"
#include "cocos-ext.h"
#include "Config.h"
#include "GameDef.h"

USING_NS_CC_EXT;

void CSimulScene::LoadResources()
{
    CSimul* pLayer = new CSimul();
    this->addChild(pLayer);
    
    CGameBoard* pLayerBoard = new CGameBoard();
    pLayerBoard->setAnchorPoint(ccp(0.5f,0.5f));
    
// 실제비율 대조를 위한 로직에 사용되는 배율
    pLayerBoard->setPosition(ccp(LCD_WIDTH/2, LCD_HEIGHT/2+130));
//    pLayerBoard->setScale(363.0f/1458);

// 게임내에 사용되는 배율
//    pLayerBoard->setPosition(ccp(LCD_WIDTH/2, LCD_HEIGHT/2+LCD_HEIGHT/4-120));
   
    this->addChild(pLayerBoard);
    
  
//테스트용
//    CTestBoard* pTestBoard = new CTestBoard();
//    pTestBoard->ignoreAnchorPointForPosition(true);
//    pTestBoard->setAnchorPoint(ccp(0.5, 0.5));
//    pTestBoard->setPosition(ccp(LCD_WIDTH/2, LCD_HEIGHT/2));
   
//    addChild(pTestBoard, 2);
}

void CSimulScene::runScene()
{
    LoadResources();
    
    CCDirector::sharedDirector()->replaceScene( CCTransitionShrinkGrow::create(0.5, this) );
}

void CSimul::onEnter()
{
    CCLayer::onEnter();
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 배경화면
    m_pBack = CCSprite::create("q_play_sam.png");
    
    // position the sprite on the center of the screen
    m_pBack->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    addChild(m_pBack, 0);
    
    
    m_pGround = CCSprite::create("ground_sam.png");
    
    m_pGround->setAnchorPoint(ccp(0.5f, 0.5f));
    
    m_pGround->setPosition(ccp(LCD_WIDTH/2, LCD_HEIGHT/2+130));
    
//    m_pGround->setOpacity(182);
    
    addChild(m_pGround, 1);
    
    setTouchEnabled(true);
}

void CSimul::onExit()
{
    m_pBack->release();
    
    CCLayer::onExit();
}

void CSimul::draw()
{
    
}

void CSimul::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{	
//    FMScene* pFMScene = (FMScene*)getParent();
//    pFMScene->SetState(FMSCENE_TITLE);
    
    //m_pBall->Force(0, 0, (-1 + 2*(rand()%2))*rand()%360, INT_TO_FIXED(10), INT_TO_FIXED(5), 0);
//    m_pBall->Force(0, 0, 90, INT_TO_FIXED(10), INT_TO_FIXED(5), 0);
/*    CCLog("1");
    
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
    CCLog("5");*/

}

void CGameBoard::onEnter()
{
    CCLayer::onEnter();
 
    m_pBall = new CFmBall();
    if (m_pBall && m_pBall->initWithFile("ball_01.png"))
    {
        m_pBall->autorelease();
    }
    m_pBall->setAnchorPoint(ccp(0.5f, 0.0f));	

    addChild(m_pBall, 2);
    
    m_pBallShadow = CCSprite::create("ball_01.png");
    
    ccBlendFunc bf;
    bf.src = GL_SRC_COLOR;
    bf.dst = GL_ONE;
    
    m_pBallShadow->setBlendFunc(bf);
    
    addChild(m_pBallShadow, 1);
    
    setTouchEnabled(true);
}

void CGameBoard::onExit()
{
    m_pBall->release();
    
    CCLayer::onExit();
}

void CGameBoard::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    //: 좌표를 가져올 임의 터치를 추출합니다.
    CCTouch *touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    CCPoint prev;
    prev.x =  this->getPosition().x + m_pBall->m_pPos->GetDD().nX;
    prev.y =  this->getPosition().y + m_pBall->m_pPos->GetDD().nY;
    
    angle = 90+CC_RADIANS_TO_DEGREES(atan2(-(location.y-prev.y), location.x-prev.x));
}

void CGameBoard::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    //: 좌표를 가져올 임의 터치를 추출합니다.
    CCTouch *touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    
   prevlocation.x =  this->getPosition().x + m_pBall->m_pPos->GetDD().nX;
   prevlocation.y =  this->getPosition().y + m_pBall->m_pPos->GetDD().nY;
    
    angle = 90+CC_RADIANS_TO_DEGREES(atan2(-(location.y-prevlocation.y), location.x-prevlocation.x));
    
    //m_pBall->Force(0, 0, (-1 + 2*(rand()%2))*rand()%360, INT_TO_FIXED(10), INT_TO_FIXED(5), 0);
    m_pBall->Force(0, 0, 90+CC_RADIANS_TO_DEGREES(atan2(-(location.y-prevlocation.y), location.x-prevlocation.x)), INT_TO_FIXED(20), INT_TO_FIXED(30), 0);
    
    btestpressed = false;
}

void CGameBoard::draw()
{
    m_pBall->CheckSideFence();
    m_pBall->CheckUpperFence();
    m_pBall->Update();
    
    m_pBall->setPosition(ccp(m_pBall->m_pPos->GetDD().nX, m_pBall->m_pPos->GetDD().nY));
    m_pBallShadow->setPosition(ccp(m_pBall->m_pPos->GetDD(false).nX, m_pBall->m_pPos->GetDD(false).nY));
    m_pBallShadow->setScale(0.8f - 0.3f*m_pBall->m_pPos->GetTrZ()/300);
    m_pBall->setScale(1.0f + 0.3f*m_pBall->m_pPos->GetTrZ()/300);
    
    m_sLineData[0] = FmDDPermil(0, -1000);		//운동장 라인 좌표 미리 계산(12*4byte 써서 계산은 1번만 하자)
	m_sLineData[1] = FmDDPermil(0, 1000);
	m_sLineData[2] = FmDDPermil(1000, 1000);
	m_sLineData[3] = FmDDPermil(1000, -1000);
	m_sLineData[4] = FmDDPermil(PENALTY_AREA_X, -PENALTY_AREA_Y);		// 페널티 하단 좌표
	m_sLineData[5] = FmDDPermil(PENALTY_AREA_X, PENALTY_AREA_Y);		// 페널티 상단 좌표
	m_sLineData[6] = FmDDPermil(1000, PENALTY_AREA_Y);					// 페널티 안족 상단
	m_sLineData[7] = FmDDPermil(1000, -PENALTY_AREA_Y);					// 페널티 안쪽 하단
	m_sLineData[8] = FmDDPermil(GOAL_AREA_X, -GOAL_AREA_Y);
	m_sLineData[9] = FmDDPermil(GOAL_AREA_X, GOAL_AREA_Y);
	m_sLineData[10] = FmDDPermil(1000, GOAL_AREA_Y);
	m_sLineData[11] = FmDDPermil(1000, -GOAL_AREA_Y);
	m_sLineData[12] = FmDDPermil(-SIDE_FENCE_DIS_X, -SIDE_FENCE_DIS_Y);
	m_sLineData[13] = FmDDPermil(SIDE_FENCE_DIS_X, -SIDE_FENCE_DIS_Y);
    
    m_sLineData[13] = FmDDPermil(0, -0);
        
    int a = m_sLineData[13].nY + m_sLineData[0].nY;
    int b = m_sLineData[13].nY + m_sLineData[1].nY;
    
    ccDrawColor4B(255,0,255,255);
    
    if(btestpressed || m_pBall->GetSpeed() > 0)
    {
        FmP2D tmp = befball.GetDD(false);
        FmP3D move = befball.GetMovePos(angle, INT_TO_FIXED(1000));
        FmP2D movetmp = move.GetDD(false);
        ccDrawLine( ccp(tmp.nX, tmp.nY), ccp(movetmp.nX, movetmp.nY) );
    }
    
    ccDrawLine( ccp(m_sLineData[13].nX+0, m_sLineData[13].nY+10), ccp(m_sLineData[13].nX+0, m_sLineData[13].nY-10) );
    ccDrawLine( ccp(m_sLineData[13].nX+10, m_sLineData[13].nY+0), ccp(m_sLineData[13].nX-10, m_sLineData[13].nY+0) );
    
    for (int i=0; i<12; i++)
	{
		if (i==6 || i==10) continue;
        
		if ((i & 3) == 3) {
			ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY), ccp(m_sLineData[i-3].nX, m_sLineData[i-3].nY) );
            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY), ccp(-m_sLineData[i-3].nX, m_sLineData[i-3].nY) );
		} else {
            ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY), ccp(m_sLineData[i+1].nX, m_sLineData[i+1].nY) );
			if (i != 0)
                ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY), ccp(-m_sLineData[i+1].nX, m_sLineData[i+1].nY) );
		}
        
//		if ((i & 3) == 3) {
//			ccDrawLine( ccp(+m_sLineData[i].nX, m_sLineData[i].nY+1), ccp(m_sLineData[i-3].nX, m_sLineData[i-3].nY+1) );
//            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY+1), ccp(-m_sLineData[i-3].nX, m_sLineData[i-3].nY+1) );
//		} else if (i == 1 || i == 5 || i == 9) {
//			ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY+1), ccp(m_sLineData[i+1].nX, m_sLineData[i+1].nY+1) );
//            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY+1), ccp(-m_sLineData[i+1].nX, m_sLineData[i+1].nY+1) );
//		} else {
//            ccDrawLine( ccp(+m_sLineData[i].nX+1, m_sLineData[i].nY), ccp(m_sLineData[i+1].nX+1, m_sLineData[i+1].nY) );
//			if (i != 0)
//                ccDrawLine( ccp(-m_sLineData[i].nX+1, m_sLineData[i].nY), ccp(-m_sLineData[i+1].nX+1, m_sLineData[i+1].nY) );
//		}
//        
//		if ((i & 3) == 3) {
//			ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY-1), ccp(m_sLineData[i-3].nX, m_sLineData[i-3].nY-1) );
//            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY-1), ccp(-m_sLineData[i-3].nX, m_sLineData[i-3].nY-1) );
//		} else if (i == 1 || i == 5 || i == 9) {
//			ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY-1), ccp(m_sLineData[i+1].nX, m_sLineData[i+1].nY-1) );
//            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY-1), ccp(-m_sLineData[i+1].nX, m_sLineData[i+1].nY-1) );
//		} else {
//            ccDrawLine( ccp(m_sLineData[i].nX-1, m_sLineData[i].nY), ccp(m_sLineData[i+1].nX-1, m_sLineData[i+1].nY) );
//            
//			if (i != 0)
//                ccDrawLine( ccp(-m_sLineData[i].nX-1, m_sLineData[i].nY), ccp(-m_sLineData[i+1].nX-1, m_sLineData[i+1].nY) );
//		}
	}
    
 //   CCPoint vertices2[] = { ccp(LCD_WIDTH/2, LCD_HEIGHT*3/4+35), ccp(30,230), ccp(50,200) };
 //   ccDrawPoly( vertices2, 3, true);
    
    int back = BACK_Y;

    FmP2D goal = FmDDPermil(-GOALPOST_X, 0);
    FmP2D goal1 = FmDDPermil(-1000, 0);
    FmP2D goal2 = FmDDPermil(-1000, GOALPOST_Y);
    FmP2D goal3 = FmDDPermil(-GOALPOST_X, GOALPOST_Y);
    FmP2D goal4 = FmDDPermil(-1000, -GOALPOST_Y);
    FmP2D goal5 = FmDDPermil(-GOALPOST_X, -GOALPOST_Y);
    
    FmP2D goalu2 = Fm2Dto3D(Fm2DPermil(-1000, GOALPOST_Y), INT_TO_FIXED(GOALPOST_Z)).GetDD();
    FmP2D goalu3 = Fm2Dto3D(Fm2DPermil(-GOALPOST_X, GOALPOST_Y), INT_TO_FIXED(GOALPOST_Z)).GetDD();
    FmP2D goalu4 = Fm2Dto3D(Fm2DPermil(-1000, -GOALPOST_Y), INT_TO_FIXED(GOALPOST_Z)).GetDD();
    FmP2D goalu5 = Fm2Dto3D(Fm2DPermil(-GOALPOST_X, -GOALPOST_Y), INT_TO_FIXED(GOALPOST_Z)).GetDD();
    
    ccDrawLine( ccp(goal.nX, goal.nY), ccp(goal1.nX, goal1.nY) );
    ccDrawLine( ccp(goal2.nX, goal2.nY), ccp(goal3.nX, goal3.nY) );
    ccDrawLine( ccp(goal4.nX, goal4.nY), ccp(goal5.nX, goal5.nY) );
    ccDrawLine( ccp(goal3.nX, goal3.nY), ccp(goal5.nX, goal5.nY) );
    
    ccDrawLine( ccp(goalu2.nX, goalu2.nY), ccp(goalu3.nX, goalu3.nY) );
    ccDrawLine( ccp(goalu2.nX, goalu2.nY), ccp(goalu4.nX, goalu4.nY) );
    ccDrawLine( ccp(goalu4.nX, goalu4.nY), ccp(goalu5.nX, goalu5.nY) );
    ccDrawLine( ccp(goalu3.nX, goalu3.nY), ccp(goalu5.nX, goalu5.nY) );
    
    ccDrawLine( ccp(goal2.nX, goal2.nY), ccp(goalu2.nX, goalu2.nY) );
    ccDrawLine( ccp(goal3.nX, goal3.nY), ccp(goalu3.nX, goalu3.nY) );
    ccDrawLine( ccp(goal4.nX, goal4.nY), ccp(goalu4.nX, goalu4.nY) );
    ccDrawLine( ccp(goal5.nX, goal5.nY), ccp(goalu5.nX, goalu5.nY) );
    
    ccDrawLine( ccp(-goal.nX, goal.nY), ccp(-goal1.nX, goal1.nY) );
    ccDrawLine( ccp(-goal2.nX, goal2.nY), ccp(-goal3.nX, goal3.nY) );
    ccDrawLine( ccp(-goal4.nX, goal4.nY), ccp(-goal5.nX, goal5.nY) );
    ccDrawLine( ccp(-goal3.nX, goal3.nY), ccp(-goal5.nX, goal5.nY) );
    
    ccDrawLine( ccp(-goalu2.nX, goalu2.nY), ccp(-goalu3.nX, goalu3.nY) );
    ccDrawLine( ccp(-goalu2.nX, goalu2.nY), ccp(-goalu4.nX, goalu4.nY) );
    ccDrawLine( ccp(-goalu4.nX, goalu4.nY), ccp(-goalu5.nX, goalu5.nY) );
    ccDrawLine( ccp(-goalu3.nX, goalu3.nY), ccp(-goalu5.nX, goalu5.nY) );
    
    ccDrawLine( ccp(-goal2.nX, goal2.nY), ccp(-goalu2.nX, goalu2.nY) );
    ccDrawLine( ccp(-goal3.nX, goal3.nY), ccp(-goalu3.nX, goalu3.nY) );
    ccDrawLine( ccp(-goal4.nX, goal4.nY), ccp(-goalu4.nX, goalu4.nY) );
    ccDrawLine( ccp(-goal5.nX, goal5.nY), ccp(-goalu5.nX, goalu5.nY) );
    
    glLineWidth(1);
    ccDrawColor4B(255,255,255,255);
    ccPointSize(1);
    
    ccDrawLine( ccp(0, 10), ccp(0, -10) );
    ccDrawLine( ccp(10, 0), ccp(-10, 0) );

}





void CTestBoard::onEnter()
{
    CCLayer::onEnter();
    
    //실제 비율 이미지와 대조를 위한 로직
    
     CCSprite* ptest = CCSprite::create("testmap3.png");
     
     ptest->setAnchorPoint(ccp(0.5f, 0.0f));
     
     ptest->setPosition(ccp(LCD_WIDTH/2, LCD_HEIGHT/2));
     
     float eyex = 0, eyey = 0, eyez = 0;
     float arc = CC_DEGREES_TO_RADIANS(-59.5);
     float DeltaX = 0,DeltaY = 0,DeltaZ = 0;
     ptest->getCamera()->getEyeXYZ(&eyex, &eyey, &eyez);
     int rotatetype = 2;
     
     switch(rotatetype)
     {
     case 0:
     // Z축에 의한 회전
     DeltaX =  ( eyex * cosf(arc) ) + ( eyey * sinf(arc) );
     DeltaY = -( eyex * sinf(arc) ) + ( eyey * cosf(arc) );
     DeltaZ = eyez;
     break;
     case 1:
     // Y축에 의한 회전
     DeltaX = ( eyex * cosf(arc) ) - ( eyez * sinf(arc) );
     DeltaY = eyey;
     DeltaZ = ( eyex * sinf(arc) ) + ( eyez * cosf(arc) );
     break;
     case 2:
     // X축에 의한 회전
     DeltaX = eyex;
     DeltaY =  ( eyey * cosf(arc) ) + ( eyez * sinf(arc) );
     DeltaZ = -( eyey * sinf(arc) ) + ( eyez * cosf(arc) );
     break;
     }
     
     ptest->getCamera()->setEyeXYZ(DeltaX,DeltaY,DeltaZ);
     
     ptest->setOpacity(126);
     
     addChild(ptest, 0);
    
    setTouchEnabled(true);
}

void CTestBoard::onExit()
{
    CCLayer::onExit();
}

void CTestBoard::draw()
{
    // Rotation
    m_Tx = 59.5;
    m_Ty = 0;
    m_Tz = 0;
    
    // Zoom
    float Zoom = 0;
    
    // Object
    float x[4] = {BACK_X, BACK_X, -BACK_X, -BACK_X};
    float y[4] = {BACK_Y*2, 0, BACK_Y*2, 0};
    float z[4] = {0, 0, 0, 0};
    
    ccDrawLine( ccp(x[0], y[0]), ccp(x[1], y[1]) );
    ccDrawLine( ccp(x[2], y[2]), ccp(x[3], y[3]) );
    ccDrawLine( ccp(x[0], y[0]), ccp(x[2], y[2]) );
    ccDrawLine( ccp(x[1], y[1]), ccp(x[3], y[3]) );
    
//    CCPoint a = GetScreenPoint(x[0], y[0], z[0]);
//    CCPoint b = GetScreenPoint(x[1], y[1], z[1]);
//    CCPoint c = GetScreenPoint(x[2], y[2], z[2]);
//    CCPoint d = GetScreenPoint(x[3], y[3], z[3]);
    
    ccDrawColor4B(255,0,255,255);
    
//    ccDrawLine( a, b );
//    ccDrawLine( c, d );
//    ccDrawLine( a, c );
//    ccDrawLine( b, d );
    
    FmP3D       m_sLineData1[14];
    
    m_sLineData1[0] = Fm3DPermil(0, -1000);		//운동장 라인 좌표 미리 계산(12*4byte 써서 계산은 1번만 하자)
	m_sLineData1[1] = Fm3DPermil(0, 1000);
	m_sLineData1[2] = Fm3DPermil(1000, 1000);
	m_sLineData1[3] = Fm3DPermil(1000, -1000);
	m_sLineData1[4] = Fm3DPermil(PENALTY_AREA_X, -PENALTY_AREA_Y);		// 페널티 하단 좌표
	m_sLineData1[5] = Fm3DPermil(PENALTY_AREA_X, PENALTY_AREA_Y);		// 페널티 상단 좌표
	m_sLineData1[6] = Fm3DPermil(1000, PENALTY_AREA_Y);					// 페널티 안족 상단
	m_sLineData1[7] = Fm3DPermil(1000, -PENALTY_AREA_Y);					// 페널티 안쪽 하단
	m_sLineData1[8] = Fm3DPermil(GOAL_AREA_X, -GOAL_AREA_Y);
	m_sLineData1[9] = Fm3DPermil(GOAL_AREA_X, GOAL_AREA_Y);
	m_sLineData1[10] = Fm3DPermil(1000, GOAL_AREA_Y);
	m_sLineData1[11] = Fm3DPermil(1000, -GOAL_AREA_Y);
	m_sLineData1[12] = Fm3DPermil(-SIDE_FENCE_DIS_X, -SIDE_FENCE_DIS_Y);
	m_sLineData1[13] = Fm3DPermil(SIDE_FENCE_DIS_X, -SIDE_FENCE_DIS_Y);

    FmP2D       m_sLineData[14];
    
    m_sLineData[0] = m_sLineData1[0].GetDD();//GetScreenPoint(m_sLineData1[0].GetTrX(), m_sLineData1[0].GetTrY()+BACK_Y, m_sLineData1[0].GetTrZ());
    m_sLineData[1] = m_sLineData1[1].GetDD();//GetScreenPoint(m_sLineData1[1].GetTrX(), m_sLineData1[1].GetTrY()+BACK_Y, m_sLineData1[1].GetTrZ());
    m_sLineData[2] = m_sLineData1[2].GetDD();//GetScreenPoint(m_sLineData1[2].GetTrX(), m_sLineData1[2].GetTrY()+BACK_Y, m_sLineData1[2].GetTrZ());
    m_sLineData[3] = m_sLineData1[3].GetDD();//GetScreenPoint(m_sLineData1[3].GetTrX(), m_sLineData1[3].GetTrY()+BACK_Y, m_sLineData1[3].GetTrZ());
    m_sLineData[4] = m_sLineData1[4].GetDD();//GetScreenPoint(m_sLineData1[4].GetTrX(), m_sLineData1[4].GetTrY()+BACK_Y, m_sLineData1[4].GetTrZ());
    m_sLineData[5] = m_sLineData1[5].GetDD();//GetScreenPoint(m_sLineData1[5].GetTrX(), m_sLineData1[5].GetTrY()+BACK_Y, m_sLineData1[5].GetTrZ());
    m_sLineData[6] = m_sLineData1[6].GetDD();//GetScreenPoint(m_sLineData1[6].GetTrX(), m_sLineData1[6].GetTrY()+BACK_Y, m_sLineData1[6].GetTrZ());
    m_sLineData[7] = m_sLineData1[7].GetDD();//GetScreenPoint(m_sLineData1[7].GetTrX(), m_sLineData1[7].GetTrY()+BACK_Y, m_sLineData1[7].GetTrZ());
    m_sLineData[8] = m_sLineData1[8].GetDD();//GetScreenPoint(m_sLineData1[8].GetTrX(), m_sLineData1[8].GetTrY()+BACK_Y, m_sLineData1[8].GetTrZ());
    m_sLineData[9] = m_sLineData1[9].GetDD();//GetScreenPoint(m_sLineData1[9].GetTrX(), m_sLineData1[9].GetTrY()+BACK_Y, m_sLineData1[9].GetTrZ());
    m_sLineData[10] = m_sLineData1[10].GetDD();//GetScreenPoint(m_sLineData1[10].GetTrX(), m_sLineData1[10].GetTrY()+BACK_Y, m_sLineData1[10].GetTrZ());
    m_sLineData[11] = m_sLineData1[11].GetDD();//GetScreenPoint(m_sLineData1[11].GetTrX(), m_sLineData1[11].GetTrY()+BACK_Y, m_sLineData1[11].GetTrZ());
    m_sLineData[12] = m_sLineData1[12].GetDD();//GetScreenPoint(m_sLineData1[12].GetTrX(), m_sLineData1[12].GetTrY()+BACK_Y, m_sLineData1[12].GetTrZ());
    m_sLineData[13] = m_sLineData1[13].GetDD();//GetScreenPoint(m_sLineData1[13].GetTrX(), m_sLineData1[13].GetTrY()+BACK_Y, m_sLineData1[13].GetTrZ());
    
  /*  m_sLineData[0] = FmDDPermil(0, -1000);		//운동장 라인 좌표 미리 계산(12*4byte 써서 계산은 1번만 하자)
	m_sLineData[1] = FmDDPermil(0, 1000);
	m_sLineData[2] = FmDDPermil(1000, 1000);
	m_sLineData[3] = FmDDPermil(1000, -1000);
	m_sLineData[4] = FmDDPermil(PENALTY_AREA_X, -PENALTY_AREA_Y);		// 페널티 하단 좌표
	m_sLineData[5] = FmDDPermil(PENALTY_AREA_X, PENALTY_AREA_Y);		// 페널티 상단 좌표
	m_sLineData[6] = FmDDPermil(1000, PENALTY_AREA_Y);					// 페널티 안족 상단
	m_sLineData[7] = FmDDPermil(1000, -PENALTY_AREA_Y);					// 페널티 안쪽 하단
	m_sLineData[8] = FmDDPermil(GOAL_AREA_X, -GOAL_AREA_Y);
	m_sLineData[9] = FmDDPermil(GOAL_AREA_X, GOAL_AREA_Y);
	m_sLineData[10] = FmDDPermil(1000, GOAL_AREA_Y);
	m_sLineData[11] = FmDDPermil(1000, -GOAL_AREA_Y);
	m_sLineData[12] = FmDDPermil(-SIDE_FENCE_DIS_X, -SIDE_FENCE_DIS_Y);
	m_sLineData[13] = FmDDPermil(SIDE_FENCE_DIS_X, -SIDE_FENCE_DIS_Y);*/
    
    ccDrawLine( ccp(m_sLineData[13].nX+0, m_sLineData[13].nY+10), ccp(m_sLineData[13].nX+0, m_sLineData[13].nY-10) );
    ccDrawLine( ccp(m_sLineData[13].nX+10, m_sLineData[13].nY+0), ccp(m_sLineData[13].nX-10, m_sLineData[13].nY+0) );
    
    for (int i=0; i<12; i++)
	{
		if (i==6 || i==10) continue;
        
		if ((i & 3) == 3) {
			ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY), ccp(m_sLineData[i-3].nX, m_sLineData[i-3].nY) );
            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY), ccp(-m_sLineData[i-3].nX, m_sLineData[i-3].nY) );
		} else {
            ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY), ccp(m_sLineData[i+1].nX, m_sLineData[i+1].nY) );
			if (i != 0)
                ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY), ccp(-m_sLineData[i+1].nX, m_sLineData[i+1].nY) );
		}
        
/*		if ((i & 3) == 3) {
			ccDrawLine( ccp(+m_sLineData[i].nX, m_sLineData[i].nY+1), ccp(m_sLineData[i-3].nX, m_sLineData[i-3].nY+1) );
            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY+1), ccp(-m_sLineData[i-3].nX, m_sLineData[i-3].nY+1) );
		} else if (i == 1 || i == 5 || i == 9) {
			ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY+1), ccp(m_sLineData[i+1].nX, m_sLineData[i+1].nY+1) );
            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY+1), ccp(-m_sLineData[i+1].nX, m_sLineData[i+1].nY+1) );
		} else {
            ccDrawLine( ccp(+m_sLineData[i].nX+1, m_sLineData[i].nY), ccp(m_sLineData[i+1].nX+1, m_sLineData[i+1].nY) );
			if (i != 0)
                ccDrawLine( ccp(-m_sLineData[i].nX+1, m_sLineData[i].nY), ccp(-m_sLineData[i+1].nX+1, m_sLineData[i+1].nY) );
		}
        
		if ((i & 3) == 3) {
			ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY-1), ccp(m_sLineData[i-3].nX, m_sLineData[i-3].nY-1) );
            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY-1), ccp(-m_sLineData[i-3].nX, m_sLineData[i-3].nY-1) );
		} else if (i == 1 || i == 5 || i == 9) {
			ccDrawLine( ccp(m_sLineData[i].nX, m_sLineData[i].nY-1), ccp(m_sLineData[i+1].nX, m_sLineData[i+1].nY-1) );
            ccDrawLine( ccp(-m_sLineData[i].nX, m_sLineData[i].nY-1), ccp(-m_sLineData[i+1].nX, m_sLineData[i+1].nY-1) );
		} else {
            ccDrawLine( ccp(m_sLineData[i].nX-1, m_sLineData[i].nY), ccp(m_sLineData[i+1].nX-1, m_sLineData[i+1].nY) );
            
			if (i != 0)
                ccDrawLine( ccp(-m_sLineData[i].nX-1, m_sLineData[i].nY), ccp(-m_sLineData[i+1].nX-1, m_sLineData[i+1].nY) );
		}*/
	}
    
    glLineWidth(1);
    ccDrawColor4B(255,255,255,255);
    ccPointSize(1);
}

FmP2D CTestBoard::GetScreenPoint(int x, int y, int z)
{
    x= x*292/BACK_X;
    y= y*292/BACK_X;
    z= z*292/BACK_X;
    
    
    CCPoint ret;
    // Eye
    float eyex = 0;
    float eyey = 0;
    float eyez = -LCD_HEIGHT/2/tan(CC_DEGREES_TO_RADIANS(30)); //-LCD_HEIGHT/2/sin(CC_DEGREES_TO_RADIANS(30));
    
    // Screen
    float screen = 0;//eyez* (getCamera()->getZEye()*2-0.1f);

//    0.1f, zeye*2
    
    // Rotation
    // =(L3+$I$10)*(cosf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //+(M3+$I$11)*(sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz))-cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //+(N3+$I$12)*(cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz))+sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //cosf(CC_DEGREES_TO_RADIANS(
    //sinf(CC_DEGREES_TO_RADIANS(
    //=(L3+$I$10)*(COS(RADIANS($I$16))*COS(RADIANS($I$17)))+(M3+$I$11)*(SIN(RADIANS($I$15))*SIN(RADIANS($I$16))*COS(RADIANS($I$17))-COS(RADIANS($I$15))*SIN(RADIANS($I$17)))+(N3+$I$12)*(COS(RADIANS($I$15))*SIN(RADIANS($I$16))*COS(RADIANS($I$17))+SIN(RADIANS($I$15))*SIN(RADIANS($I$17)))
    float rotx = x * (cosf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
               + y * (sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz))-cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
               + z * (cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz))+sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)));
    // =(L3+$I$10)*(cosf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //+(M3+$I$11)*(sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz))+cosf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //+(N3+$I$12)*(cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz))-sinf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
    float roty = x * (cosf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
               + y * (sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz))+cosf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
               + z * (cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz))-sinf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)));
    // =-(L3+$I$10)*sinf(CC_DEGREES_TO_RADIANS(m_Ty))
    //+(M3+$I$11)*(sinf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Ty)))
    //+(N3+$I$12)*(cosf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Ty)))
    float rotz = - x * sinf(CC_DEGREES_TO_RADIANS(m_Ty))
                 + y * (sinf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Ty)))
                 + z * (cosf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Ty)));
    
    // Screen좌표
    // rotx-(rotx-eyex)*(roty-screen)/(roty-eyey)
    float rX = rotx-(rotx-eyex)*(rotz-screen)/(rotz-eyez);
    // roty-(roty-eyez)*(roty-screen)/(roty-eyey)
    float rY = roty-(roty-eyey)*(rotz-screen)/(rotz-eyez);
    
    
    ret.x = rX;
    ret.y = rY;
    
    FmP2D test;
    test.nX = ret.x;
    test.nY = ret.y;
    
    return test;
}

