#pragma once

extern	HWND		g_hWnd;

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			PI			3.141592f

#define			SCENE_CHANGE  999
#define			PLAYER_DIE    2479	

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1






#define SINGLE(type)\
private:\
	type();\
	~type();\
public:\
	static type* CreateSingleTonInst()\
	{\
		static type mgr;\
		return &mgr;\
	}\


enum class COLORSTATE
{
	BLUE, RED, PURPLE, COLOR_END
};

enum class DIRECTION
{
	BLUE = 0,
	RED,
	PURPLE,
	ENEMY,
	DIR_END
};

enum class SCENE_TYPE
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGEBOSS,
	GAMEOVER,

	END
};

enum class OBJECT_TYPE
{
	NONE,
	ITEM,
	MONSTER,
	PLAYER,
	BOSS,
	
	OBJ_BULLET, 
	OBJ_MONSTERBULLET,

	PLAYER_SHIELD,

	UI,
	END
};

typedef struct tagInfo
{
	float		fX;   // pos ÁÂÇ¥
	float		fY;	  // pos ÁÂÇ¥

	float		fCX;  // size Å©±â
	float		fCY;  // size Å©±â	


}INFO;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}

