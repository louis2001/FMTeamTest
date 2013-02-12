//
//  FmMath.h
//  FifaManager
//
//  Created by louis on 13. 1. 25..
//
//

#ifndef __FifaManager__FmMath__
#define __FifaManager__FmMath__

inline int FmSign(int n) { return ( (n) > 0 ) ? 1 : ( (n) < 0 ) ? -1 : 0; } /// 1:(+), 0:(0), -1(-)

int         Mod(int x1, int x2);
int         AngSign(int v);
int         AngDis(int v1, int v2);
int         Get8Dir(int nAng);


#endif /* defined(__FifaManager__FmMath__) */
