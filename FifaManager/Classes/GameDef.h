//
//  GameDef.h
//  FifaManager
//
//  Created by louis on 13. 1. 23..
//
//

#ifndef FifaManager_GameDef_h
#define FifaManager_GameDef_h

//-경기관련 값정의
// 실제 경기장 비율 참조
#define REAL_STADIUM_X      105
#define REAL_STADIUM_Y      68          //UEFA 경기장 규격 분류 4(UEFA 플레이오프 가능 규격)
// 경기장 상하단 정의
#define BACK_X              729         //사용리소스 사이즈 참조
#define BACK_XU             544//590         //상단 사이즈
#define BACK_Y              (BACK_X*REAL_STADIUM_Y/REAL_STADIUM_X)
#define BACK_Z              BACK_X      //높이는 X축과 비례
#define Z_RATIO             80          //Z축 Y축 투영 비율(%)
// 스크롤 영역 설정(임시)
#define BACK_SCR_X          (BACK_X+30+100)	//운동장 크기(스크롤될 전체 영역)(광고판 뒷그물등 포함된 스크롤가능한 최대 위치)
#define BACK_SCR_Y          (BACK_Y+77+27)


#define __TYPE1_GAMEDEF__

//729 , 472

#if defined(__TYPE1_GAMEDEF__)

//-운동장 관련 셋팅값(운동장 중앙기준으로 경기장영역에 대한 천분율)
// 골포스트 (천분율)
#define GOALPOST_X          1045        //골대 뒷그물까지의 넓이
#define GOALPOST_Y          110         //골대 세로크기
#define GOALPOST_Z          35          //골대 높이
// Penalty (천분율)
#define PENALTY_AREA_X      685//650
#define PENALTY_AREA_Y      595//575
// 골에어리어 (천분율)
#define GOAL_AREA_X         895
#define GOAL_AREA_Y         272
// 펜스 정의
#define UPPER_FENCE_DIS     20          //리얼 사이즈
#define SIDE_FENCE_DIS_X    1165
#define SIDE_FENCE_DIS_Y    1070        //천분율

//-볼,선수 충돌 사이즈
#define SIZE_BALL           9
#define SIZE_PLAYER         15

#else
//-운동장 관련 셋팅값(운동장 중앙기준으로 경기장영역에 대한 천분율)
// 골포스트 (천분율)
#define GOALPOST_X          1045        //골대 뒷그물까지의 넓이
#define GOALPOST_Y          149         //골대 세로크기
#define GOALPOST_Z          80          //골대 높이
// Penalty (천분율)
#define PENALTY_AREA_X      770//685//650
#define PENALTY_AREA_Y      592//575
// 골에어리어 (천분율)
#define GOAL_AREA_X         875
#define GOAL_AREA_Y         275
// 펜스 정의
#define UPPER_FENCE_DIS     20          //리얼 사이즈
#define SIDE_FENCE_DIS_X    1165
#define SIDE_FENCE_DIS_Y    1070        //천분율

//-볼,선수 충돌 사이즈
#define SIZE_BALL           9
#define SIZE_PLAYER         15
#endif

// 능력치 정의
#define PLAYER_ABIL_MAX     999


enum ePosition
{
    POS_NONE = -1,
    POS_GK,             // 키퍼		GK(Goalkeeper)
    POS_DF,				// 수비		CB(Center Back), LB/RB(Left/Right Back) LWB/RWB(Left/Right Wing Back)
    POS_MF,				// 미들		CAM(Center Attacking Midfielder), LWM/RWM(Left/Right Wing Midfieldef) CM(Central Midfielder) CDM(Center Defensive Midfielder, Holding Midfielder)
    POS_FW,				// 공격		ST(Striker), LWF/RWF(Left/Right Wing Forward)
    
    POS_MAX
};

enum ePositionSub
{
    POS_SUB_NONE = -1,
    POS_SUB_MF_WING,
    POS_SUB_DF_WING,
    
    POS_SUB_MAX
};

enum ePlayerMotionDef
{
    MT_NONE = -1,
    MT_WAIT,
    MT_WALK,
    MT_RUN,
    MT_KICK,
    MT_LONGKICK,
    MT_PASS,
    MT_LONGPASS,
    MT_TRAPING,
    MT_TRAPING2,
    MT_SLIDING,
    MT_TURNKICK_CW,
    MT_TURNKICK_CCW,
    MT_TURNPASS_CW,
    MT_TURNPASS_CCW,
    MT_BALLCONTROL1,
    MT_BALLCONTROL2,
    MT_BALLCONTROL3,
    MT_HEADING,
    MT_WAITWITHBALL,
    MT_SLIDINGCATCH,
    MT_DIVING,
    MT_DIVINGCATCH,
    MT_PUNCHING,
    MT_PUNCHINGCATCH,
    MT_GKDEF_CW,
    MT_GKDEF_CCW,
    MT_GK_THROWING,
    MT_GK_THROWING2,
    MT_GK_DROPBALL,
    MT_GK_MOVEBALL,
    MT_GK_DRIBBLE,
    MT_GK_DIRECTION,
    MT_GK_DIRECTION_BALL,
    MT_GK_KICK,
    MT_GK_KICK2,
    MT_THROWINGREADY,
    MT_THROWING,
    MT_TURN180,
    MT_SETPIECESTAND,
    MT_FREEKICK,
    MT_ROBBED,
    MT_ROBBED2,
    MT_FEEL_JOY1,
    MT_FEEL_JOY2,
    MT_FEEL_OTL1_1,
    MT_FEEL_OTL1_2,
    MT_FEEL_OTL2_1,
    MT_FEEL_OTL2_2,
    MT_FEEL_OTL3_1,
    MT_FEEL_OTL3_2,
    MT_FEEL_SHOCK1,
    MT_CEREMONY1,
    MT_CEREMONY2,
    MT_CEREMONY3,
    MT_CEREMONY4,
    MT_CEREMONY5,
    MT_CEREMONY6,
    MT_CEREMONY7,
    MT_DIVINGHEADING,
    MT_WALL1,
    MT_WALL2,
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif
