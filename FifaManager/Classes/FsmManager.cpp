//
//  FsmManager.cpp
//  FifaManager
//
//  Created by louis on 13. 2. 6..
//
//

#include "FsmManager.h"

CFsmMgr::CFsmMgr()
{
    m_pFSMStack = NULL;
    m_pCurFsmMsg = NULL;
    
    InitFSM();
}

CFsmMgr::~CFsmMgr()
{
    if( m_pFSMStack )
    {
        for(int i = 0; i < m_pFSMStack->GetCapacity(); ++i)
        {
            FSMMsg* pFSM = m_pFSMStack->ElementAt(i);
            CC_SAFE_DELETE(pFSM);
        }
        CC_SAFE_DELETE(m_pFSMStack);
    }
}

void CFsmMgr::InitFSM()
{
    m_eFSMState = -1;
    if(m_pFSMStack == NULL)
    {
        m_pFSMStack = new AStack<FSMMsg*, DEFAULT_STACK_SIZE>;
    }
    m_pCurFsmMsg = NULL;
}

void CFsmMgr::ClearFSM()
{
    while(m_pFSMStack->GetCount() > 0)
    {
        PopFSM();
    }
}

FSMMsg* CFsmMgr::PushFSM(FSMMsg *pFSM)
{
    m_pFSMStack->Push(new FSMMsg(pFSM->protocol, pFSM->pCmdObject, pFSM->cmd0, pFSM->cmd1, pFSM->cmd2, pFSM->cmd3, pFSM->cmd4));
    return m_pFSMStack->Top();
}

FSMMsg* CFsmMgr::PushFSM(int p, void* pV, int c0, int c1, int c2, int c3, int c4)
{
    m_pFSMStack->Push(new FSMMsg(p, pV, c0, c1, c2, c3, c4));
    return m_pFSMStack->Top();
}

FSMMsg* CFsmMgr::TopFSM()
{
    return m_pFSMStack->Top();
}

void CFsmMgr::CompleteFSM()
{
    if(m_pCurFsmMsg != NULL)
    {
        m_pCurFsmMsg->bCompleteLogic = false;
    }
}

void CFsmMgr::NextFSM()
{
    if(m_eFSMState != FSM_TYPE_NONE)
    {
        if(m_pCurFsmMsg != NULL)
        {
            if(m_pCurFsmMsg->bCompleteLogic)
                return;
        }
    }
    m_eFSMState = FSM_TYPE_NEXT;
}

void CFsmMgr::NextSpotFSM()
{
    NextFSM();
    DoFSMHandle();
}

void CFsmMgr::PopFSM()
{
    m_pFSMStack->Pop();
}

void CFsmMgr::DoFSMHandle()
{
    if(m_eFSMState == FSM_TYPE_NONE)
    {
        m_pCurFsmMsg = NULL;
        return;
    }
    while(m_eFSMState == 0)
    {
        if(FSMHandle() == NULL)
            return;
    }
    DoFSMLogic();
}

FSMMsg* CFsmMgr::FSMHandle()
{
    if(m_pFSMStack->GetCount() <= 0)
        return NULL;
    m_pCurFsmMsg = TopFSM();
    PopFSM();
    
    m_eFSMState = m_pCurFsmMsg->protocol;
    InitFSMLogic();
    return m_pCurFsmMsg;
}

bool CFsmMgr::IsEmptyFSM()
{
    return (m_pFSMStack->GetCount() <= 0);
}