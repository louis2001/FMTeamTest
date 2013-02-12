//
//  FmBall.cpp
//  FifaManager
//
//  Created by louis on 13. 1. 24..
//
//

#include "FmBall.h"
#include "FmMath.h"
#include "GameDef.h"

CFmBall::CFmBall()
{
    m_nType = TYPE_OBJECT_BALL;
    
    Init();
}

CFmBall::~CFmBall()
{
    CC_SAFE_DELETE(m_pPos);
}

void CFmBall::operator=(CFmBall &pb)
{
    *m_pPos = *pb.m_pPos;
    
    m_nSpeed        = pb.m_nSpeed;
    m_nSpeedZ       = pb.m_nSpeedZ;
    m_tBoundPos     = pb.m_tBoundPos;
    m_tBoundPosSnd  = pb.m_tBoundPosSnd;
    m_nBoundHH      = pb.m_nBoundHH;
    m_nSpin         = pb.m_nSpin;
    m_nTouchTeam    = pb.m_nTouchTeam;
    m_nTouchPI      = pb.m_nTouchPI;
    m_nAngle        = pb.m_nAngle;
    m_nNotForceFlag = pb.m_nNotForceFlag;
    m_nMissFlag     = pb.m_nMissFlag;
}

void CFmBall::Init()
{
    m_nAngle            = 0;
    m_nSpeed            = 0;
    m_nSpeedZ           = 0;
    
    *m_pPos             = FmP3D(0, 0, 0);
    m_nTouchTeam        = 0;
    m_nTouchPI          = -1;
    m_nSpin             = 0;
    m_nNotForceFlag     = 0;
    m_nMissFlag         = 0;
    m_nBoundHH          = -1;
    m_tBoundPos.nX      = 0;
    m_tBoundPos.nY      = 0;
    m_tBoundPosSnd.nX   = 0;
    m_tBoundPosSnd.nY   = 0;
}

bool CFmBall::Update(bool bTmp/* = false*/)
{
    bool ret = false;
    //좌표이동
    *m_pPos = *m_pPos + FmP3D(-sin(CC_DEGREES_TO_RADIANS(m_nAngle))*m_nSpeed, cos(CC_DEGREES_TO_RADIANS(m_nAngle))*m_nSpeed, m_nSpeedZ);
    
    if(!bTmp)
        ret = CheckGoalpost();
    
    if(m_pPos->GetZ() <= 0)                     //땅에 닿았을때 처리
    {
        if(m_nSpeedZ == 0)
        {
            if(m_nSpeed/20 > CON_SPEED_REG2)
                m_nSpeed -= m_nSpeed/20;        //공 빠르면 많이 차감
            else
                m_nSpeed -= CON_SPEED_REG2;     //공기 저항 속도
        }
        else
        {
            m_nSpeed = m_nSpeed * CON_SPEED_REG/1000 - CON_SPEED_REG2;
        }
        
        m_nSpeedZ = -m_nSpeedZ * CON_SPEEDZ_REG/1000 - CON_SPEEDZ_REG2;         //Z축 속도 감소
        if(m_nSpeedZ < INT_TO_FIXED(1))
            m_nSpeedZ = 0;
        
        m_pPos->SetZ(0);
        m_nAngle = m_nAngle + m_nSpin/16;
        m_nSpin = m_nSpin * CON_SPIN_REG/1000;
        
        if(!bTmp)
        {
            if(m_nSpeedZ != 0)
                SetBoundPos();
            else
                m_nBoundHH = -1;
        }
    }
    else
    {
        m_nSpeed = m_nSpeed * CON_SPEED_AIR_REG/1000;
        m_nSpeedZ -= CON_SPEEDZ_AIR_REG;
        int t = 10 + m_nSpeed / INT_TO_FIXED(30);
        m_nAngle = m_nAngle + m_nSpin*t/900;
        m_nSpin = m_nSpin * CON_SPIN_AIR_REG/1000;
    }
    
    m_nAngle = Mod(m_nAngle, 360);
    if(m_nSpeed < INT_TO_FIXED(1))
        m_nSpeed = 0;
    if(m_nNotForceFlag > 0)
        m_nNotForceFlag--;
    if(m_nMissFlag > 0)
        m_nMissFlag--;
    
    return ret;
}

void CFmBall::Force(int nTeam, int nIdx, int nAng, int nPow, int nPowZ, int nSpin, bool dribble/* = false*/)
{
    if(nPow != 0 && m_nNotForceFlag > 0 && m_nTouchTeam == nTeam && m_nTouchPI == nIdx)
        return;
    m_nTouchTeam = nTeam;
    m_nTouchPI = nIdx;
    m_nAngle = nAng;
    m_nSpeed = nPow;
    m_nSpeedZ = nPowZ;
    m_nSpin = nSpin;
    m_nMissFlag = 0;
    
    if(m_nSpeed > INT_TO_FIXED(8))
		m_nMissFlag = 12;
}

void CFmBall::Bound(int nTeam, int nIdx, int nAng)
{
    int t = (180 - abs(AngDis(m_nAngle, nAng))) / 45;               //0~3(순방향3, 역방향0)
    m_nTouchTeam = nTeam;
    m_nTouchPI = nIdx;
    m_nAngle = nAng;
    m_nSpeed = (m_nSpeed*(rand()%2+2+t))>>3;                    //(25%~62.5% , 37.5%~75%) 로 감속된다.
    m_nSpeedZ = (m_nSpeedZ*(rand()%2+2+t))>>4;                  //(25%~62.5% , 37.5%~75%) 로 감속된다.
    SetBoundPos();
    m_nMissFlag = 0;
    m_nNotForceFlag = 0;
    if(m_nSpeed > INT_TO_FIXED(8))
        m_nMissFlag = 6;
}

void CFmBall::SetBoundPos()
{
    CFmBall* pBall = new CFmBall();
    pBall->Init();
    *pBall = *this;
    pBall->m_nBoundHH = -1;
    pBall->m_tBoundPos.nX = 0;
    pBall->m_tBoundPos.nY = 0;
    pBall->m_tBoundPosSnd.nX = 0;
    pBall->m_tBoundPosSnd.nY = 0;
    
    bool bBound = false;
    int nBeforeSpdZ = 0;
    
    for(int i = 0; i < 150; i++)
    {
//        m_tBallTracePos[i].nX = -1;
//        m_tBallTracePos[i].nY = -1;
//        
//        m_tBallTracePos2[i].nX = -1;
//        m_tBallTracePos2[i].nY = -1;
    }
    
    for(int i = 0; i < 150; i++)
    {
        if(bBound == false)
            nBeforeSpdZ = m_nSpeedZ;
        Update(true);
        if(bBound == false && nBeforeSpdZ < 0 && m_nSpeedZ > 0)
            bBound = true;
        
//        m_tBallTracePos[i] = m_pPos->GetDD();
//        m_tBallTracePos[i] = m_pPos->GetDD(false);
        
        //공 머리 위치지점 체크
        if(pBall->m_tBoundPos.nX == 0 && pBall->m_tBoundPos.nY == 0 && bBound == false && m_nSpeedZ <= 0 && m_pPos->GetTrZ() < 80)
        {
            pBall->m_tBoundPos.nX = m_pPos->GetX();
            pBall->m_tBoundPos.nY = m_pPos->GetY();
        }
        
        //공 착지 위치 체크
        if(pBall->m_tBoundPosSnd.nX == 0 && pBall->m_tBoundPosSnd.nY == 0 && bBound)
        {
            pBall->m_tBoundPosSnd.nX = m_pPos->GetX();
            pBall->m_tBoundPosSnd.nY = m_pPos->GetY();
            break;
        }
        
        //경기장 밖으로 나가는 공에 대한 체크
        if(abs(m_pPos->GetX()) > INT_TO_FIXED(BACK_X)*11/10 || abs(m_pPos->GetY()) > INT_TO_FIXED(BACK_Y)*12/10)
        {
            pBall->m_tBoundPos.nX = m_pPos->GetX();
            pBall->m_tBoundPos.nY = m_pPos->GetY();
            pBall->m_tBoundPosSnd.nX = m_pPos->GetX();
            pBall->m_tBoundPosSnd.nY = m_pPos->GetY();
            break;
        }
        
        //공이 가장 높게 떴을때 Z좌표 체크
        if(m_pPos->GetTrZ() > pBall->m_nBoundHH)
        {
            pBall->m_nBoundHH = m_pPos->GetTrZ();
        }
    }
    
    *this = *pBall;
    CC_SAFE_DELETE(pBall);
}

FmP3D CFmBall::GetPredictMovePos(int frm)
{
    if(frm <= 0)
        return *m_pPos;
    CFmBall* pBall = new CFmBall();
    pBall->Init();
    *pBall = *this;
    for(int i = 0; i < frm-1; i++)
        Update(true);
    FmP3D tmp = *m_pPos;
    *this = *pBall;
    
    return tmp;
}

void CFmBall::CheckGoalArea()
{
	if(abs(m_pPos->GetX()) > abs(INT_TO_FIXED(GOALPOST_X*BACK_X/1000)))
	{
		m_pPos->SetX(INT_TO_FIXED(GOALPOST_X*BACK_X/1000)*FmSign(m_pPos->GetX()));
		m_nAngle = Mod(360-m_nAngle, 360);
        
		m_nSpeedZ = m_nSpeedZ/6;
		m_nSpeed = m_nSpeed/6;
		//if(m_pPos->GetZ() < INT_TO_FIXED(20))
		//	m_pRefPlayMgr->m_pGoalPost[m_pPos->GetX()>0?1:0][2]->GetAniObject()->InitMotion(6, false);
		//else
		//	m_pRefPlayMgr->m_pGoalPost[m_pPos->GetX()>0?1:0][2]->GetAniObject()->InitMotion(5, false);
		//GET_APP()->PlaySound(SOUND_KIND_GOALWEB, false);
	}
    
	if (abs(m_pPos->GetY()) > abs(INT_TO_FIXED(GOALPOST_Y*BACK_Y/1000)))
	{
		m_pPos->SetY(INT_TO_FIXED(GOALPOST_Y*BACK_Y/1000)*FmSign(m_pPos->GetY()));
		m_nAngle = Mod(180-m_nAngle, 360);
		m_nSpeedZ = m_nSpeedZ / 6;
		m_nSpeed = m_nSpeed / 3;
		//if(m_pPos->GetY() > 0)
		//	m_pRefPlayMgr->m_pGoalPost[m_pPos->GetX()>0?1:0][0]->GetAniObject()->InitMotion(4, false);
	}
	if (m_pPos->GetZ() > INT_TO_FIXED(GOALPOST_Z))
	{
		m_pPos->SetZ(INT_TO_FIXED(GOALPOST_Z));
		m_nSpeedZ = m_nSpeedZ / 6;
		m_nSpeed = m_nSpeed / 6;
		if (m_nSpeedZ > 0)
            m_nSpeedZ *= -1;
		//m_pRefPlayMgr->m_pGoalPost[m_pPos->GetX()>0?1:0][0]->GetAniObject()->InitMotion(3, false);
	}
}

void CFmBall::CheckGoalArea2()														//노골일 경우 골대와 비교
{
	if (abs(m_pPos->GetX()) > abs(INT_TO_FIXED(BACK_X)) && abs(m_pPos->GetX()) < abs(INT_TO_FIXED(GOALPOST_X*BACK_X/1000)) && (m_pPos->GetZ() < INT_TO_FIXED(GOALPOST_Z)) && abs(m_pPos->GetY()) < abs(INT_TO_FIXED(GOALPOST_Y*BACK_Y/1000)))
	{
		if (m_pPos->GetZ() - m_nSpeedZ - CON_SPEEDZ_AIR_REG < INT_TO_FIXED(GOALPOST_Z))	//골망의 옆쪽에 걸린경우
		{
			m_pPos->SetY(INT_TO_FIXED(GOALPOST_Y*BACK_Y/1000)*FmSign(m_pPos->GetY()));
			m_nAngle = Mod(180-m_nAngle, 360);
			m_nSpeedZ = m_nSpeedZ / 6;
			m_nSpeed = m_nSpeed / 6;
			//if(m_pPos->GetY() > 0)
			//	m_pRefPlayMgr->m_pGoalPost[m_pPos->GetX()>0?1:0][0]->GetAniObject()->InitMotion(4, false);
		}
		else																		//골망의 위쪽에 걸린 경우
		{
			m_pPos->SetZ(INT_TO_FIXED(GOALPOST_Z)+1);
			m_nSpeedZ = abs(m_nSpeedZ / 6);										//공은 위로 튀게
			m_nSpeed = m_nSpeed / 2;
			//m_pRefPlayMgr->m_pGoalPost[m_pPos->GetX()>0?1:0][0]->GetAniObject()->InitMotion(3, false);
		}
	}
}

void CFmBall::CheckUpperFence()																//위쪽 펜스 비교
{
/*	if (m_pPos->GetY() < -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS) && m_pPos->GetY() > -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17))			//펜스 넘어감
	{
		if (m_pPos->GetZ() < INT_TO_FIXED(17))				//펜스 높이에 걸림
		{
			m_pPos->SetY(-INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS));
			m_nAngle = Mod(180-m_nAngle, 360);
			m_nSpeed = m_nSpeed / 4;
			m_nSpeedZ = m_nSpeedZ / 4;
		}
	} else if (m_pPos->GetY() < -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17) && m_pPos->GetY() > -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17+30)) {
		if (m_pPos->GetZ() < 0)				//펜스 높이에 걸림
		{
			m_pPos->SetY(-INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17));
			m_nAngle = Mod(180-m_nAngle, 360);
			m_nSpeed = m_nSpeed / 4;
			m_nSpeedZ = m_nSpeedZ / 4;
		}
	} else if (m_pPos->GetY() < -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17+30) && m_pPos->GetY() > -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17+30+37)) {
		if (m_pPos->GetZ() < INT_TO_FIXED(37))				//펜스 높이에 걸림
		{
			m_pPos->SetY(-INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17+30));
			m_nAngle = Mod(180-m_nAngle, 360);
			m_nSpeed = m_nSpeed / 4;
			m_nSpeedZ = m_nSpeedZ / 4;
		}
	}
    
	if (abs(m_pPos->GetX()) > INT_TO_FIXED(SIDE_FENCE_DIS_X*BACK_X/1000) && abs(m_pPos->GetX()) < INT_TO_FIXED(SIDE_FENCE_DIS_X*BACK_X/1000 + 17))		//펜스 넘어감
	{
		if (m_pPos->GetZ() < INT_TO_FIXED(17))				//펜스 높이에 걸림
		{
			if(m_pPos->GetX() > 0) {
				m_pPos->SetX(INT_TO_FIXED(SIDE_FENCE_DIS_X*BACK_X/1000));
			} else {
				m_pPos->SetX(-INT_TO_FIXED(SIDE_FENCE_DIS_X*BACK_X/1000));
			}
			m_nAngle = Mod(360-m_nAngle, 360);
			m_nSpeed = m_nSpeed / 4;
			m_nSpeedZ = m_nSpeedZ / 4;
		}
	} else {
        
		if (abs(m_pPos->GetX()) > INT_TO_FIXED(BACK_X+500))		//펜스 넘어감
		{
			m_nAngle = Mod(360-m_nAngle, 360);
			m_nSpeed = m_nSpeed / 6;
			m_nSpeedZ = m_nSpeedZ / 6;
		}
	}*/
    
    if (abs(m_pPos->GetY()) > INT_TO_FIXED(BACK_Y))//+500))		//펜스 넘어감
	{
        m_pPos->SetY(FmSign(m_pPos->GetY())*INT_TO_FIXED(BACK_Y));
		m_nAngle = Mod(180-m_nAngle, 360);
//		m_nSpeed = m_nSpeed / 6;
//		m_nSpeedZ = m_nSpeedZ / 6;
	}
}

bool CFmBall::CheckGoalpost()																//골대 비교
{
	if(m_nSpeed == 0)	return false;
	int tmpx = abs(m_pPos->GetX()) - abs(INT_TO_FIXED(BACK_X));
	int tmpy = abs(m_pPos->GetY()) - abs(INT_TO_FIXED(GOALPOST_Y*BACK_Y/1000));
	int rate = 20;
	if(tmpx*tmpx+tmpy*tmpy < INT_TO_FIXED(5)*INT_TO_FIXED(5))									//골포스트 맞음
	{
		int movex, movey;
		for(int i = 0; i <= 20; ++i)
		{
			movex = m_pPos->GetX() + (sin(CC_DEGREES_TO_RADIANS(m_nAngle))*i*m_nSpeed)/20;
			movey = m_pPos->GetY() - (cos(CC_DEGREES_TO_RADIANS(m_nAngle))*i*m_nSpeed)/20;
			tmpx = abs(movex) - abs(INT_TO_FIXED(BACK_X));
			tmpy = abs(movey) - abs(INT_TO_FIXED(GOALPOST_Y*BACK_Y/1000));
			if(tmpx*tmpx+tmpy*tmpy < INT_TO_FIXED(5)*INT_TO_FIXED(5)) continue;
			rate = i-1;
			break;
		}
		m_pPos->SetX(m_pPos->GetX() + (sin(CC_DEGREES_TO_RADIANS(m_nAngle))*rate*m_nSpeed)/20);
		m_pPos->SetY(m_pPos->GetY() - (cos(CC_DEGREES_TO_RADIANS(m_nAngle))*rate*m_nSpeed)/20);
        
		FmP3D cBack = FmP3D((FmSign(m_pPos->GetX()))*abs(INT_TO_FIXED(BACK_X)), FmSign(m_pPos->GetY())*abs(INT_TO_FIXED(GOALPOST_Y*BACK_Y/1000)));
		m_nAngle = cBack.GetAngle(*m_pPos);
		m_nMissFlag = 8;
		m_nSpeed = m_nSpeed*(rand()%20+60)/100;
		m_nSpeedZ = m_nSpeedZ*(rand()%20+60)/100;
		return true;
	}
	return false;
}

void CFmBall::CheckSideFence()																//위쪽 펜스 비교
{
/*	if (m_pPos->GetX() < -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS) && m_pPos->GetX() > -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17))			//펜스 넘어감
	{
		if (m_pPos->GetZ() < INT_TO_FIXED(17))				//펜스 높이에 걸림
		{
			m_pPos->SetY(-INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS));
			m_nAngle = Mod(180-m_nAngle, 360);
			m_nSpeed = m_nSpeed / 4;
			m_nSpeedZ = m_nSpeedZ / 4;
		}
	} else if (m_pPos->GetY() < -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17) && m_pPos->GetY() > -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17+30)) {
		if (m_pPos->GetZ() < INT_TO_FIXED(0))				//펜스 높이에 걸림
		{
			m_pPos->SetY(-INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17));
			m_nAngle = Mod(180-m_nAngle, 360);
			m_nSpeed = m_nSpeed / 4;
			m_nSpeedZ = m_nSpeedZ / 4;
		}
	} else if (m_pPos->GetY() < -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17+30) && m_pPos->GetY() > -INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17+30+37)) {
		if (m_pPos->GetZ() < INT_TO_FIXED(37))				//펜스 높이에 걸림
		{
			m_pPos->SetY(-INT_TO_FIXED(BACK_Y+UPPER_FENCE_DIS+17+30));
			m_nAngle = Mod(180-m_nAngle, 360);
			m_nSpeed = m_nSpeed / 4;
			m_nSpeedZ = m_nSpeedZ / 4;
		}
	}*/
    
    
	if (abs(m_pPos->GetX()) > INT_TO_FIXED(BACK_X))//+500))		//펜스 넘어감
	{
        m_pPos->SetX(FmSign(m_pPos->GetX())*INT_TO_FIXED(BACK_X));
		m_nAngle = Mod(360-m_nAngle, 360);
		//m_nSpeed = m_nSpeed / 6;
		//m_nSpeedZ = m_nSpeedZ / 6;
	}
}

void CFmBall::StickMove(int aX)
{
	int t;
	int tx = -sin(CC_DEGREES_TO_RADIANS(m_nAngle))*m_nSpeed;
    
	if (tx == 0)
        return;
    
	if (m_pPos->GetX() > aX)
	{
		if (m_pPos->GetX() + tx > aX)
            return;
	}
    else
    {
		if (m_pPos->GetX() + tx < aX)
            return;
	}
	t = abs(((aX-m_pPos->GetX())/100) / tx);
    
    *m_pPos = *m_pPos + FmP3D(-sin(CC_DEGREES_TO_RADIANS(m_nAngle))*m_nSpeed*t, cos(CC_DEGREES_TO_RADIANS(m_nAngle))*m_nSpeed*t, m_nSpeedZ*t)/100;
}




