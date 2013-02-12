//
//  FmP3D.h
//  FifaManager
//
//  Created by louis on 13. 1. 22..
//
//

#ifndef __FifaManager__FmP3D__
#define __FifaManager__FmP3D__

#define TR_VAL      5
#define INT_TO_FIXED(a)     ((a) << TR_VAL)
#define FIXED_TO_INT(a)     ((a) >> TR_VAL)

typedef struct tagFmP2D
{
    int         nX;
    int         nY;
} FmP2D;

class FmP3D
{
protected:
    int m_X, m_Y, m_Z;
    
public:
    FmP3D(int nx = 0, int ny = 0, int nz = 0, bool bTr = false);
    ~FmP3D();
    
    FmP3D operator+(const FmP3D& t3D);
    FmP3D operator+(int nV);
    FmP3D operator-(const FmP3D& t3D);
    FmP3D operator-(int nV);
    FmP3D operator*(const FmP3D& t3D);
    FmP3D operator*(int nV);
    FmP3D operator/(const FmP3D& t3D);
    FmP3D operator/(int nV);
    bool operator==(const FmP3D& t3D);
    
    inline FmP3D    Get()           { return FmP3D(GetX(), GetY(), GetZ()); }
    inline int      GetX()          { return m_X; }
    inline int      GetY()          { return m_Y; }
    inline int      GetZ()          { return m_Z; }
    inline void     SetX(int nV)    { m_X = nV; }
    inline void     SetY(int nV)    { m_Y = nV; }
    inline void     SetZ(int nV)    { m_Z = nV; }
    inline FmP3D    GetTr()         { return FmP3D(GetTrX(), GetTrY(), GetTrZ()); }
    inline int      GetTrX()        { return FIXED_TO_INT(m_X); }
    inline int      GetTrY()        { return FIXED_TO_INT(m_Y); }
    inline int      GetTrZ()        { return FIXED_TO_INT(m_Z); }

    unsigned int    GetRangePow(FmP3D t3D);            //두 점간의 거리 제곱
    unsigned int    GetRange(FmP3D t3D);               //두 점간의 거리
    int             GetAngle(FmP3D t3D);               //입력 점을 바라보는 각도
    FmP2D           GetDD(bool ableZ = true);          //좌표를 Draw좌표로 변환
    FmP3D           GetMovePos(int nAng, int nDis);    //각도로 거리만큼 이동시의 좌표
    
    FmP2D           GetScreenPoint(int x, int y, int z);
};

FmP2D Fm2DPermil(int nX, int nY);                   //운동장 크기에 천분율 3D좌표
FmP3D Fm3DPermil(int nX, int nY);                   //운동장 크기에 천분율 3D좌표
FmP2D FmDDPermil(int nX, int nY);                   //운동장 크기에 천분율 Draw좌표
FmP3D Fm2Dto3D(FmP2D t2D, int nZ = 0);              //2D

#endif /* defined(__FifaManager__FmP3D__) */
