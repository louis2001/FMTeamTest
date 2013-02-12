//
//  FsmManager.h
//  FifaManager
//
//  Created by louis on 13. 2. 6..
//
//

#ifndef __FifaManager__FsmManager__
#define __FifaManager__FsmManager__

#include "cocos2d.h"

/// This is a growable LIFO stack with an initial capacity of N.
/// If the stack size exceeds the initial capacity, the heap is used
/// to increase the size of the stack.
template <typename T, int N>
class AStack
{
public:
    AStack()
    {
        m_stack = m_array;
        m_count = 0;
        m_capacity = N;
    }
    
    ~AStack()
    {
        if (m_stack != m_array)
        {
            CC_SAFE_DELETE(m_stack);
            m_stack = NULL;
        }
    }
    
    void Push(const T& element)
    {
        if (m_count == m_capacity)
        {
            T* old = m_stack;
            m_capacity *= 2;
            m_stack = (T*)malloc(m_capacity * sizeof(T));
            std::memcpy(m_stack, old, m_count * sizeof(T));
            if (old != m_array)
            {
                CC_SAFE_DELETE(old);
            }
        }
        
        m_stack[m_count] = element;
        ++m_count;
    }
    
    T Pop()
    {
        assert(m_count > 0);
        --m_count;
        return m_stack[m_count];
    }
    
    T Top()
    {
        return m_stack[m_count-1];
    }
    
    T ElementAt(int idx)
    {        
        return m_stack[idx];
    }
    
    int GetCount()
    {
        return m_count;
    }
    
    int GetCapacity()
    {
        return m_capacity;
    }
    
private:
    T* m_stack;
    T m_array[N];
    int m_count;
    int m_capacity;
};


typedef struct tagFSMMsg {
    int protocol;
    void* pCmdObject;
    int cmd0;
    int cmd1;
    int cmd2;
    int cmd3;
    int cmd4;
    
    bool bCompleteLogic;
    
    tagFSMMsg(){
        protocol = 0;
        pCmdObject = NULL;
        cmd0 = 0;
        cmd1 = 0;
        cmd2 = 0;
        cmd3 = 0;
        cmd4 = 0;
        bCompleteLogic = false;
    }
    
    tagFSMMsg(int p, void* pV = NULL, int c0 = 0, int c1 = 0, int c2 = 0, int c3 = 0, int c4 = 0){
        protocol = p;
        pCmdObject = pV;
        cmd0 = c0;
        cmd1 = c1;
        cmd2 = c2;
        cmd3 = c3;
        cmd4 = c4;
        bCompleteLogic = false;
    }
    
    void SetCompleteLogic(){
        bCompleteLogic = true;
    }
}FSMMsg;

enum eFSMType{
    FSM_TYPE_NONE = -1,
    FSM_TYPE_NEXT,
    FSM_TYPE_MAX
};

#define DEFAULT_STACK_SIZE 10

class CFsmMgr
{
private:
    AStack<FSMMsg*, DEFAULT_STACK_SIZE>* m_pFSMStack;
    
    FSMMsg* m_pCurFsmMsg;
    int m_eFSMState;
    
public:
    CFsmMgr();
    ~CFsmMgr();
    
    virtual void InitFSM();
    
    virtual FSMMsg* PushFSM(FSMMsg* pFSM);
    virtual FSMMsg* PushFSM(int p, void* pV = NULL, int c0 = 0, int c1 = 0, int c2 = 0, int c3 = 0, int c4 = 0);
    
    virtual FSMMsg* TopFSM();
    virtual void PopFSM();
    
    virtual void NextFSM();
    virtual void CompleteFSM();
    virtual void NextSpotFSM();
    
    FSMMsg* FSMHandle();
    void DoFSMHandle();
    
    virtual void InitFSMLogic() = 0;
    virtual void DoFSMLogic() = 0;
    
    void ClearFSM();
    
    bool IsEmptyFSM();
};

#endif /* defined(__FifaManager__FsmManager__) */
