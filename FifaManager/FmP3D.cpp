//
//  FmP3D.cpp
//  FifaManager
//
//  Created by louis on 13. 1. 22..
//
//
#include "FmP3D.h"
#include "ccMacros.h"
#include "GameDef.h"
#include "Config.h"
#include "cocos2d.h"
USING_NS_CC;

FmP3D::FmP3D(int nx/* = 0*/, int ny/* = 0*/, int nz/* = 0*/, bool bTr/* = false*/)
{
    m_X = nx << (TR_VAL*bTr), m_Y = ny << (TR_VAL*bTr), m_Z = nz << (TR_VAL*bTr);
}

FmP3D::~FmP3D()
{
    
}

FmP3D FmP3D::operator+(const FmP3D &t3D)
{
    FmP3D tp(m_X, m_Y, m_Z);
    
    tp.m_X += t3D.m_X;
    tp.m_Y += t3D.m_Y;
    tp.m_Z += t3D.m_Z;
    
    return tp;
}

FmP3D FmP3D::operator+(int nV)
{
    FmP3D tp(m_X, m_Y, m_Z);
    
    tp.m_X += nV;
    tp.m_Y += nV;
    tp.m_Z += nV;
    
    return tp;
}

FmP3D FmP3D::operator-(const FmP3D &t3D)
{
    FmP3D tp(m_X, m_Y, m_Z);
    
    tp.m_X -= t3D.m_X;
    tp.m_Y -= t3D.m_Y;
    tp.m_Z -= t3D.m_Z;
    
    return tp;
}

FmP3D FmP3D::operator-(int nV)
{
    FmP3D tp(m_X, m_Y, m_Z);
    
    tp.m_X -= nV;
    tp.m_Y -= nV;
    tp.m_Z -= nV;
    
    return tp;
}

FmP3D FmP3D::operator*(const FmP3D &t3D)
{
    FmP3D tp(m_X, m_Y, m_Z);
    
    tp.m_X *= t3D.m_X;
    tp.m_Y *= t3D.m_Y;
    tp.m_Z *= t3D.m_Z;
    
    return tp;
}

FmP3D FmP3D::operator*(int nV)
{
    FmP3D tp(m_X, m_Y, m_Z);
    
    tp.m_X *= nV;
    tp.m_Y *= nV;
    tp.m_Z *= nV;
    
    return tp;
}

FmP3D FmP3D::operator/(const FmP3D &t3D)
{
    FmP3D tp(m_X, m_Y, m_Z);
    
    tp.m_X /= t3D.m_X;
    tp.m_Y /= t3D.m_Y;
    tp.m_Z /= t3D.m_Z;
    
    return tp;
}

FmP3D FmP3D::operator/(int nV)
{
    FmP3D tp(m_X, m_Y, m_Z);
    
    tp.m_X /= nV;
    tp.m_Y /= nV;
    tp.m_Z /= nV;
    
    return tp;
}

bool FmP3D::operator==(const FmP3D &t3D)
{
    if(m_X == t3D.m_X && m_Y == t3D.m_Y && m_Z == t3D.m_Z)
        return true;
    return false;
}

// 두점간의 거리의 제곱
unsigned int FmP3D::GetRangePow(FmP3D t3D)
{
    FmP3D tTmp(m_X, m_Y, m_Z);
    
    tTmp = tTmp-t3D;
    tTmp = tTmp*tTmp;
    
    return tTmp.GetX() + tTmp.GetY();
}

unsigned int FmP3D::GetRange(FmP3D t3D)
{
    return sqrt(GetRangePow(t3D));
}

int FmP3D::GetAngle(FmP3D t3D)
{
    return CC_RADIANS_TO_DEGREES(atan2(-(GetY() - t3D.GetY()), GetX() - t3D.GetX()));
}

FmP3D FmP3D::GetMovePos(int nAng, int nDis)
{
    FmP3D t3D;
    
    t3D.SetX(GetX() + (int)(-nDis*sin(CC_DEGREES_TO_RADIANS(nAng))));
    t3D.SetY(GetY() + (int)(nDis*cos(CC_DEGREES_TO_RADIANS(nAng))));
    t3D.SetZ(GetZ());
    
    return t3D;
}

FmP2D FmP3D::GetScreenPoint(int x, int y, int z)
{
    FmP2D ret;
    float m_Tx = 59.5+2;
    float m_Ty = 0;
    float m_Tz = 0;
    
    // Eye
    float eyex = 0;
    float eyey = 0;
    float eyez = -LCD_HEIGHT*0.64/tan(CC_DEGREES_TO_RADIANS(30)); //-LCD_HEIGHT/2/sin(CC_DEGREES_TO_RADIANS(30));
    
    float height = CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().height;
    
    // Screen
    float screen = 0;
    
    //    0.1f, zeye*2
    
    // Rotation
    // =(L3+$I$10)*(cosf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //+(M3+$I$11)*(sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz))-cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //+(N3+$I$12)*(cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz))+sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //cosf(CC_DEGREES_TO_RADIANS(
    //sinf(CC_DEGREES_TO_RADIANS(
    //=(L3+$I$10)*(COS(RADIANS($I$16))*COS(RADIANS($I$17)))+(M3+$I$11)*(SIN(RADIANS($I$15))*SIN(RADIANS($I$16))*COS(RADIANS($I$17))-COS(RADIANS($I$15))*SIN(RADIANS($I$17)))+(N3+$I$12)*(COS(RADIANS($I$15))*SIN(RADIANS($I$16))*COS(RADIANS($I$17))+SIN(RADIANS($I$15))*SIN(RADIANS($I$17)))
    float rotx = -x * (cosf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
    - y * (sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz))+cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
    - z * (cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*cosf(CC_DEGREES_TO_RADIANS(m_Tz))-sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)));
    // =(L3+$I$10)*(cosf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //+(M3+$I$11)*(sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz))+cosf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
    //+(N3+$I$12)*(cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz))-sinf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
    float roty = -x * (cosf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz)))
    - y * (sinf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz))-cosf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)))
    - z * (cosf(CC_DEGREES_TO_RADIANS(m_Tx))*sinf(CC_DEGREES_TO_RADIANS(m_Ty))*sinf(CC_DEGREES_TO_RADIANS(m_Tz))+sinf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Tz)));
    // =-(L3+$I$10)*sinf(CC_DEGREES_TO_RADIANS(m_Ty))
    //+(M3+$I$11)*(sinf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Ty)))
    //+(N3+$I$12)*(cosf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Ty)))
    float rotz = - x * sinf(CC_DEGREES_TO_RADIANS(m_Ty))
    + y * (sinf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Ty)))
    + z * (cosf(CC_DEGREES_TO_RADIANS(m_Tx))*cosf(CC_DEGREES_TO_RADIANS(m_Ty)));
    
    // Screen좌표
    // rotx-(rotx-eyex)*(roty-screen)/(roty-eyey)
    ret.nX = rotx-(rotx-eyex)*(rotz-screen)/(rotz-eyez);
    // roty-(roty-eyez)*(roty-screen)/(roty-eyey)
    ret.nY = roty-(roty-eyey)*(rotz-screen)/(rotz-eyez);
    
    return ret;
}

FmP2D FmP3D::GetDD(bool ableZ /*= true*/)
{
    FmP2D t2D;
    
    int addx = GetTrX() * (-GetTrY()-BACK_Y) * (BACK_X - BACK_XU) / (BACK_Y<<1) / BACK_X;
    t2D.nX = GetTrX() + addx;
    //int addx = GetTrX() * sin(CC_DEGREES_TO_RADIANS(90*(GetTrY()+BACK_Y) / (BACK_Y<<1))) * (BACK_X - BACK_XU) / BACK_X;
    //t2D.nX = GetTrX() - addx;
    
    //int addy = BACK_Y * (GetTrY()+BACK_Y) * (BACK_X - BACK_XU-130) / (BACK_Y<<1) / BACK_X;
    float gapy = 300;
    
    int addy = gapy * (sin(CC_DEGREES_TO_RADIANS(90*(GetTrY()+BACK_Y) / (BACK_Y<<1))));
    int addz = ableZ*GetTrZ()*Z_RATIO/100;
    t2D.nY = (GetTrY()*(BACK_Y-gapy/2)/BACK_Y)*82/236 + addz + addy*82/236;
    
    t2D.nY = t2D.nY-BACK_Y*gapy*82/2/BACK_Y/236;
    
   
    
    int x1 = GetTrX();                                              //하단
    int x2 = GetTrX() - GetTrX() * (BACK_X - BACK_XU) / BACK_X;     //상단
    int y1 = -BACK_Y;
    int y2 = BACK_Y;
    
    
    
    if(ableZ == true)
        t2D = GetScreenPoint(GetTrX()*292/BACK_X, (GetTrY()+BACK_Y)*292/BACK_X, -GetTrZ()*292/BACK_X);
    else
        t2D = GetScreenPoint(GetTrX()*292/BACK_X, (GetTrY()+BACK_Y)*292/BACK_X, 0);
    
 //   t2D.nX *= 586.0f/1458;
 //   t2D.nY *= 586.0f/1458;
    
    return t2D;
}

//Function
FmP2D Fm2DPermil(int nX, int nY)                   //운동장 크기에 천분율 3D좌표
{
    FmP2D tTmp;
    
    tTmp.nX = INT_TO_FIXED(BACK_X*nX/1000);
    tTmp.nY = INT_TO_FIXED(BACK_Y*nY/1000);
    
    return tTmp;
}

FmP3D Fm3DPermil(int nX, int nY)                   //운동장 크기에 천분율 3D좌표
{
    return Fm2Dto3D(Fm2DPermil(nX, nY));
}

FmP2D FmDDPermil(int nX, int nY)                   //운동장 크기에 천분율 Draw좌표
{
    FmP3D tTmp = Fm3DPermil(nX, nY);
    
    return tTmp.GetDD();
}

FmP3D Fm2Dto3D(FmP2D t2D, int nZ/* = 0*/)              //2D
{
    return FmP3D(t2D.nX, t2D.nY, nZ);
}


