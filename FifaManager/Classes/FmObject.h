//
//  FmObject.h
//  FifaManager
//
//  Created by louis on 13. 1. 24..
//
//

#ifndef __FifaManager__FmObject__
#define __FifaManager__FmObject__

#include "cocos2d.h"
#include "FmP3D.h"

USING_NS_CC;

enum
{
    TYPE_OBJECT_NONE = -1,
    TYPE_OBJECT_BALL,
    TYPE_OBJECT_PLAYER,
    
    TYPE_OBJECT_MAX
};

class CFmObject : public CCSprite
{
public:
    CFmObject();
    ~CFmObject();
    
    FmP3D*          m_pPos;
protected:
    int             m_nType;                    //오브젝트 타입
    int             m_nAngle;                   //오브젝트 방향
    
    int             m_nSpeed;                   //속도
    int             m_nSpeedZ;                  //직각속도값
    
public:
    uint32_t        GetRangePow(CFmObject* pObj);
    uint32_t        GetRange(CFmObject* pObj);
    int             GetAngle(CFmObject* pObj);

    inline int      GetType() { return m_nType; }
    inline void     SetAngle(int arc) { m_nAngle = arc; }
    inline int      GetAngle() { return m_nAngle;}
    inline void     SetSpeed(int spd) { m_nSpeed = spd; }
    inline int      GetSpeed() { return m_nSpeed; }
    inline void     SetSpeedZ(int spd) { m_nSpeedZ = spd; }
    inline int      GetSpeedZ() { return m_nSpeedZ; }
};

#endif /* defined(__FifaManager__FmObject__) */
