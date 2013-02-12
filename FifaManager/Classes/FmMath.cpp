//
//  FmMath.cpp
//  FifaManager
//
//  Created by louis on 13. 1. 25..
//
//

#include "FmMath.h"
#include "CCPlatformMacros.h"

int Mod(int v1, int v2)
{
    if(v1 < 0)      v1 += v2;
    if(v1 >= v2)    v1 -= v2;
    CC_ASSERT(v1 >= 0 && v1 < 360);
    
    return v1;
}

int AngSign(int v)
{
    v = Mod(v, 360);
    if(v >= 0 && v < 180)
        return 1;
    return -1;
}

int AngDis(int v1, int v2)
{
    int t = v2 - v1;
    if(t > 180)     t -= 360;
    if(t <= -180)   t += 360;

    return t;
}

int Get8Dir(int nAng)
{
    int t = (nAng+23)/45;
    
    if(t > 4)
        return t - 8;
    
    return t;
}