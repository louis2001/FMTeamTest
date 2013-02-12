//
//  FMScene.h
//  FifaManager
//
//  Created by louis on 13. 1. 21..
//
//

#ifndef FifaManager_FMScene_h
#define FifaManager_FMScene_h

#include "cocos2d.h"

enum FMSCENE_STATE{
    FMSCENE_TITLE       = 0,
    FMSCENE_TOPMENU,
    
    FMSCENE_SIMUL,
    FMSCENE_MAX_SIZE
};

USING_NS_CC;
using namespace std;

class FMScene : public CCScene
{
public:
    FMScene();
    
    virtual void onEnter();
    
    virtual void runScene() = 0;
    
    void SetState(FMSCENE_STATE eState);
};



#endif
