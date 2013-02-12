//
//  FMScene.cpp
//  FifaManager
//
//  Created by louis on 13. 1. 21..
//
//

#include "FMScene.h"

#include "CTitleScene.h"
#include "CSimulScene.h"

FMScene::FMScene()
{
    CCScene::init();
}

void FMScene::onEnter()
{
    CCScene::onEnter();
}

void FMScene::SetState(FMSCENE_STATE eState)
{
    CCDirector::sharedDirector()->purgeCachedData();
    
    FMScene* pScene = NULL;
    
    switch (eState) {
        case FMSCENE_TITLE:
            pScene = new CTitleScene();
            break;
            
        case FMSCENE_TOPMENU:
            //            pScene = new CTopMenuScene();
            break;
            
        case FMSCENE_SIMUL:
            pScene = new CSimulScene();
            break;
            
        default:
            break;
    }
    
    if (pScene) {
        pScene->runScene();
        pScene->release();
    }
}