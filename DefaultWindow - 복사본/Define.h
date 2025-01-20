#pragma once

extern	HWND		g_hWnd;

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			PI			3.141592f

#define			SCENE_CHANGE  999


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

enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LU,
	RU,
	LD,
	RD,

	DIR_END
};

enum class SCENE_TYPE
{
	STAGE1,
	STAGE2,
	STAGE3,

	END
};

enum class OBJECT_TYPE
{
	NONE,
	MONSTER,
	PLAYER,
	BULLET,
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

