//
//  FmPlayer.h
//  FifaManager
//
//  Created by louis on 13. 2. 6..
//
//

#ifndef __FifaManager__FmPlayer__
#define __FifaManager__FmPlayer__

#include "GameDef.h"
#include "FmObject.h"
#include "FsmManager.h"

enum eFSMPlayerType
{
    FSM_PLAYER_INIT = FSM_TYPE_MAX,
    FSM_PLAYER_WAIT,
    FSM_PLAYER_MOVE,
    FSM_PLAYER_PASS,
    FSM_PLAYER_KICK,
    
    FSM_PLAYER_MAX
};

class CFmPlayer : public CFmObject, public CFsmMgr
{
    CFmPlayer(int nTeam, int nIdx, int ID);
    virtual ~CFmPlayer();
    
    bool DoLogic();
    void DoAnimate();
    
bool            m_bRed;
bool            m_bYellow;
int             m_nFoulFlag;
ePosition       m_ePosition;
ePositionSub    m_ePositionSub;


};

#endif /* defined(__FifaManager__FmPlayer__) */
