//
//  FmObject.cpp
//  FifaManager
//
//  Created by louis on 13. 1. 24..
//
//

#include "FmObject.h"

CFmObject::CFmObject()
{
    m_nType     = TYPE_OBJECT_NONE;
    m_pPos      = new FmP3D();
    m_nAngle    = 0;
    m_nSpeed    = 0;
    m_nSpeedZ   = 0;
}

CFmObject::~CFmObject()
{
    
}

uint32_t CFmObject::GetRange(CFmObject *pObj)
{
    return m_pPos->GetRange(*pObj->m_pPos);
}

uint32_t CFmObject::GetRangePow(CFmObject *pObj)
{
    return m_pPos->GetRangePow(*pObj->m_pPos);
}

int CFmObject::GetAngle(CFmObject *pObj)
{
    return m_pPos->GetAngle(*pObj->m_pPos);
}