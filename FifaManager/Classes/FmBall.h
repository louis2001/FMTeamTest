//
//  FmBall.h
//  FifaManager
//
//  Created by louis on 13. 1. 24..
//
//

#ifndef __FifaManager__FmBall__
#define __FifaManager__FmBall__

#include "FmObject.h"

static const int C_SPEED_REG[3]     = { 800, 700, 875 };            //땅에 닿을때 공의 speed 감속 퍼밀
static const int C_SPEED_REG2[3]    = {   3,   4,   3 };            //땅에 닿을때 공의 speed 감속 차감 값
static const int C_SPEED_AIR_REG[3] = { 985, 980, 984 };            //공기중에서 공의 speed 감속 퍼밀
static const int C_SPEEDZ_REG[3]    = { 600, 500, 600 };            //땅에 닿을때 speedZ 감속 퍼밀
static const int C_SPEEDZ_REG2[3]   = {  64,  80,  60 };            //땅에 닿을때 speedZ 감속 차감 값
static const int C_SPEEDZ_AIR_REG[3]= {  24,  26,  24 };            //중력 speedZ에 차감 값
static const int C_SPIN_REG[3]      = { 500, 300, 480 };            //땅에 땋을때 감소 회전 퍼밀
static const int C_SPIN_AIR_REG[3]  = { 890, 750, 850 };            //공기중에서 공의 감소 회전 퍼밀

#define GROUND_CONDITION        2

#define CON_SPEED_REG		(C_SPEED_REG[GROUND_CONDITION]+100)
#define CON_SPEED_REG2		C_SPEED_REG2[GROUND_CONDITION]
#define CON_SPEED_AIR_REG	C_SPEED_AIR_REG[GROUND_CONDITION]
#define CON_SPEEDZ_REG		(C_SPEEDZ_REG[GROUND_CONDITION]+100)
#define CON_SPEEDZ_REG2		C_SPEEDZ_REG2[GROUND_CONDITION]
#define CON_SPEEDZ_AIR_REG	C_SPEEDZ_AIR_REG[GROUND_CONDITION]
#define CON_SPIN_REG		C_SPIN_REG[GROUND_CONDITION]
#define CON_SPIN_AIR_REG	C_SPIN_AIR_REG[GROUND_CONDITION]

class CFmBall : public CFmObject
{
public:
    CFmBall();
    ~CFmBall();
    
    void operator=(CFmBall& pb);

public:
    FmP2D               m_tBoundPos;                    // 받을 위치 좌표
    FmP2D               m_tBoundPosSnd;                 // 머리 위치에 도달 좌표
    int                 m_nBoundHH;                     // 바운드 최대 높이
    int                 m_nTouchTeam;                   // 최종 터치팀
    int                 m_nTouchPI;                     // 최종 터치선수
    int                 m_nNotForceFlag;                // 볼에 액션을 제한하기 위한 플래그
    int                 m_nMissFlag;                    // 볼 간섭 AI처리용 플래그
   
    int                 m_nSpin;                        // 회전
    
    void                Init();
    bool                Update(bool bTmp = false);
    void                Force(int nTeam, int nIdx, int nAng, int nPow, int nPowZ, int nSpin, bool dribble = false);             //공 힘 전달
    void                Bound(int nTeam, int nIdx, int nAng);
    void                SetBoundPos();
    
    void                StickMove(int nX);
    
    FmP3D               GetPredictMovePos(int frm);
    
    void                CheckGoalArea();
    void                CheckGoalArea2();
    void                CheckUpperFence();
    bool                CheckGoalpost();
    void                CheckSideFence();
    
    inline void         SetNotForceFlag(int nFrm) { m_nNotForceFlag = nFrm; }
    
};


#endif /* defined(__FifaManager__FmBall__) */
